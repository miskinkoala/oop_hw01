#include "chess.hpp"

#define COLLUM 8
#define ROW 8

// namespace std;
const int START_SCORE = 1000;

///////////////

// GLOBAL FUNCTIONS

bool search(vector<vector<int>> vec, int i, int j)
{
    for (int a = 0; a < vec.size(); ++a)
    {
        if (vec[a][0] == i && vec[a][1] == j)
            return true;
    }
    return false;
}

string getUserMove()
{
    string command;
    cout << "Enter your move:" << endl;
    cin >> command;
    return command;
}

/////////////////

ChessBoard::ChessBoard() : _bScore(START_SCORE), _wScore(START_SCORE)
{
    _board = vector<vector<ChessPiece>>(ROW, vector<ChessPiece>(COLLUM, ChessPiece('.', 'n')));
    B_king_indexes = {0, 4};
    W_king_indexes = {7, 4};
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COLLUM; ++j)
        {
            if (i == 0)
            { // black pieces(exluce pawns) placing
                if (j == 0 || j == 7)
                    _board[i][j] = ChessPiece('r', 'b'); // rook
                else if (j == 1 || j == 6)
                    _board[i][j] = ChessPiece('n', 'b'); // knight
                else if (j == 2 || j == 5)
                    _board[i][j] = ChessPiece('b', 'b'); // bishop
                else if (j == 3)
                    _board[i][j] = ChessPiece('q', 'b'); // quen
                else if (j == 4)
                    _board[i][j] = ChessPiece('k', 'b'); // king
            }
            else if (i == 7)
            { // white pieces(exluce pawns) placing
                if (j == 0 || j == 7)
                    _board[i][j] = ChessPiece('r', 'w'); // rook
                else if (j == 1 || j == 6)
                    _board[i][j] = ChessPiece('n', 'w'); // knight
                else if (j == 2 || j == 5)
                    _board[i][j] = ChessPiece('b', 'w'); // bishop
                else if (j == 3)
                    _board[i][j] = ChessPiece('q', 'w'); // quen
                else if (j == 4)
                    _board[i][j] = ChessPiece('k', 'w'); // king
            }
            else if (i == 1) // pawn placing(black)
                _board[i][j] = ChessPiece('p', 'b');
            else if (i == 6)
                _board[i][j] = ChessPiece('p', 'w');
            else // place holder wil put dot elsewhere
                _board[i][j] = ChessPiece('.', 'n');
        }
    }
}

/*
const vector<ChessPiece> ChessBoard::operator[](int i) const
{
    return (_board[i]);
}

vector<ChessPiece> &ChessBoard::operator[](int i)
{
    return _board[i];
}
*/
// FRIEND AND GLOBALSS FUNCTIONS

int *commandResolver(const string &command)
{
    int *cmd = new int[4];
    for (int i = 0; i < 4; ++i) // TODO check error if(command[i] - 97 > 7)
    {
        if (command[i] >= '1' && command[i] <= '8')
            cmd[i] = (command[i] - 49);
        else if (command[i] >= 'a' && command[i] <= 'h')
            cmd[i] = (command[i] - 97);
        else
            cerr << "error in commandresolver" << endl; // cmd = nullptr
    }
    cmd[1] = abs(cmd[1] - 7);
    cmd[3] = abs(cmd[3] - 7);
    return cmd;
}

void ChessBoard::move(const string &command)
{
    int *cmd;
    if ((cmd = commandResolver(command)) == nullptr)
        cerr << "error invalid input" << endl;
    cerr << cmd[0] << endl;
    cerr << cmd[1] << endl;
    cerr << cmd[2] << endl;
    cerr << cmd[3] << endl;

    cerr << "deneme1" << endl;
    cerr << "e7e5" << endl;

    if (isValidMove(cmd))
    {
        cerr << "deneme2" << endl;
        _board[cmd[3]][cmd[2]] = _board[cmd[1]][cmd[0]];
        _board[cmd[1]][cmd[0]] = ChessPiece('.', 'n');
        delete[] cmd;
        cmd = nullptr;
    }
}

