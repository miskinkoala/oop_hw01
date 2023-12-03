#include <vector>
#include <iostream>
using namespace std;

/*
------
The #define Guard

#ifndef FOO_BAR_BAZ_H_
#define FOO_BAR_BAZ_H_

...

#endif  // FOO_BAR_BAZ_H_

------
inline function less than 10 lines

-------
dir2/foo2.h.
A blank line
C system headers (more precisely: headers in angle brackets with the .h extension), e.g., <unistd.h>, <stdlib.h>.
A blank line
C++ standard library headers (without file extension), e.g., <algorithm>, <cstddef>.
A blank line
Other libraries' .h files.
A blank line
Your project's .h files.


-------
put it in namespace "CSE241HW"




--------
o Pawn: 1 point
o Knight: 3 points
o Bishop: 3 points
o Rook: 5 points
o Queen: 9 points
o Safety of each piece: minus half the point of that piece if under attack

*/

#include <iostream>

// Define a struct for an integer pair
struct IntPair
{
    int first;
    int second;
};

class ChessPiece
{
public:
    ChessPiece(char type, char color);
    char getColor() const;
    char getType() const;
    double getPoint() const; // TODO: think if we set minus points when under threat

    char setColor(char color);
    char setType(char type);
    double setPoint(double point); // TODO: think if we set minus points when under threat

    friend ostream &operator<<(ostream &os, const ChessPiece obj);
    bool operator==(const ChessPiece &other) const;
    bool operator==(const char other) const;
    bool operator!=(const ChessPiece &other) const;
    bool operator!=(const char other) const;

private:
    char _color;
    char _type;
    int _point;
};

class ChessBoard
{

public:
    ChessBoard();
    // ChessBoard(Fıleptr)        bool loadFile();

    // getters and setters
    vector<vector<ChessPiece>> getBoard();
    double getBScore() const;
    double getWScore() const;
    // vector<vector<ChessPiece>> getBoard() const; TODO: could not know what to do when acces object's private data
    // const situation modify or not instead I'll go for [] operator overload
    void setBScore(double score);
    void setWScore(double score);

    void printBoard() const;
    int calcScore();
    void move(const string &command);
    bool isValidMove(const int *command) const;
    bool isCheck(const char color) const; // TODO will change
    bool saveFile() const;

    friend ostream &operator<<(ostream &os, const ChessBoard obj);
    vector<ChessPiece> &operator[](int i);
    const vector<ChessPiece> operator[](int i) const;

    // TODO make global
    // bool getUserMove();

private:
    vector<vector<ChessPiece>> _board;
    double _bScore;
    double _wScore;
    vector<int> B_king_indexes;
    vector<int> W_king_indexes;
};
