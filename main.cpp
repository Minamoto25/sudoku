#include "sudoku.h"

int main(){
    Generator generator(9);
    auto boards = generator.generate(5);
    for(auto board : boards){
        printBoard(board);
    }
    ProblemMaker pro(30, 50, 5, boards);
    auto problems = pro.makeProblems();
    for(auto problem : problems){
        printBoard(problem);
        Solver solv(problem);
        solv.solve();
        auto solutions = solv.getSolutions();
        std::cout << "level: " << solv.getLevel() << std::endl;
        for(auto solution : solutions){
            printBoard(solution);
        }
    }
    return 0;
}