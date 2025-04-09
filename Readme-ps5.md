# PS5: DNA Alignment

## Contact
Name: Mohammed Ayan
Section: 201

Partner: Ansh Patel
Partner Section: 202

Time to Complete: ~8 Hours


## Description
Explain what the project does

This project implements an Edit Distance calculator using dynamic programming in C++. The program is designed to compute the optimal edit distance between two input strings, which is the minimum cost required to transform one string into another through a series of character insertions, deletions, and substitutions. Each operation has an associated cost: insertions and deletions cost 2 units, while substitutions cost 0 if characters match and 1 if they are different. The class uses a dynamic programming matrix (dp) to store results. Once the edit distance is computed using the optDistance() method, the alignment() method reconstructs the exact sequence of operations (match, substitution, insertion, or deletion) required to convert one string into the other, in a clean and readable format. The project includes an interactive command-line interface. Users input two strings, and the program responds by calculating and printing the edit distance, followed by the alignment output showing how each character in one string maps to the other. It also measures and displays the execution time using the SFML library's clock.

### Features
Explain how you did the actual alignment including the data structures used.

The alignment in this project is reconstructed  through the dynamic programming matrix after the optimal edit distance has been calculated. The matrix, stored as a 2D vector of integers (`std::vector<std::vector<int>> dp`), holds the minimum cost to convert substrings of the input strings into each other. Each cell `dp[i][j]` represents the minimum cost to align the first `i` characters of the first string (`str1`) with the first `j` characters of the second string (`str2`). Once the matrix is fully populated, the alignment is performed by walking backward from the bottom-right corner of the DP matrix—starting from `dp[n][m]`, where `n` and `m` are the lengths of the two input strings. The goal is to reconstruct the path that led to this optimal cost. At each step, the program compares the current cell's value with possible predecessors to determine the operation used. If the current value matches the value from the top-left diagonal cell plus the penalty, it adds a line to the alignment indicating which characters were compared and the cost. If the value came from the left or from above, the appropriate operation and cost are recorded. To build the alignment in order, a `std::vector<std::string>` named `result` is used to collect each line of the transformation. Since the traceback is done in reverse order, this vector holds the alignment from end to start. After the traceback is complete, the vector is reversed to present the alignment in the correct sequence from the beginning of the strings. The result is then compiled into a single `std::string` named `output`, which is returned for display.

### Testing
Describe what the unit tests you wrote check for and why you picked them.

The unit tests in this project are designed to validate both the correctness of the edit distance computation and the accuracy of the alignment reconstruction across a variety of scenarios. They ensure the implementation behaves consistently under edge cases, typical inputs, and potentially error conditions. The invalid_cost_check test focuses on the most basic case: transforming a single character into another ("A" to "T"). This tests the substitution cost directly, verifying that a mismatch yields a cost of 1, and checks that the alignment reflects this operation clearly. It's a sanity check for the penalty logic and alignment formatting. The swapped_columns_check test checks the behavior when the input strings are reverse complements ("ACGT" and "TGCA"). This stresses the substitution logic over the entire string and ensures the alignment is computed per character rather than based on sequence-level similarity. It's particularly useful for catching row/column inversion bugs or misaligned index accesses. The wrong_direction test uses longer, more complex strings ("AACAGTTACC" and "TAAGGTCA") to test whether the dynamic programming correctly finds the minimal path in a more realistic alignment scenario. It checks for both matches and mismatches in nontrivial positions, helping validate the full traceback logic in the alignment() method. The reversed_check test uses a short string where two internal characters are swapped ("ACGT" vs "AGCT"), leading to two substitutions. This test doesn't just check the cost but also verifies the ordering of operations in the alignment output. It does so by enforcing that specific lines (e.g. "C G 1", "G C 1") appear in the correct sequence. The min3 test is a brute-force validation of the min3 utility function. It loops through all small combinations of three integers from 0 to 3 and confirms that the function returns the true minimum. This protects against silent logic errors in one of the most fundamental helpers used in the DP computation. Finally, TestAlignmentHeadAndTail examines edge cases involving insertions or deletions at the start or end of the string. It confirms that the algorithm can correctly detect and represent gaps ("-") when characters are missing at the head ("TGCA" vs "GCA") or tail ("AC" vs "ACTG"). These tests are important because off-by-one errors are common in DP table tracebacks, especially near the edges.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

One of the main challenges I faced in this project was correctly reconstructing the alignment from the dynamic programming matrix. The edit distance computation itself was fairly straightforward once I set up the DP table, but tracing back the exact sequence of operations—especially making sure it correctly handled all edge cases like insertions and deletions at the start or end of the strings—took some trial and error. It was easy to make off-by-one mistakes or incorrectly choose which operation led to a specific cell in the table, which would mess up the final alignment output. To my knowledge everything works as intended to. I also learned how important initialization of the DP table is in dynamic programming. Forgetting to fill in the first row and column with the correct base costs led to completely wrong distance values initially. Once I understood how the base cases model empty string transformations, everything clicked.

