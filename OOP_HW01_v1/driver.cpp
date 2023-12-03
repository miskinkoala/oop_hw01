#include <iostream>
#include "chess.hpp"

int main()
{
    cout << "Welcome to the Chess Game!" << endl;
    ChessBoard board;
    string command;
    /*vector<vector<int>> twoDVector(0, vector<int>(2, -1));
    twoDVector.push_back({1, 2});
    twoDVector.push_back({2, 5});
    twoDVector.push_back({4, 6});
*/

    cout << board << endl;
    // string cmd = getUserMove();
    //  cout << twoDVector[0][1] << endl;
    cout << "Enter your move:" << endl;
    cin >> command;
    board.move(command);
    cout << board << endl;

    cout << "Enter your move:" << endl;
    cin >> command;
    board.move(command);
    cout << board << endl;

    cout << "Enter your move:" << endl;
    cin >> command;
    board.move(command);
    cout << board << endl;

    cout << "Enter your move:" << endl;
    cin >> command;
    board.move(command);
    cout << board << endl;

    /*for (const auto &row : twoDVector)
    {
        for (const auto &element : row)
        {
            std::cout << element << " ";
        }
        std::cout << std::endl;
    }*/
}