bool ChessBoard::isValidMove(const int *cmd) const
{
    //! overload b -> w, w -> b then do merger the black and white validities
    cerr << "deneme3" << endl;
    ChessPiece piece = _board[cmd[1]][cmd[0]];
    vector<vector<int>> possible_moves(0, vector<int>(2, -1));
    int i_current = cmd[1];
    int j_current = cmd[0];
    cerr << "i_current:" << i_current << endl;
    cerr << "j_current:" << j_current << endl;
    cerr << "deneme4" << endl;

    const int i_due = cmd[3];
    const int j_due = cmd[2];
    bool flag_valid = false;
    cerr << "i_due:" << i_due << endl;
    cerr << "j_due:" << j_due << endl;
    cerr << "deneme5" << endl;
    cerr << "piece.getType():" << piece.getType() << endl;

    switch (piece.getType())
    {
    case 'p':
        // black pown validty
        cerr << "deneme6" << endl;
        if (piece.getColor() == 'b' && i_current == 1) // pown if havent move
        {
            cerr << "_board[i_current + 1][j_current]:" << _board[i_current + 1][j_current] << endl;
            if (_board[i_current + 1][j_current] == '.')
            {
                cerr << "girdi0" << endl;
                possible_moves.push_back({i_current + 1, j_current});
                if (_board[i_current + 2][j_current] == '.')
                    possible_moves.push_back({i_current + 2, j_current});
            }
            if (_board[i_current + 1][j_current + 1] != '.' && _board[i_current + 1][j_current + 1].getColor() != 'b') // cross move of pawn
                possible_moves.push_back({i_current + 1, j_current + 1});
            if (_board[i_current + 1][j_current - 1] != '.' && _board[i_current + 1][j_current - 1].getColor() != 'b') // cross move of pawn
                possible_moves.push_back({i_current + 1, j_current - 1});
        }
        else if (piece.getColor() == 'b')
        {
            if (_board[i_current + 1][j_current] == '.') // TODO add else if here for cross move of pawn
                possible_moves.push_back({i_current + 1, j_current});
            if (_board[i_current + 1][j_current + 1] != '.' && _board[i_current + 1][j_current + 1].getColor() != 'b') // cross move of pawn
                possible_moves.push_back({i_current + 1, j_current + 1});
            if (_board[i_current + 1][j_current - 1] != '.' && _board[i_current + 1][j_current - 1].getColor() != 'b') // cross move of pawn
                possible_moves.push_back({i_current + 1, j_current - 1});
        }
        else if (piece.getColor() == 'w' && i_current == 6) // pown if havent move
        {
            if (_board[i_current - 1][j_current] == '.')
            {
                possible_moves.push_back({i_current - 1, j_current});
                if (_board[i_current - 2][j_current] == '.')
                    possible_moves.push_back({i_current - 2, j_current});
            }
            if (_board[i_current + 1][j_current + 1] != '.' && _board[i_current + 1][j_current + 1].getColor() != 'w') // cross move of pawn
                possible_moves.push_back({i_current + 1, j_current + 1});
            if (_board[i_current + 1][j_current - 1] != '.' && _board[i_current + 1][j_current - 1].getColor() != 'w') // cross move of pawn
                possible_moves.push_back({i_current + 1, j_current - 1});
        }
        else if (piece.getColor() == 'w')
        {
            if (_board[i_current - 1][j_current] == '.')
                possible_moves.push_back({i_current - 1, j_current});
            if (_board[i_current + 1][j_current + 1] != '.' && _board[i_current + 1][j_current + 1].getColor() != 'w') // cross move of pawn
                possible_moves.push_back({i_current + 1, j_current + 1});
            if (_board[i_current + 1][j_current - 1] != '.' && _board[i_current + 1][j_current - 1].getColor() != 'w') // cross move of pawn
                possible_moves.push_back({i_current + 1, j_current - 1});
        }

        cerr << "search(possible_moves, i_due, j_due):" << search(possible_moves, i_due, j_due) << endl;
        cerr << "(isCheck(piece.getColor())):" << (isCheck(piece.getColor())) << endl;
        cerr << "possible_moves.size()" << possible_moves.size() << endl;

        for (size_t i = 0; i < possible_moves.size(); ++i)
        {
            for (size_t j = 0; j < possible_moves[i].size(); ++j)
            {
                cerr << possible_moves[i][j] << ' ';
            }
            cerr << endl;
        }

        if (search(possible_moves, i_due, j_due) && !(isCheck(piece.getColor()))) // TODO
            flag_valid = true;

        break;
    case 'b':

        i_current = cmd[1];
        j_current = cmd[0];

        if (piece.getColor() == 'b')
        {

            while (!flag_valid && i_current > 0 && j_current < 7) // cross right up
            {
                --i_current;
                ++j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'b')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];
            while (!flag_valid && i_current > 0 && j_current > 0) // cross left up
            {
                --i_current;
                --j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'b')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];

            while (!flag_valid && i_current < 7 && j_current < 7) // cross right down
            {

                ++i_current;
                ++j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'b')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];

            while (!flag_valid && i_current < 7 && j_current > 0) // cross left down
            {

                ++i_current;
                --j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'b')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }
        }
        else if (piece.getColor() == 'w')
        {
            while (!flag_valid && i_current > 0 && j_current < 7) // cross right up
            {
                --i_current;
                ++j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'w')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];
            while (!flag_valid && i_current > 0 && j_current > 0) // cross left up
            {
                --i_current;
                --j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'w')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];

            while (!flag_valid && i_current < 7 && j_current < 7) // cross right down
            {

                ++i_current;
                ++j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'w')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];

            while (!flag_valid && i_current < 7 && j_current > 0) // cross left down
            {

                ++i_current;
                --j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'w')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }
        }
        if (search(possible_moves, i_due, j_due) && !(isCheck(piece.getColor()))) // TODO
            flag_valid = true;

        break;

    case 'n':

        if (piece.getColor() == 'b')
        {

            if (i_current - 2 >= 0)
            { // upword L
                if (j_current - 1 >= 0 && _board[i_current - 2][j_current - 1].getColor() != 'b')
                    possible_moves.push_back({i_current - 2, j_current - 1}); // left check
                if (j_current + 1 <= 7 && _board[i_current - 2][j_current + 1].getColor() != 'b')
                    possible_moves.push_back({i_current - 2, j_current + 1}); // right check
            }
            if (i_current + 2 <= 7)
            { // downward L
                if (j_current - 1 >= 0 && _board[i_current + 2][j_current - 1].getColor() != 'b')
                    possible_moves.push_back({i_current + 2, j_current - 1}); // left check
                if (j_current + 1 <= 7 && _board[i_current + 2][j_current + 1].getColor() != 'b')
                    possible_moves.push_back({i_current + 2, j_current + 1}); // right check
            }
            if (j_current + 2 <= 7) // right L
            {
                if (i_current - 1 >= 0 && _board[i_current - 1][j_current + 2].getColor() != 'b')
                    possible_moves.push_back({i_current - 1, j_current + 2}); // up check
                if (i_current + 1 <= 7 && _board[i_current + 1][j_current + 2].getColor() != 'b')
                    possible_moves.push_back({i_current + 1, j_current + 2}); // down check
            }
            if (j_current - 2 >= 0) // left L
            {
                if (i_current - 1 >= 0 && _board[i_current - 1][j_current - 2].getColor() != 'b')
                    possible_moves.push_back({i_current - 1, j_current - 2}); // up check
                if (i_current + 1 <= 7 && _board[i_current + 1][j_current - 2].getColor() != 'b')
                    possible_moves.push_back({i_current + 1, j_current - 2}); // down check
            }
        }
        else if (piece.getColor() == 'w')
        {
            if (i_current - 2 >= 0)
            { // upword L
                if (j_current - 1 >= 0 && _board[i_current - 2][j_current - 1].getColor() != 'w')
                    possible_moves.push_back({i_current - 2, j_current - 1}); // left check
                if (j_current + 1 <= 7 && _board[i_current - 2][j_current + 1].getColor() != 'w')
                    possible_moves.push_back({i_current - 2, j_current + 1}); // right check
            }
            if (i_current + 2 <= 7)
            { // downward L
                if (j_current - 1 >= 0 && _board[i_current + 2][j_current - 1].getColor() != 'w')
                    possible_moves.push_back({i_current + 2, j_current - 1}); // left check
                if (j_current + 1 <= 7 && _board[i_current + 2][j_current + 1].getColor() != 'w')
                    possible_moves.push_back({i_current + 2, j_current + 1}); // right check
            }
            if (j_current + 2 <= 7) // right L
            {
                if (i_current - 1 >= 0 && _board[i_current - 1][j_current + 2].getColor() != 'w')
                    possible_moves.push_back({i_current - 1, j_current + 2}); // up check
                if (i_current + 1 <= 7 && _board[i_current + 1][j_current + 2].getColor() != 'w')
                    possible_moves.push_back({i_current + 1, j_current + 2}); // down check
            }
            if (j_current - 2 >= 0) // left L
            {
                if (i_current - 1 >= 0 && _board[i_current - 1][j_current - 2].getColor() != 'w')
                    possible_moves.push_back({i_current - 1, j_current - 2}); // up check
                if (i_current + 1 <= 7 && _board[i_current + 1][j_current - 2].getColor() != 'w')
                    possible_moves.push_back({i_current + 1, j_current - 2}); // down check
            }
        }
        if (search(possible_moves, i_due, j_due) && !(isCheck(piece.getColor()))) // TODO
            flag_valid = true;

        break;
    /**/ case 'r':

        if (piece.getColor() == 'b')
        {

            while (!flag_valid && i_current > 0) // up
            {
                --i_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'b')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];
            while (!flag_valid && j_current > 0) // left
            {
                --j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'b')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];

            while (!flag_valid && j_current < 7) // right
            {
                ++j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'b')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];

            while (!flag_valid && i_current < 7) // down
            {
                ++i_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'b')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }
        }
        else if (piece.getColor() == 'w')
        {
            while (!flag_valid && i_current > 0) // up
            {
                --i_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'w')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];
            while (!flag_valid && j_current > 0) // left
            {
                --j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'w')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];

            while (!flag_valid && j_current < 7) // right
            {
                ++j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'w')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];

            while (!flag_valid && i_current < 7) // down
            {
                ++i_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'w')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }
        }
        if (search(possible_moves, i_due, j_due) && !(isCheck(piece.getColor()))) // TODO
            flag_valid = true;

        break;
    case 'q':

        if (piece.getColor() == 'b')
        {

            while (!flag_valid && i_current > 0) // up
            {
                --i_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'b')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];
            while (!flag_valid && j_current > 0) // left
            {
                --j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'b')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];

            while (!flag_valid && j_current < 7) // right
            {
                ++j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'b')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];

            while (!flag_valid && i_current < 7) // down
            {
                ++i_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'b')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            while (!flag_valid && i_current > 0 && j_current < 7) // cross right up
            {
                --i_current;
                ++j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'b')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];
            while (!flag_valid && i_current > 0 && j_current > 0) // cross left up
            {
                --i_current;
                --j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'b')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];

            while (!flag_valid && i_current < 7 && j_current < 7) // cross right down
            {

                ++i_current;
                ++j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'b')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];

            while (!flag_valid && i_current < 7 && j_current > 0) // cross left down
            {

                ++i_current;
                --j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'b')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }
        }
        else if (piece.getColor() == 'w')
        {

            while (!flag_valid && i_current > 0) // up
            {
                --i_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'w')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];
            while (!flag_valid && j_current > 0) // left
            {
                --j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'w')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];

            while (!flag_valid && j_current < 7) // right
            {
                ++j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'w')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];

            while (!flag_valid && i_current < 7) // down
            {
                ++i_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'w')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            while (!flag_valid && i_current > 0 && j_current < 7) // cross right up
            {
                --i_current;
                ++j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'w')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];
            while (!flag_valid && i_current > 0 && j_current > 0) // cross left up
            {
                --i_current;
                --j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'w')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];

            while (!flag_valid && i_current < 7 && j_current < 7) // cross right down
            {

                ++i_current;
                ++j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'w')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }

            i_current = cmd[1];
            j_current = cmd[0];

            while (!flag_valid && i_current < 7 && j_current > 0) // cross left down
            {

                ++i_current;
                --j_current;
                if (_board[i_current][j_current].getType() != '.')
                {
                    if (_board[i_current][j_current].getColor() != 'w')
                    {
                        possible_moves.push_back({i_current, j_current});
                    }
                    break;
                }
                possible_moves.push_back({i_current, j_current});
            }
        }
        if (search(possible_moves, i_due, j_due) && !(isCheck(piece.getColor()))) // TODO
            flag_valid = true;
        break;

    case 'k':
        if (piece.getColor() == 'b')
        {
            if (i_current - 1 >= 0)
            { // up
            }
            if (i_current + 2 <= 7)
            { // down
            }
            if (j_current + 2 <= 7) // right
            {
            }
            if (j_current - 2 >= 0) // left
            {
            }

            if (i_current - 2 >= 0)
            { // right cross up
            }
            if (i_current + 2 <= 7)
            { // left cross up
            }
            if (j_current + 2 <= 7) // right cross down
            {
            }
            if (j_current - 2 >= 0) // left cross downs
            {
            }
        }

        break;
    }
    cerr << "flag_valid:" << flag_valid << endl;
    cerr << "possible_moves: " << endl;
    for (size_t i = 0; i < possible_moves.size(); ++i)
    {
        for (size_t j = 0; j < possible_moves[i].size(); ++j)
        {
            cerr << possible_moves[i][j] << ' ';
        }
        cerr << endl;
    }
    return flag_valid;
}

