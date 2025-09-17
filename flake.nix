{
  description = "flake for dev setup";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };

  outputs = { self, nixpkgs }:
    let
      supportedSystems = [ "aarch64-darwin" "x86_64-linux" ];
      perSystem = pkgs:
        let
          buildTools = with pkgs; [
            rustc
            zsh
            libgcc
          ];
          buildInputs = [
          ];
        in
        {
          packages.default = pkgs.stdenv.mkDerivation {
            pname = "codeforces";
            version = "0.1.0";

            nativeBuildInputs = buildTools;
            buildInputs = buildInputs;

            meta = {
              description = "flake";
              platforms = pkgs.lib.platforms.all; # Works on any system defined above
            };

            buildPhase = ''
              runHook preBuild
              dune build @all
              runHook postBuild
            '';

            doCheck = true;
            checkPhase = ''
              runHook preCheck
              # Add tasks for testing
              runHook postCheck
            '';

            installPhase = ''
              runHook preInstall
              # Add build steps
              runHook postInstall
            '';
          };

          # This defines the development shell using the most basic and compatible method.
          devShells.default = pkgs.mkShell {
            name = "dev-shell";

            # By putting all tools and libraries directly into `buildInputs`,
            # we rely on Nix's most fundamental mechanism for building an environment.
            # This avoids any helper functions that may be missing or incompatible.
            buildInputs = buildTools ++ buildInputs;

            shellHook = ''
              echo "Entered development environment."
              export PATH=${pkgs.zsh}/bin:$PATH
              export SHELL=${pkgs.zsh}/bin/zsh
              exec ${pkgs.zsh}/bin/zsh --login
            '';
          };
        };
      # Generate the outputs for each supported system using the function above.
      flakeOutputs = nixpkgs.lib.foldl'
        (final: system:
          let
            pkgs = nixpkgs.legacyPackages.${system};
            systemOutputs = perSystem pkgs;
          in
          nixpkgs.lib.recursiveUpdate final {
            packages.${system} = systemOutputs.packages;
            devShells.${system} = systemOutputs.devShells;
            checks.${system}.default = systemOutputs.packages.default;
          })
        { }
        supportedSystems;

    in
    flakeOutputs;
}
