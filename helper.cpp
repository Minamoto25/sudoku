/*Copyright 2023 Ma Jiangyuan & FengChaopeng*/
#include "include/helper.h"

#include <stdio.h>
#include <string.h>

#include <fstream>


void printBoard(const Board& board) {
  for (auto row : board) {
    for (auto num : row) {
      if (num != 0)
        std::cout << num << " ";
      else
        std::cout << "$ ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

std::string args_checker(const Args& args) {
  std::string error_msg;
  // if no arg specified, print usage
  if (!args.final_boards_cnt && !args.games_cnt &&
      args.problem_input_path == "" && !args.game_level && !args.min_empty &&
      !args.max_empty && !args.unique) {
    error_msg =
        "Usage: ./sudoku -c final_boards_cnt -s problem_input_path -n "
        "games_cnt -m game_level -r min_empty~max_empty -u unique";
  } else if (!args.games_cnt &&
             ((args.game_level != 0) | (args.min_empty != 0) |
              (args.max_empty != 0) | args.unique)) {
    error_msg = "Error: -n must be specified when -m, -r or -u is specified";
  } else if (args.min_empty && args.min_empty < 20 ||
             args.max_empty && args.max_empty > 55) {  // arg range check
    error_msg = "Error: number of empty cells must be between 20~55";
  } else if (args.min_empty && args.max_empty &&
             args.min_empty > args.max_empty) {
    error_msg = "Error: args.min_empty must be smaller than args.max_empty";
  } else if (args.final_boards_cnt &&
             (args.final_boards_cnt < 1 || args.final_boards_cnt > 1000000)) {
    error_msg = "Error: number of final boards must be between 1~1000000";
  } else if (args.problem_input_path != "") {
    std::ifstream in(args.problem_input_path);
    if (!in) {
      error_msg = "Error: problem input file does not exist";
    }
  } else if (args.games_cnt && (args.games_cnt < 1 || args.games_cnt > 10000)) {
    error_msg = "Error: number of games must be between 1~10000";
  } else if (args.game_level && (args.game_level < 1 || args.game_level > 3)) {
    error_msg = "Error: game level must be between 1~3";
  }
  return error_msg;
}
bool isValid(const Board& board, int row, int col, int num) {
  // check row
  for (size_t i = 0; i < board.size(); i++) {
    if (board[row][i] == num) {
      return false;
    }
  }
  // check col
  for (size_t i = 0; i < board.size(); i++) {
    if (board[i][col] == num) {
      return false;
    }
  }
  // check block
  size_t block_size = static_cast<size_t>(sqrt(board.size()));
  size_t block_row = row / block_size;
  size_t block_col = col / block_size;
  for (size_t i = block_row * block_size; i < (block_row + 1) * block_size;
       i++) {
    for (size_t j = block_col * block_size; j < (block_col + 1) * block_size;
         j++) {
      if (board[i][j] == num) {
        return false;
      }
    }
  }
  return true;
}
void BoardDumper::operator()(const Board& board) {
  for (auto row : board) {
    for (auto num : row) {
      if (num != 0)
        os << num << " ";
      else
        os << "$ ";
    }
    os << std::endl;
  }
  os << std::endl;
}

bool BoardReader::operator()() {
  for (auto& row : board) {
    for (auto& num : row) {
      char c;
      is >> c;
      if (!c) return false;
      if (c == '$')
        num = 0;
      else
        num = c - '0';
    }
  }
  return true;
}

bool checkRange(std::string str) {
  // check if optarg is of form "min~max"
  // if so, return true and store min and max in args
  // return false otherwise
  if (!strchr(str.c_str(), '~')) return false;
  for (auto c : str) {
    if (!isdigit(c) && c != '~') return false;
  }
  return true;
}
