#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <chrono>

#include "GameState.hpp"
#include "GameGraph.hpp"

int main(int argc, char *argv[])
{
    std::string fname_input = "input.txt";
    std::cout << "Please enter the input file file-path: ";
    std::cin >> fname_input;

    std::fstream inputFile;
    inputFile.open(fname_input, std::ios::in);
    if (!inputFile.is_open())
    {
        std::cerr << "Error when opening the file: " << fname_input << std::endl;
        std::exit(0);
    }

    std::string fname_output = "output.txt";
    std::cout << "Please enter the output file file-path: ";
    std::cin >> fname_output;

    std::fstream outputFile;
    outputFile.open(fname_output, std::ios::out);
    if (!outputFile.is_open())
    {
        std::cerr << "Error when opening the file: " << fname_output << std::endl;
        std::exit(0);
    }

    int case_cnt = 0;
    while (true)
    {
        case_cnt += 1;
        std::cout << "==================" << std::endl;
        std::cout << "Case " << case_cnt << std::endl;
        std::cout << "==================" << std::endl;

        int row = 0;
        int col = 0;
        inputFile >> row >> col; inputFile.ignore();

        std::vector<std::vector<int>> initialBoard;
        for (int i = 0; i < row; ++i)
        {
            int val = 0;
            initialBoard.push_back(std::vector<int>());
            for (int j = 0; j < col; ++j)
            {
                inputFile >> val;
                initialBoard[i].push_back(val);
            }
        }

        GameState::SetGameInfo(initialBoard);
        std::cout << "===Initial Board===" << std::endl;
        GameState::InitialBoard().DisplayBoard();
        std::cout << "===Final Board===" << std::endl;
        GameState::FinalBoard().DisplayBoard();

        GameGraph graph;
        for (int i = 0; i < argc; ++i)
        {
            if (strcmp(argv[i], "t") == 0)
            {
                graph.ShowTime = true;
            }
        }

        /* IDDFS */
        auto start = std::chrono::high_resolution_clock::now();
        bool isSearchSuccess = graph.IDDFS(GameState::InitialBoard(), GameState::FinalBoard(), 30);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
        std::cout << "===Result: IDS===" << std::endl;
        if (isSearchSuccess)
        {
            std::cout << "Total run time = " + std::to_string(duration.count()) << " seconds." << std::endl;
            outputFile << "Total run time = " + std::to_string(duration.count()) << " seconds." << std::endl;
            if (graph.Solution().size() == 1)
                std::cout << "An optimal solution has " + std::to_string(graph.Solution().size()) << " move:" << std::endl;
            else
                std::cout << "An optimal solution has " + std::to_string(graph.Solution().size()) << " moves:" << std::endl;
            outputFile << "An optimal solution has " + std::to_string(graph.Solution().size()) << " moves:" << std::endl;
            
            for (size_t i = 0; i < graph.Solution().size(); ++i)
            {
                std::cout << graph.Solution()[i] << " ";
                outputFile << graph.Solution()[i] << " ";
            }
            std::cout << std::endl;
            outputFile << std::endl;
        }
        else
        {
            std::cout << "no solution" << std::endl;
            outputFile << "no solution" << std::endl;
        }

        if (inputFile.eof())
            break;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}