/*Copyright 2023 Ma Jiangyuan & FengChaopeng*/
#include "include/sudoku.h"

#include <algorithm>

#include "include/helper.h"

std::random_device rd;
std::mt19937 gen = std::mt19937(rd());

std::vector<int> Generator::genRow() {
  std::vector<int> row;
  for (size_t i = 0; i < size; i++) {
    row.push_back(static_cast<int>(i) + 1);
  }
  std::string row_string;
  std::shuffle(row.begin(), row.end(), gen);
  return row;
}

bool Generator::genOne(int row, int col) {
  if (row == size) {
    return true;
  }
  if (col == size) {
    return genOne(row + 1, 0);
  }
  std::vector<int> nums;
  for (size_t i = 1; i <= size; i++) {
    nums.push_back(static_cast<int>(i));
  }
  std::shuffle(nums.begin(), nums.end(), gen);
  for (auto num : nums) {
    if (isValid(one_board, row, col, num)) {
      one_board[row][col] = num;
      if (genOne(row, col + 1)) {
        return true;
      }
      one_board[row][col] = 0;
    }
  }
  return false;
}

std::vector<Board> Generator::generate(unsigned cnt) {
  std::vector<Board> boards;
  while (true) {
    std::vector<int> row = genRow();
    one_board = Board(size, std::vector<int>(size, 0));
    one_board[0] = row;
    while (!genOne(1, 0)) {
    }
    std::string board_string;
    for (auto row : one_board) {
      for (auto num : row) {
        board_string += std::to_string(num) + "";
      }
    }
    if (board_history.find(board_string) != board_history.end()) {
      continue;
    }
    boards.push_back(one_board);
    cnt--;
    if (!cnt) break;
  }
  return boards;
}

Board ProblemMaker::makeProblem() {
  size_t size = boards[0][0].size();
  int board_index = std::uniform_int_distribution<int>(
      0, static_cast<int>(boards.size()) - 1)(gen);
  Board board = boards[board_index];
  std::vector<int> row_index(size * size);
  for (size_t i = 0; i < size * size; i++) {
    row_index[i] = static_cast<int>(i);
  }
  std::shuffle(row_index.begin(), row_index.end(), gen);
  int empty_cnt = std::uniform_int_distribution<int>(min_empty, max_empty)(gen);
  for (int i = 0; i < empty_cnt; i++) {
    int row = row_index[i] / static_cast<int>(size);
    int col = row_index[i] % static_cast<int>(size);
    board[row][col] = 0;
  }
  std::string board_string;
  for (auto row : board) {
    for (auto num : row) {
      board_string += std::to_string(num) + " ";
    }
  }
  return board;
}

bool Solver::dfs(int row, int col) {
  if (row == board.size()) {
    solutions.push_back(board);
    return true;
  }
  if (col == board.size()) {
    return dfs(row + 1, 0);
  }
  if (board[row][col] != 0) {
    return dfs(row, col + 1);
  }
  for (size_t i = 1; i <= board.size(); i++) {
    if (isValid(board, row, col, static_cast<int>(i))) {
      board[row][col] = static_cast<int>(i);
      bool res = dfs(row, col + 1);
      if (!res) try_sum += 1;
      board[row][col] = 0;
    }
  }
  return false;
}

void Solver::solve() { dfs(0, 0); }