## Analysis

### Example
Do one additional test case by hand. It should be constructed in such a way that you know the correct  output before running your program on it, and it should be a "corner case" that helps check if your program handles all special situations correctly. 

Please list:
Input string 1: CAT  
Input string 2: GCAT - a copy of the test case input
- G 2  
C C 0  
A A 0  
T T 0  - the expected test case output
Yes, the output matches exactly as the expected output - whether your program ran correctly on it or not
 - optionally, any other remarks

### Specs
Your Computer
Memory: 16 GB
Processors: M1 Pro, 10 core CPU, 16 core GPU

Partner's Computer
Memory: 16gb unified memory
Processors: M2 8 core CPU, 10 core GPU

### Runs
Fill in the table with the results of running your code on both your and your partner's computers.

| data file     | distance | memory (mb) | time (seconds) | partner time |
|---------------|----------|-------------|----------------|--------------|
|ecoli2500.txt  | 118      | 24.24       |  0.19577       | 0.00409 s    |
|ecoli5000.txt  | 160      | 96.08       |  0.778366      | 0.710403 s   |
|ecoli10000.txt | 223      | 382.6       |  3.10749       | 2.79187 s    |
|ecoli20000.txt | 3135     | 1530        |  12.2137       | 11.2702 s    |
|ecoli50000.txt | 19485    | 9930        |  78.9141       | 75.5377 s    |
|ecoli100000.txt| 24166    | 38180       |  335.078       | 319.98 s     |

Here is an example from another computer for some of the files.

| data file    | distance | time (s) |
|--------------|----------|----------|
|ecoli2500.txt |      118 |    0.171 |
|ecoli5000.txt |      160 |    0.529 |
|ecoli7000.txt |      194 |    0.990 |
|ecoli10000.txt|      223 |    1.972 |
|ecoli20000.txt|     3135 |    7.730 |

### Time
Assume the two strings are the same length (M = N).  By applying the doubling method to the data points that you obtained, estimate the running time of your program in seconds as a polynomial function of N, in the form a * N^b for some constants a and b.  Determine the largest input your program can handle if it is limited to one day of computation.

Provide a brief justification/explanation of how you applied the doubling method, and if you data seems not to work, describe what went wrong and use the sample data instead.
 - a = 3 x 10^-8
 - b = 2
 - largest N = 1,697,000

 ecoli50000.txt took around 75 seconds while ecoli1000000.txt too around 300 seconds. T(2N)/T(N) = 2^b, 300/75=4=2^2. Therefore b=2. So the time complexity seesm to be T(N) = aN^2. 75=a*50000^2, solving this gives a=3x10^-8. Now we need to find the largest N for 24 hrs, meaning T(N) = aN^2 <= 86,400 seconds. Solving this would give us N=1697000. We used the doubling method to estimate the exponent b bu comparing the runtimes for inputs of size N and 2N, then solved for a. This gave us a model that fits O(N^2). Using this we calculated the maximum N that fits within a 24-hour window.

### Memory
Assume the two strings are the same length (M = N).  Look at your code and determine how much memory it requires as a polynomial function of N, in the form a * N^b for some constants a and b.  Determine the largest input size your computer can handle if limited to 8GiB of RAM.
 - a = 4
 - b = 2
 - largest N = 46,340

 8GB gives us 8,589,934,592 bytes. We need 4N^2 <= 8,589,934,592, solving gives us the largest N. Each integer takes 4 bytes therefore a=4.

### Valgrind
Run valgrind and list any errors you see.  Identify whether the memory usage reported by valgrind almost matches the calculations in the previous section.

| data file     | Calculated (mb) | Measured (mb) | Difference (%) |
|---------------|-----------------|---------------|----------------|
|ecoli2500.txt  |   24.24         |  24.24        |  0             |
|ecoli5000.txt  |   96.08         |  96.08        |  0             |
|ecoli10000.txt |   382.6         |  382.6        |  0             |
|ecoli20000.txt |   1492          |  1492         |  0             |
|ecoli50000.txt |   1445.3        |  N/A          |  killed        |
|ecoli100000.txt|   2225.7        |  N/A          |  killed        |(did not run on valgrind)

## Pair Programming
If you worked with a partner, do you have any remarks on the pair programming method? E.g., how many times did you switch, what are the tradeoffs of driving vs. navigating, etc.?

I think working with a partner was like a cheat code. It makes thing much more faster and easier to do than doing it alone. Even when debugging, having someone else looking at the code with fresh eyes helps. Sometimes one of us would be stuck on a silly off-by-one error or a missing base case, and the other would catch it in seconds. We switched from coding to navigating and vice verse every 30-40 mins.

## Extra Credit
Anything special you did.  This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

DP matrix: https://stackoverflow.com/questions/15390832/dynamic-programming-and-the-use-of-matrices