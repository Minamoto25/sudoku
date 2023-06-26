//
// Created by 'Confidence'F on 6/26/2023.
//
#include "gtest/gtest.h"
#include "../sudoku.h"

//TEST(GeneratorTest, GenerateValidSudokuBoard) {
//    Generator generator(9);
//    auto boards = generator.generate(1);
//    EXPECT_TRUE(boards.isValid());
//}

TEST(GeneratorTest, GenerateDifferentSudokuBoard) {
    Generator generator(9);
    auto board1 = generator.generate(1);
    auto board2 = generator.generate(1);
    EXPECT_FALSE(board1[0] == board2[0]);
}