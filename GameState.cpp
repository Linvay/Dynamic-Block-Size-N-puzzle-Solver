#include "GameState.hpp"

GameState GameState::msInitialBoard = GameState(std::vector<std::vector<int>>());
GameState GameState::msFinalBoard = GameState(std::vector<std::vector<int>>());
size_t GameState::msBoardWidth = 0;
size_t GameState::msBoardHeight = 0;

bool GameState::operator== (const GameState &rhs) const
{
    for (int i = 0; i < mPieces.size(); ++i)
    {
        if (mPieces[i] != rhs.Pieces()[i])
            return false;
    }
    return true;
}

bool GameState::operator!= (const GameState &rhs) const
{
    for (int i = 0; i < mPieces.size(); ++i)
    {
        if (mPieces[i] != rhs.Pieces()[i])
            return true;
    }
    return false;
}

GameState::GameState(const std::vector<std::vector<int>> &board)
{
    mBoard = board;

    /* Scan through board to get all the pieces */
    std::map<int, std::vector<Coordinate>, std::less<int>> piece_pos = std::map<int, std::vector<Coordinate>>();
    for (size_t row = 0; row < board.size(); ++row)
    {
        for (size_t col = 0; col < board[0].size(); ++col)
        {
            int index = board[row][col];
            if (index == 0)
                continue;
            if (piece_pos.find(index) != piece_pos.end())
            {
                piece_pos[index].push_back(Coordinate(row, col));
            }
            else
            {
                std::vector<Coordinate> pos_stack = {Coordinate(row, col)};
                piece_pos.insert({index, pos_stack});
            }
        }
    }

    /* Initialize piece list */
    std::map<int, std::vector<Coordinate>>::iterator it;
    for (it = piece_pos.begin(); it != piece_pos.end(); ++it)
    {
        int index = it->first;
        int y = it->second[0].y;
        int x = it->second[0].x;
        int width = it->second.back().x - x + 1;
        int height = it->second.back().y - y + 1;
        mPieces.push_back(Piece(index, y, x, width, height));
    }
}

/* Initialize initial board and generating final board */
bool GameState::SetGameInfo(const std::vector<std::vector<int>> &init_board)
{
    GameState::msBoardHeight = init_board.size();
    GameState::msBoardWidth = init_board[0].size();
    GameState::msInitialBoard = GameState(init_board);
    std::vector<Piece> pieces = GameState::msInitialBoard.Pieces();

    /* Generate the final board */
    bool isPiecePlaced = false;
    std::vector<std::vector<int>> final_board(msBoardHeight, std::vector<int>(msBoardWidth, 0));
    for (int idx = 0; idx < pieces.size(); idx++)
    {
        isPiecePlaced = false;

        for (int row = 0; row < GameState::msBoardHeight; ++row)
        {
            for (int col = 0; col < GameState::msBoardWidth; ++col)
            {
                int index = final_board[row][col];
                Piece &cur_piece = pieces[idx];
                if (GameState::CanPieceFit(cur_piece, final_board, Coordinate(row, col)))
                {
                    for (int i = 0; i < cur_piece.height; ++i)
                    {
                        for (int j = 0; j < cur_piece.width; ++j)
                        {
                            final_board[row+i][col+j] = cur_piece.index;
                        }
                    }
                    isPiecePlaced = true;
                }

                if (isPiecePlaced)
                    break;
            }

            if (isPiecePlaced)
                break;
        }
    }

    GameState::msFinalBoard = GameState(final_board);

    return true;
}

void GameState::DisplayBoard() const
{
    for (int row = 0; row < GameState::msBoardHeight; ++row)
    {
        for (int col = 0; col < GameState::msBoardWidth; ++col)
        {
            std::cout << mBoard[row][col] << " ";
        }
        std::cout << std::endl;
    }
}

