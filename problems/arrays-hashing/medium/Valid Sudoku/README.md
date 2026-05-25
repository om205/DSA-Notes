# Valid Sudoku

- Difficulty: Medium
- Topic: Array, Hash Table, Matrix
- Platform: LeetCode
- Link: https://leetcode.com/problems/valid-sudoku/

---

## Problem Statement

Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to three rules: each row must contain digits 1-9 without repetition, each column must contain digits 1-9 without repetition, and each of the nine 3x3 sub-boxes must contain digits 1-9 without repetition. A partially filled Sudoku board is given, where '.' represents empty cells which do not need validation.

---

## Examples

### Example 1

```txt
Input: board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]

Output: true
```

Explanation: The given board is valid according to the Sudoku rules.

### Example 2

```txt
Input: board = [["8","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]

Output: false
```

Explanation: The '8' in the top left 3x3 sub-box appears twice (at (0,0) and (3,0), which are within the same sub-box at (0,0)). Therefore, it is invalid.

---

## Constraints

- `board.length == 9`
- `board[i].length == 9`
- `board[i][j] is a digit ('1'-'9') or '.'.`
---

## Intuition

Used bitmasking to save space and created three arrays to store rows, columns and square so that we do not need to traverse more than once.

---


## Takeaways



## C++ Concepts

-
