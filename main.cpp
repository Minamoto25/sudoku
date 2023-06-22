#include "sudoku.h"

int main(){
    Generator generator(9);
    auto boards = generator.generate(100);
    for(auto board : boards){
        printBoard(board);
    }
    return 0;
}