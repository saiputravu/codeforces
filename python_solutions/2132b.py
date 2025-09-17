import sys

def solve(n):
  """
  Finds all integers that result from dividing n by (1 + 10**i)
  where the division has no remainder.
  """
  solutions = [n // (1 + 10 ** i) for i in range(1, len(str(n))) if n % (1 + 10 ** i) == 0]
  return solutions

def main():
  """
  Main function to handle input and output as per the requirements.
  """
  # Read the first line to get the number of test cases.
  try:
    num_test_cases = int(sys.stdin.readline())
  except (ValueError, IndexError):
    # Handle cases where input is empty or not a valid number.
    return

  # Process each test case.
  for _ in range(num_test_cases):
    line = sys.stdin.readline().strip()
    if not line:
      continue
    
    try:
      n = int(line)
      results = solve(n)
      
      if not results:
        # If there are no solutions, print '0'.
        print('0')
      else:
        # If solutions exist, print the count.
        print(len(results))
        # Sort the results and print them on a new line, space-separated.
        results.sort()
        print(*results)
        
    except ValueError:
      # Handle cases where a line is not a valid integer.
      print('0')

if __name__ == "__main__":
  main()
