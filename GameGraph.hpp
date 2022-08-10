#ifndef GAMEGRAPH_HPP
#define GAMEGRAPH_HPP

#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <algorithm>
#include <chrono>
#include "GameState.hpp"

class GameGraph
{
public:
    GameGraph() {};
    bool IDDFS(const GameState &node, const GameState &target, const int max_depth);
    bool IDAStar(const GameState &start_node, const GameState &target);
    std::vector<std::string> Solution() const { return mSolution; }
    bool ShowTime = false;
private:
    bool DLS(const GameState &node, const GameState &target, const int limit, std::vector<GameState> visited_nodes);
    size_t Search(const GameState &node, const GameState & target, const int limit, std::vector<GameState> visited_nodes);
    std::vector<std::string> mSolution = std::vector<std::string>();
    const int FOUND = -1;
    const int INF = INT32_MAX;
    bool mHasRemain = false;
};

#endif