use std::{
    error::Error,
    io::{self},
    num::ParseIntError,
    str::FromStr,
};

// Reads the next line in stdin and splits by sep, outputting a
fn readline<T>(sep: &str) -> Result<Vec<T>, Box<dyn Error>>
where
    T: FromStr,
    T::Err: Error + 'static,
{
    let mut buf = String::new();
    io::stdin().read_line(&mut buf)?;
    let result = buf
        .trim()
        .split_whitespace()
        .map(|el| el.parse::<T>())
        .collect::<Result<Vec<T>, T::Err>>()
        .map_err(|e| e.into())?;
    Ok(result)
}

fn main() -> Result<(), ParseIntError> {
    let mut buf = String::new();
    io::stdin().read_line(&mut buf);
    let n = match buf.parse::<u32>() {
        Ok(it) => it,
        Err(err) => return Err(err),
    };
    for i in 1..n {
        // Ignore the number of elements.
        io::stdin().read_line(&mut buf);
        io::stdin().read_line(&mut buf);
        let inp: Vec<u32> = buf
            .split_whitespace()
            .map(|x| x.parse::<u32>().unwrap())
            .collect();
        println!("{:?}", inp);
    }
    return Ok(());
}