/* From a GameState, generate all the possible next GameState */
std::vector<GameState> GameState::GetNextStates() const
{
    std::vector<GameState> result;
    for (int i = 0; i < mPieces.size(); ++i)
    {
        for (Coordinate dir : directions)
        {
            Coordinate dest = mPieces[i].position + dir;
            if (CanPieceFit(mPieces[i], dest))
            {
                std::vector<std::vector<int>> new_board = mBoard;
                GameState::MovePiece(mPieces[i], new_board, dest);
                GameState new_game_state = GameState(new_board);

                /* When generating next GameState, update their move history */
                new_game_state.MoveHistory() = mMoveHistory;
                if (dir == Coordinate(-1, 0))
                    new_game_state.MoveHistory().push_back("U"+std::to_string(mPieces[i].index));
                else if (dir == Coordinate(0, 1))
                    new_game_state.MoveHistory().push_back("R"+std::to_string(mPieces[i].index));
                else if (dir == Coordinate(1, 0))
                    new_game_state.MoveHistory().push_back("D"+std::to_string(mPieces[i].index));
                else if (dir == Coordinate(0, -1))
                    new_game_state.MoveHistory().push_back("L"+std::to_string(mPieces[i].index));

                /* Update the gscore for IDA* */
                new_game_state.G() = mG + 1;

                result.push_back(new_game_state);
            }
        }
    }
    return result;
}

/* Check if piece can fit at a given coordinate */
bool GameState::CanPieceFit(const Piece &piece, const Coordinate &dest) const
{
    for (int i = 0; i < piece.height; ++i)
    {
        for (int j = 0; j < piece.width; ++j)
        {
            if (dest.y + i >= GameState::msBoardHeight 
                || dest.x + j >= GameState::msBoardWidth
                || dest.y + i < 0
                || dest.x + j < 0)
                return false;
            if (mBoard[dest.y+i][dest.x+j] != 0 && mBoard[dest.y+i][dest.x+j] != piece.index)
            {
                return false;
            }
        }
    }
    return true;
}

bool GameState::CanPieceFit(const Piece &piece, const std::vector<std::vector<int>> &board, const Coordinate &dest)
{
    for (int i = 0; i < piece.height; ++i)
    {
        for (int j = 0; j < piece.width; ++j)
        {
            if (dest.y + i >= board.size() 
                || dest.x + j >= board[0].size()
                || dest.y + i < 0
                || dest.x + j < 0)
                return false;
            if (board[dest.y+i][dest.x+j] != 0 && board[dest.y+i][dest.x+j] != piece.index)
            {
                return false;
            }
        }
    }
    return true;
}

/* Move a piece to the desired position */
void GameState::MovePiece(const Piece &piece, const Coordinate &dest)
{
    for (int i = 0; i < piece.height; ++i)
    {
        for (int j = 0; j < piece.width; ++j)
        {
            mBoard[piece.position.y+i][piece.position.x+j] = 0;
        }
    }

    for (int i = 0; i < piece.height; ++i)
    {
        for (int j = 0; j < piece.width; ++j)
        {
            mBoard[dest.y+i][dest.x+j] = piece.index;
        }
    }
}

void GameState::MovePiece(const Piece &piece, std::vector<std::vector<int>> &board, const Coordinate &dest)
{
    for (int i = 0; i < piece.height; ++i)
    {
        for (int j = 0; j < piece.width; ++j)
        {
            board[piece.position.y+i][piece.position.x+j] = 0;
        }
    }

    for (int i = 0; i < piece.height; ++i)
    {
        for (int j = 0; j < piece.width; ++j)
        {
            board[dest.y+i][dest.x+j] = piece.index;
        }
    }
}

/* Using Manhattan distance as heuristic */
int GameState::Heuristic() const
{
    size_t result = 0;
    for (int i = 0; i < mPieces.size(); ++i)
    {
        result += mPieces[i].position.Manhattan(GameState::msFinalBoard.Pieces()[i].position);
    }
    return result;
}