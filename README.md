# Square sum problem
Inspired by [Numberphile](https://www.youtube.com/watch?v=G1m7goLCJDY)

This is my try at solving the Square-Sum Problem. It checks whether is it possible to rearrange the sequence of numbers 1..n such way that the sum of any two sequential numbers is a perfect square.

**Implementation:** Backtracking

**Performance improvements made:**
1. All the pairs of numbers that can form a perfect square are computed before the algorithm starts searching for a path
2. All the numbers are sorted ascendant by the number of edges (this was done because i found it more plausible for a valid path to start with a vertex that has the minimum number of edges from all).

The code is a mess, but it works well and has a reasonable execution time.

### Compile:
    1. git clone https://github.com/x4204/the_square_sum_problem.git square_sum_problem
    2. cd square_sum_problem
    3. make
    4. ./square_sum_problem <N>


Any suggestions on how to make it run faster are welcome.
