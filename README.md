# sudoku
A toy sudoku for pair programming practice
# How to build
```shell
cmake -B build
cmake --build build
```
To run the programm:
```shell
./build/Debug/sudoku.exe
```
if you have g++ installed, you can also run:
```shell
g++ -o sudoku.exe main.cpp sudoku.cpp helper.cpp getopt.cpp & ./sudoku.exe
```