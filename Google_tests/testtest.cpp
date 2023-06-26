//
// Created by 'Confidence'F on 6/26/2023.
//
#include <fstream>
#include "gtest/gtest.h"
#include "../sudoku.h"
#include "../helper.h"

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

TEST(SolverTest, ValidSudokuBoard) {
    std::ifstream in("problems.txt");
    Board problem(9,std::vector<int>(9,0));
    readBoard(problem,in);
    in.close();
    EXPECT_TRUE(isValidSudoku(problem, 9));
}

TEST(SolverTest, InvalidSudokuBoard) {
    Board board = { {0, 0, 0} };
    EXPECT_FALSE(isValidSudoku(board, 9));
}

TEST(SolverTest, SolveValidSudokuBoard) {
    std::ifstream in("problems.txt");
    Board problem(9,std::vector<int>(9,0));
    readBoard(problem,in);
    in.close();

    //printBoard(problem);

    Solver solver(problem);
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
    EXPECT_TRUE(solver.isValid(problem, 0, 1, 2));
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
    EXPECT_FALSE(solver.isValid(problem, 0, 1, 1));
}

TEST(ProblemMakerTest, MakeValidSudokuProblem) {
    std::ifstream in("final_boards.txt");
    std::vector<Board> solution;
    Board board(9,std::vector<int>(9,0));
    readBoard(board,in);
    solution.push_back(board);
    in.close();

    ProblemMaker problem_maker(20, 55, solution);
    Board problem = problem_maker.makeProblem();
    EXPECT_TRUE(isValidSudoku(problem, 9));
}

TEST(ProblemMakerTest, MakeDifferentSudokuProblem) {
    std::ifstream in("final_boards.txt");
    std::vector<Board> solution;
    Board board(9,std::vector<int>(9,0));
    readBoard(board,in);
    solution.push_back(board);
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

