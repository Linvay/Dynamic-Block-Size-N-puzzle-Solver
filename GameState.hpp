#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>

struct Coordinate
{
    int y = 0;
    int x = 0;
    Coordinate(const int y, const int x):y(y), x(x) {}
    Coordinate operator+(const Coordinate &rhs) const
    {
        return Coordinate(y + rhs.y, x + rhs.x);
    }
    Coordinate operator-(const Coordinate &rhs) const
    {
        return Coordinate(y - rhs.y, x - rhs.x);
    }
    bool operator==(const Coordinate &rhs) const
    {
        return (y == rhs.y && x == rhs.x);
    }
    bool operator!=(const Coordinate &rhs) const
    {
        return (y != rhs.y || x != rhs.x);
    }
    size_t Manhattan(const Coordinate &dest) const
    {
        return std::abs(dest.y - y) + std::abs(dest.x - x);
    }
};

const std::vector<Coordinate> directions = {Coordinate(-1, 0), 
                                            Coordinate(0, 1),
                                            Coordinate(1, 0),
                                            Coordinate(0, -1)};

struct Piece
{
    Piece(const int index, const int y, const int x, const int width, const int height)
        :index(index), width(width), height(height), position(Coordinate(y, x)) {}
    Coordinate position;
    int index;
    int width;
    int height;
    bool operator==(const Piece &rhs) const
    {
        return (index == rhs.index &&
                width == rhs.width &&
                height == rhs.height &&
                position == rhs.position);
    }
    bool operator!=(const Piece &rhs) const
    {
        return (index != rhs.index ||
                width != rhs.width ||
                height != rhs.height ||
                position != rhs.position);
    }
};

class GameState
{
public:
    GameState(const std::vector<std::vector<int>> &board);
    static bool SetGameInfo(const std::vector<std::vector<int>> &init_board);
    // static void DisplayGameInfo();
    void DisplayBoard() const;
    std::vector<GameState> GetNextStates() const;
    bool operator== (const GameState &rhs) const;
    bool operator!= (const GameState &rhs) const;
    std::vector<std::vector<int>> Board() { return mBoard; }
    std::vector<Piece> Pieces() const { return mPieces; }
    std::vector<std::string> MoveHistory() const { return mMoveHistory; }
    std::vector<std::string> & MoveHistory() { return mMoveHistory; }
    static GameState InitialBoard() { return msInitialBoard; }
    static GameState FinalBoard() { return msFinalBoard; }
    int Heuristic() const;
    int G() const { return mG; }
    int & G() { return mG; }
protected:
    void MovePiece(const Piece &piece, const Coordinate &dest);
private:
    static GameState msInitialBoard;
    static GameState msFinalBoard;
    static size_t msBoardWidth;
    static size_t msBoardHeight;
    std::vector<std::vector<int>> mBoard;
    std::vector<Piece> mPieces;
    std::vector<std::string> mMoveHistory = std::vector<std::string>();
    int mG = 0;
    bool CanPieceFit(const Piece &piece, const Coordinate &dest) const;
    static bool CanPieceFit(const Piece &piece, const std::vector<std::vector<int>> &board, const Coordinate &dest);
    static void MovePiece(const Piece &piece, std::vector<std::vector<int>> &board, const Coordinate &dest);
};

#endif