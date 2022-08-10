# Sliding-Puzzle-Solver
A C++ application that solves n-puzzles of which the blocks can be of various sizes of rectangles, using iterative deepening search (IDS) algorithm and iterative A* algorithm (IDA*).

This project is inspired by [the project of madweasel](https://github.com/madweasel/Traga-2)

<div align="center">
  <img src="https://user-images.githubusercontent.com/63941955/183853048-44e6a847-9233-4aca-a94a-5048922707a5.png" width=300 height=250></img>
</div>

## Build

Use `make` to compile all the .cpp files and generate the executables

## Program Execution

Run `.\main_IDS` and `.\main_IDAStar` to solve the puzzle with IDS and IDA*,  respectively.  
Run `.\main_IDS t` or `.\main_IDAStar t` for additional information about the total runtime of the search

## Input Format

The program would require you to give the initial board of the sliding puzzle.  
You should prepare a text file as input, the format is as follows:

For each test case:  
- The first line would be 2 integers, indicating the number of **rows** and **columns** of the board
- The following lines would be the layout of the borad, each sliding is represented with an index, starting from 1. The piece has to be a rectangle

see `input.txt` for an example input

<div align="center">
<img src="https://user-images.githubusercontent.com/63941955/183859679-716d7743-2d39-4d7d-abf0-fb06d109cd1d.png"></img>
</div>