bool ChessBoard::isCheck(const char color) const
{
    // can ı merge black and white king conditions
    // add bishop conditon
    bool flag_check = false;
    int king_i;
    int king_j;
    if (color == 'b') // checks for black king
    {
        king_i = B_king_indexes[0];
        king_j = B_king_indexes[1];
        while (!flag_check && king_i > 0) // upward
        {
            --king_i;
            if (_board[king_i][king_j].getType() != '.')
            {
                if (_board[king_i][king_j].getColor() != 'b')
                {
                    if (_board[king_i][king_j].getType() == 'q' || // add king here for validty
                        _board[king_i][king_j].getType() == 'r')
                    {
                        cerr << "deneme ischeck1" << endl;
                        flag_check = true;
                        break;
                    }
                }
                break;
            }
        }

        king_i = B_king_indexes[0];
        king_j = B_king_indexes[1];
        while (!flag_check && king_i < 7) // downward
        {
            ++king_i;
            if (_board[king_i][king_j].getType() != '.')
            {
                if (_board[king_i][king_j].getColor() != 'b')
                {
                    if (_board[king_i][king_j].getType() == 'q' ||
                        _board[king_i][king_j].getType() == 'r')
                    {
                        cerr << "deneme ischeck2" << endl;
                        flag_check = true;
                        break;
                    }
                }
                break;
            }
        }

        king_i = B_king_indexes[0];
        king_j = B_king_indexes[1];
        while (!flag_check && king_j < 7) // right
        {
            ++king_j;
            if (_board[king_i][king_j].getType() != '.')
            {
                if (_board[king_i][king_j].getColor() != 'b')
                {
                    if (_board[king_i][king_j].getType() == 'q' ||
                        _board[king_i][king_j].getType() == 'r')
                    {
                        flag_check = true;
                        cerr << "deneme ischeck3" << endl;
                        break;
                    }
                }
                break;
            }
        }

        king_i = B_king_indexes[0];
        king_j = B_king_indexes[1];
        while (!flag_check && king_j > 0) // left
        {
            --king_j;
            if (_board[king_i][king_j].getType() != '.')
            {
                if (_board[king_i][king_j].getColor() != 'b')
                {
                    if (_board[king_i][king_j].getType() == 'q' ||
                        _board[king_i][king_j].getType() == 'r')
                    {
                        flag_check = true;
                        cerr << "deneme ischeck4" << endl;
                        break;
                    }
                }
                break;
            }
        }

        king_i = B_king_indexes[0];
        king_j = B_king_indexes[1];
        while (!flag_check && king_i > 0 && king_j < 7) // cross right up
        {
            --king_i;
            ++king_j;
            if (_board[king_i][king_j].getType() != '.')
            {
                if (_board[king_i][king_j].getColor() != 'b')
                {
                    if (_board[king_i][king_j].getType() == 'q' ||
                        _board[king_i][king_j].getType() == 'b')
                    {
                        flag_check = true;
                        cerr << "deneme ischeck5" << endl;
                        break;
                    }
                }
                break;
            }
        }

        king_i = B_king_indexes[0];
        king_j = B_king_indexes[1];
        while (!flag_check && king_i > 0 && king_j > 0) // cross left up
        {
            --king_i;
            --king_j;
            if (_board[king_i][king_j].getType() != '.')
            {
                if (_board[king_i][king_j].getColor() != 'b')
                {
                    if (_board[king_i][king_j].getType() == 'q' ||
                        _board[king_i][king_j].getType() == 'b')
                    {
                        flag_check = true;
                        cerr << "deneme ischeck6" << endl;
                        break;
                    }
                }
                break;
            }
        }

        king_i = B_king_indexes[0];
        king_j = B_king_indexes[1];

        if ((king_i < 7 && king_j < 7) && (_board[king_i + 1][king_j + 1].getType() == 'p' &&
                                           _board[king_i + 1][king_j + 1].getColor() == 'w'))
            flag_check = true;

        while (!flag_check && king_i < 7 && king_j < 7) // cross right down
        {

            ++king_i;
            ++king_j;
            if (_board[king_i][king_j].getType() != '.')
            {
                if (_board[king_i][king_j].getColor() != 'b')
                {
                    if (_board[king_i][king_j].getType() == 'q' ||
                        _board[king_i][king_j].getType() == 'b')
                    {
                        flag_check = true;
                        cerr << "deneme ischeck7" << endl;
                        break;
                    }
                }
                break;
            }
        }

        king_i = B_king_indexes[0];
        king_j = B_king_indexes[1];

        if ((king_i < 7 && king_j > 0) && (_board[king_i + 1][king_j - 1].getType() == 'p' &&
                                           _board[king_i + 1][king_j - 1].getColor() == 'w'))
            flag_check = true;

        while (!flag_check && king_i < 7 && king_j > 0) // cross left down
        {

            ++king_i;
            --king_j;
            if (_board[king_i][king_j].getType() != '.')
            {
                if (_board[king_i][king_j].getColor() != 'b')
                {
                    if (_board[king_i][king_j].getType() == 'q' ||
                        _board[king_i][king_j].getType() == 'b')
                    {
                        flag_check = true;
                        cerr << "deneme ischeck8" << endl;
                        break;
                    }
                }
                break;
            }
        }
        cerr << "flag_check ischeck10" << flag_check << endl;
    }
    else if (color == 'w') // checks for white king
    {
        cerr << "girdi beyaz ischeck9" << endl;

        int king_i = W_king_indexes[0];
        int king_j = W_king_indexes[1];
        while (!flag_check && king_i > 0) // upward
        {
            --king_i;
            if (_board[king_i][king_j].getType() != '.')
            {
                if (_board[king_i][king_j].getColor() != 'w')
                {
                    if (_board[king_i][king_j].getType() == 'q' || // add king here for validty
                        _board[king_i][king_j].getType() == 'r')
                    {
                        flag_check = true;
                        break;
                    }
                }
                break;
            }
        }
        cerr << "1flag_check ischeck: " << flag_check << endl;
        king_i = W_king_indexes[0];
        king_j = W_king_indexes[1];
        while (!flag_check && king_i < 7) // downward
        {
            ++king_i;
            if (_board[king_i][king_j].getType() != '.')
            {
                if (_board[king_i][king_j].getColor() != 'w')
                {
                    if (_board[king_i][king_j].getType() == 'q' ||
                        _board[king_i][king_j].getType() == 'r')
                    {
                        flag_check = true;
                        break;
                    }
                }
                break;
            }
        }
        cerr << "2flag_check ischeck: " << flag_check << endl;
        king_i = W_king_indexes[0];
        king_j = W_king_indexes[1];
        while (!flag_check && king_j < 7) // right
        {
            ++king_j;
            if (_board[king_i][king_j].getType() != '.')
            {
                if (_board[king_i][king_j].getColor() != 'w')
                {
                    if (_board[king_i][king_j].getType() == 'q' ||
                        _board[king_i][king_j].getType() == 'r')
                    {
                        flag_check = true;
                        break;
                    }
                }
                break;
            }
        }
        cerr << "3flag_check ischeck: " << flag_check << endl;
        king_i = W_king_indexes[0];
        king_j = W_king_indexes[1];
        while (!flag_check && king_j > 0) // left
        {
            --king_j;
            if (_board[king_i][king_j].getType() != '.')
            {
                if (_board[king_i][king_j].getColor() != 'w')
                {
                    if (_board[king_i][king_j].getType() == 'q' ||
                        _board[king_i][king_j].getType() == 'r')
                    {
                        flag_check = true;
                        break;
                    }
                }
                break;
            }
        }
        cerr << "4flag_check ischeck: " << flag_check << endl;
        king_i = W_king_indexes[0];
        king_j = W_king_indexes[1];

        if ((king_i > 0 && king_j < 7) && ((_board[king_i - 1][king_j + 1].getType() == 'p') &&
                                           _board[king_i - 1][king_j + 1].getColor() == 'b'))
            flag_check = true;

        while (!flag_check && king_i > 0 && king_j < 7) // cross right up
        {
            --king_i;
            ++king_j;
            if (_board[king_i][king_j].getType() != '.')
            {
                if (_board[king_i][king_j].getColor() != 'w')
                {
                    if (_board[king_i][king_j].getType() == 'q' ||
                        _board[king_i][king_j].getType() == 'b')
                    {
                        flag_check = true;
                        break;
                    }
                }
                break;
            }
        }
        cerr << "5flag_check ischeck: " << flag_check << endl;
        king_i = W_king_indexes[0];
        king_j = W_king_indexes[1];

        if ((king_i > 0 && king_j > 7) && (_board[king_i - 1][king_j - 1].getType() == 'p' &&
                                           _board[king_i - 1][king_j - 1].getColor() == 'b'))
            flag_check = true;

        while (!flag_check && king_i > 0 && king_j > 0) // cross left up
        {
            --king_i;
            --king_j;
            if (_board[king_i][king_j].getType() != '.')
            {
                if (_board[king_i][king_j].getColor() != 'w')
                {
                    if (_board[king_i][king_j].getType() == 'q' ||
                        _board[king_i][king_j].getType() == 'b')
                    {
                        flag_check = true;
                        break;
                    }
                }
                break;
            }
        }
        cerr << "6flag_check ischeck: " << flag_check << endl;
        king_i = W_king_indexes[0];
        king_j = W_king_indexes[1];

        while (!flag_check && king_i < 7 && king_j < 7) // cross right down
        {

            ++king_i;
            ++king_j;
            if (_board[king_i][king_j].getType() != '.')
            {
                if (_board[king_i][king_j].getColor() != 'w')
                {
                    if (_board[king_i][king_j].getType() == 'q' ||
                        _board[king_i][king_j].getType() == 'b')
                    {
                        flag_check = true;
                        break;
                    }
                }
                break;
            }
        }
        cerr << "7flag_check ischeck: " << flag_check << endl;
        king_i = W_king_indexes[0];
        king_j = W_king_indexes[1];

        while (!flag_check && king_i < 7 && king_j > 0) // cross left down
        {

            ++king_i;
            --king_j;
            if (_board[king_i][king_j].getType() != '.')
            {
                if (_board[king_i][king_j].getColor() != 'w')
                {
                    if (_board[king_i][king_j].getType() == 'q' ||
                        _board[king_i][king_j].getType() == 'b')
                    {
                        flag_check = true;
                        break;
                    }
                }
                break;
            }
        }
    }
    cerr << "deneme ischeck9" << endl;
    cerr << "flag_check ischeck: " << flag_check << endl;
    return flag_check; // TODO when flag check true imediatly return
}

