/*Copyright 2023 Ma Jiangyuan & FengZhaopeng*/
#include <string.h>

#include <fstream>

#include "include/getopt.h"
#include "include/helper.h"
#include "include/sudoku.h"

int main(int argc, char* argv[]) {
  // parse arguments
  Args args{};
  // memset(&args, 0, sizeof(args));
  int opt;
  std::string error_msg;
  while ((opt = getopt(argc, argv, "c:s:n:m:r:u")) != -1) {
    switch (opt) {
      case 'c':
        args.final_boards_cnt = std::stoi(optarg);
        break;
      case 's':
        args.problem_input_path = optarg;
        break;
      case 'n':
        args.games_cnt = std::stoi(optarg);
        break;
      case 'm':
        args.game_level = std::stoi(optarg);
        break;
      case 'r':
        if (!checkRange(optarg)) {
          error_msg = "bad empty cells range, should be of form min~max\n";
          break;
        }
        // range of empty cells, of form "min~max"
        args.min_empty = std::stoi(optarg);
        args.max_empty = std::stoi(strchr(optarg, '~') + 1);
        break;
      case 'u':
        args.unique = true;
        break;
      default:
        return 1;
    }
  }
  if (args.games_cnt) {
    // default values:
    if (!args.game_level) args.game_level = 2;
    if (!args.min_empty) args.min_empty = 20;
    if (!args.max_empty) args.max_empty = 55;
  }
  error_msg = args_checker(args);
  if (error_msg != "") {
    std::cout << error_msg << std::endl;
    return 1;
  }
  // generate final boards
  if (args.final_boards_cnt) {
    Generator generator(9);
    auto boards = generator.generate(args.final_boards_cnt);
    std::ofstream of("final_boards.txt", std::ios::out);
    BoardDumper dumper(of);
    for (auto board : boards) {
      dumper(board);
    }
    of.close();
  }
  // generate problems
  if (args.games_cnt) {
    std::ifstream in("final_boards.txt");
    std::vector<Board> boards;
    BoardReader reader(in);
    // while(!in.eof()){ not work, keep returning 0 when hit eof
    while (reader()) {
      boards.push_back(reader.board);
    }
    in.close();
    ProblemMaker pro(args.min_empty, args.max_empty, boards);
    std::vector<Board> final_problems;
    while (true) {
      Board problem = pro.makeProblem();
      Solver solv(problem);
      solv.solve();
      if (args.unique && solv.getSolutions().size() != 1) {
        continue;
      }
      if (args.game_level && solv.getLevel() != args.game_level) {
        continue;
      }
      final_problems.push_back(problem);
      std::cout << "generated " << final_problems.size() << " problems\n";
      if (final_problems.size() == args.games_cnt) {
        break;
      }
    }
    std::ofstream of("problems.txt", std::ios::out);
    BoardDumper dumper(of);
    for (auto problem : final_problems) {
      dumper(problem);
    }
  }
  // solve problems
  if (args.problem_input_path != "") {
    std::ifstream in(args.problem_input_path);
    std::vector<Board> problems;
    BoardReader readBoard(in);
    while (readBoard()) {
      problems.push_back(readBoard.board);
    }
    in.close();
    std::ofstream of("sudoku.txt", std::ios::out);
    BoardDumper writeBoard(of);
    for (auto problem : problems) {
      Solver solv(problem);
      solv.solve();
      auto solutions = solv.getSolutions();
      char msg[100];
      // should not use sprintf, use snprintf instead
      // sprintf(msg, "there are %d solutions\n", solutions.size());
      snprintf(msg, sizeof(msg), "there are %zd solutions\n", solutions.size());
      of << msg;
      for (auto solution : solutions) {
        writeBoard(solution);
      }
    }
  }
}
