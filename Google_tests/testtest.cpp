//
// Created by 'Confidence'F on 6/26/2023.
//
#include <fstream>
#include "gtest/gtest.h"
#include "../include/sudoku.h"
#include "../include/helper.h"

TEST(GeneratorTest, GenerateValidSudokuBoard) {
    Generator generator(9);
    auto boards = generator.generate(1);
    ProblemMaker problem_maker(20, 55, boards);
    Board problem = problem_maker.makeProblem();
    EXPECT_TRUE(isValidSudoku(problem, 9));
}

TEST(GeneratorTest, GenerateDifferentSudokuBoard) {
    Generator generator(9);
    auto board1 = generator.generate(1);
    auto board2 = generator.generate(1);
    EXPECT_FALSE(board1[0] == board2[0]);
}

TEST(GeneratorTest, TestGenOne) {
    Generator generator(9);
    Board problem(9,std::vector<int>(9,0));
    generator.one_board = problem;
    generator.one_board[0] = {6,8,1,2,3,9,7,4,5};
    EXPECT_TRUE(generator.genOne(1, 0));
}

TEST(GeneratorTest, TestCannotGenOne) {
    Generator generator(9);
    Board problem(9,std::vector<int>(9,0));
    generator.one_board = problem;
    generator.one_board[0] = {1,1,1,1,1,1,1,1,1};
    EXPECT_FALSE(generator.genOne(1, 0));
}

TEST(SolverTest, ValidSudokuBoard) {
    std::ifstream in("problems.txt");
    BoardReader reader(in);
    reader();
    in.close();
    EXPECT_TRUE(isValidSudoku(reader.board, 9));
}

TEST(SolverTest, InvalidSudokuBoard) {
    Board board = { {0, 0, 0} };
    EXPECT_FALSE(isValidSudoku(board, 9));
}

TEST(SolverTest, SolveValidSudokuBoard) {
    std::ifstream in("problems.txt");
    BoardReader reader(in);
    reader();
    in.close();

    Solver solver(reader.board);
    solver.solve();
    auto solutions = solver.getSolutions();
    EXPECT_TRUE(solutions.size() >= 1);
}

TEST(SolverTest, ValidStepValidation) {
    Board problem = {{6,0,0,0,0,9,7,4,0},
                     {5,0,0,6,4,1,0,3,0},
                     {0,0,3,0,7,5,0,0,6},
                     {4,1,8,0,6,0,0,9,7},
                     {9,0,5,1,0,3,6,2,4},
                     {0,3,6,7,9,4,1,5,0},
                     {0,5,0,0,1,8,4,6,0},
                     {3,0,9,4,5,0,2,7,1},
                     {0,6,0,9,0,0,8,3,0}};
    Solver solver(problem);
    EXPECT_TRUE(isValid(problem, 0, 1, 2));
}

TEST(SolverTest, InvalidStepValidation) {
    Board problem = {{6,0,0,0,0,9,7,4,0},
                     {5,0,0,6,4,1,0,3,0},
                     {0,0,3,0,7,5,0,0,6},
                     {4,1,8,0,6,0,0,9,7},
                     {9,0,5,1,0,3,6,2,4},
                     {0,3,6,7,9,4,1,5,0},
                     {0,5,0,0,1,8,4,6,0},
                     {3,0,9,4,5,0,2,7,1},
                     {0,6,0,9,0,0,8,3,0}};
    Solver solver(problem);
    EXPECT_FALSE(isValid(problem, 0, 1, 1));
}

TEST(ProblemMakerTest, MakeValidSudokuProblem) {
    std::ifstream in("final_boards.txt");
    std::vector<Board> solution;
    BoardReader reader(in);
    reader();
    solution.push_back(reader.board);
    in.close();

    ProblemMaker problem_maker(20, 55, solution);
    Board problem = problem_maker.makeProblem();
    EXPECT_TRUE(isValidSudoku(problem, 9));
}

TEST(ProblemMakerTest, MakeDifferentSudokuProblem) {
    std::ifstream in("final_boards.txt");
    std::vector<Board> solution;
    BoardReader reader(in);
    reader();
    solution.push_back(reader.board);
    in.close();

    bool have_diff = false;
    int cnt = 100;
    while(cnt > 0) {
        ProblemMaker problem_maker(20, 55, solution);
        Board problem = problem_maker.makeProblem();

        Solver solver(problem);
        solver.solve();
        auto solutions = solver.getSolutions();

        cnt--;
        if(solutions.size() > 1){
            have_diff = true;
            break;
        }
    }

    EXPECT_TRUE(have_diff);
}