ostream &operator<<(ostream &os, const ChessBoard obj)
{
    for (int i = 0; i < ROW; ++i)
    {
        os << abs(8 - i) << " | ";
        for (int j = 0; j < COLLUM; ++j)
        {
            os << obj._board[i][j] << ' ';
        }
        os << endl;
    }
    os << "    ";
    for (int i = 0; i < (COLLUM * 2 + 2); ++i)
    {
        os << "-";
    }
    os << endl;

    os << "    "; // TODO print " " char amount of rate of columm
    char letter = 'a';
    for (int i = 0; i < COLLUM; ++i)
    {
        os << letter++ << " ";
    }
    return os;
}

////////////////////////////////////////////////

ChessPiece::ChessPiece(char type = '.', char color = 'n') : _type(type), _color(color) // TODO make defoult . piece
{
    _point = 100;
}

char ChessPiece::getType() const
{
    return _type;
}
char ChessPiece::getColor() const
{
    return _color;
}

bool ChessPiece::operator==(const ChessPiece &other) const
{
    return (getType() == other.getType());
}

bool ChessPiece::operator==(const char other) const
{
    return (getType() == other);
}

bool ChessPiece::operator!=(const ChessPiece &other) const
{
    return (!(getType() == other.getType()));
}

bool ChessPiece::operator!=(const char other) const
{
    return (!(getType() == other));
}

// FRIEND AND GLOBAL FUNCTIONS

ostream &operator<<(ostream &os, const ChessPiece obj)
{
    if (obj.getColor() == 'w')
        os << static_cast<char>((obj.getType()) - 32); // uppercase
    else
        os << obj.getType();

    return os;
}

////////////////////////////
