/*Copyright 2023 Ma Jiangyuan & FengChaopeng*/
#ifndef INCLUDE_SUDOKU_H_
#define INCLUDE_SUDOKU_H_
#include <cstdint>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>


typedef std::vector<std::vector<int>> Board;

class Generator {
 private:
  //Board one_board;
  unsigned size;  // generally, size should be 9, but you can try other sizes of
                  // square
  std::unordered_map<std::string, int> board_history;
  std::vector<int> genRow();
  // bool genOne(int row, int col);

 public:
  Board one_board;
  explicit Generator(unsigned n) : size(n) {}
  std::vector<Board> generate(unsigned cnt);
  bool genOne(int row, int col);
};

class ProblemMaker {
  std::unordered_map<std::string, int> board_history;
  const std::vector<Board>& boards;

 public:
  int min_empty, max_empty;
  ProblemMaker(int min_empty, int max_empty, const std::vector<Board>& boards)
      : min_empty(min_empty), max_empty(max_empty), boards(boards) {}
  Board makeProblem();
};

class Solver {
 private:
  Board board;
  uint64_t try_sum = 0;
  std::vector<Board> solutions;
  bool dfs(int row, int col);
  std::unordered_map<std::string, int> board_history;
 public:
  explicit Solver(const Board& board) : board(board) {}
  void solve();
  int getLevel() const {
    if (try_sum < 100)
      return 1;
    else if (try_sum < 1000)
      return 2;
    else
      return 3;
  }
  const std::vector<Board>& getSolutions() const { return solutions; }
};
#endif  // INCLUDE_SUDOKU_H_
