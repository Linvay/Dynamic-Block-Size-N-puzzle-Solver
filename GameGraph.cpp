#include "GameGraph.hpp"

/* Recursive Depth-Limited Search */
bool GameGraph::DLS(const GameState &node, const GameState &target, const int limit, std::vector<GameState> visited_nodes)
{
    if (node == target)
    {
        mSolution = node.MoveHistory();
        return true;
    }

    // If reached the maximum depth, stop recursing.
    if (limit <= 0)
    {
        if (node.GetNextStates().size())
            mHasRemain = true;
        return false;
    }

    // Recurse for all the nodes adjacent to the source node.
    std::vector<GameState> next_nodes = node.GetNextStates();
    for (GameState &node : next_nodes)
    {
        // prevent traversing the same node
        if (std::find(visited_nodes.begin(), visited_nodes.end(), node) == visited_nodes.end())
        {
            visited_nodes.push_back(node);
            if (DLS(node, target, limit-1, visited_nodes) == true)
            {
                return true;
            }
            visited_nodes.pop_back();
        }
    }

    return false;
}

/* Iterative Deepening Depth-First Search */
bool GameGraph::IDDFS(const GameState &source_node, const GameState &target, const int max_depth)
{
    mSolution.clear();
    mHasRemain = false;
    
    // search until depth limit is reached
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i <= max_depth; ++i)
    {
        std::vector<GameState> visited_nodes = {source_node};
        if (DLS(source_node, target, i, visited_nodes) == true)
        {
            return true;
        }

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
        if (ShowTime)
            std::cout << "Depth " << i << ": total runtime = " << duration.count() << " seconds." << std:: endl; 

        if (mHasRemain == false)
            break;
    }

    return false;
}

/* Iterative Deepening A* */
bool GameGraph::IDAStar(const GameState &source_node, const GameState &target)
{
    size_t limit = source_node.Heuristic();
    mSolution.clear();

    auto start = std::chrono::high_resolution_clock::now();
    while (true)
    {
        std::vector<GameState> visited_nodes = {source_node};
        size_t fscore = Search(source_node, target, limit, visited_nodes);
        if (fscore == FOUND)
            return true;
        if (fscore == INF)   // no more node to traverse, board has no solution
            return false;
        limit = fscore;

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);
        if (ShowTime)
            std::cout << "Limit " << limit << ": total runtime = " << duration.count() << " seconds." << std:: endl;
    }
}

/* Recursive search for IDA* */
size_t GameGraph::Search(const GameState &node, const GameState &target, const int limit, std::vector<GameState> visited_nodes)
{
    int f = node.Heuristic() + node.G();

    // if fscore is beyond limit, end search
    if (f > limit)
    {
        return f;
    }
    
    // if finial board is found, return success
    if (node == target)
    {
        mSolution = node.MoveHistory();
        return FOUND;
    }
    
    int min_fscore = INF;
    for (GameState next_node : node.GetNextStates())
    {
        // prevent traversing the same node
        if (std::find(visited_nodes.begin(), visited_nodes.end(), next_node) == visited_nodes.end())
        {
            visited_nodes.push_back(node);
            int fscore = Search(next_node, target, limit, visited_nodes);
            if (fscore == FOUND)
                return FOUND;
            if (fscore < min_fscore)
                min_fscore = fscore;
            visited_nodes.pop_back();
        }
    }

    // if final board is not found, update the limit
    return min_fscore;
}