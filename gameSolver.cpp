#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <set>
using namespace std;

/* helper function to display and store solutions */
void printBoard(vector<vector<int>> board)
{
    for (vector<int> row : board)
    {
        for (int item : row)
        {
            cout << item << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printSolutionWithClicks(pair<vector<vector<int>>, pair<int, int>> solutionWithClicks)
{
    printBoard(solutionWithClicks.first);
    cout << solutionWithClicks.second.first << " " << solutionWithClicks.second.second << endl;
}

/*game logic*/
int manageColor(int color, int colorAmount)
{
    return (color + 1) % colorAmount;
}

vector<std::vector<int>> clickBoard(int row, int column, vector<vector<int>> board, int colorAmount)
{
    vector<vector<int>> tempBoard(board);
    const int rows = tempBoard.size();
    const int columns = tempBoard[0].size();

    tempBoard[row][column] = manageColor(tempBoard[row][column], colorAmount);
    for (int offset = -1; offset < 2; offset += 2)
    {

        if (row + offset >= 0 && row + offset < columns)
            tempBoard[row + offset][column] = manageColor(tempBoard[row + offset][column], colorAmount);
        if (column + offset >= 0 && column + offset < rows)
            tempBoard[row][column + offset] = manageColor(tempBoard[row][column + offset], colorAmount);
    }
    return tempBoard;
}

bool checkWin(vector<vector<int>> board)
{
    const int check = board[0][0];
    for (vector<int> row : board)
    {
        for (int item : row)
        {
            if (check != item)
                return false;
        }
    }
    return true;
}

/* Solver*/

void findSolutions(int rows, int columns, int colorAmount)
{
    cout << "Computing all possible solutions for a " << rows << " * " << columns << " board with " << colorAmount << " colors." << endl;
    set<vector<vector<int>>> solutionsAll;
    set<vector<vector<int>>> solutionsLast;
    vector<pair<vector<vector<int>>, pair<int, int>>> solutionsWithClicks;

    set<vector<vector<int>>> solutionsCurrent;
    bool finished = false;
    for (int color = 0; color < colorAmount; color++)
    {
        vector<vector<int>> tempBoard = {{color, color, color}, {color, color, color}, {color, color, color}};
        solutionsAll.insert(tempBoard);
        solutionsLast.insert(tempBoard);
        solutionsWithClicks.push_back(make_pair(tempBoard, make_pair(0, 0)));
    }
    for (int step = 1; !finished; step++)
    {
        for (int click = 0; click < rows * columns; click++)
        {
            const int row = click / columns;
            const int column = click % columns;
            for (vector<vector<int>> board : solutionsLast)
            {
                vector<vector<int>> tempBoard = clickBoard(row, column, board, colorAmount);
                if (!solutionsAll.count(tempBoard))
                {
                    solutionsAll.insert(tempBoard);
                    solutionsCurrent.insert(tempBoard);
                    solutionsWithClicks.push_back(make_pair(tempBoard, make_pair(row, column)));
                }
            }
        }
        solutionsLast = solutionsCurrent;
        solutionsCurrent.clear();
        cout << solutionsLast.size() << " new solutions found with " << step << " steps." << endl;
        if (!solutionsLast.size())
        {
            finished = true;
            cout << "Number of unique boards: " << solutionsAll.size() << endl;
            printSolutionWithClicks(solutionsWithClicks[180]);
        }
    }
}

int main(int argc, char *argv[])
{
    int rows = 3;
    int columns = 3;
    int colorAmount = 2;
    vector<vector<int>> board = {{1, 1, 1},
                                 {1, 1, 1},
                                 {1, 1, 0}};
    // const auto start = chrono::steady_clock::now();
    // findSolutions(rows, columns, colorAmount);
    // const auto end = chrono::steady_clock::now();
    // cout << "Done in " << chrono::duration_cast<chrono::seconds>(end - start).count() << " s!" << endl;
    set<pair<int, string>> test;
    test.insert(make_pair(1, "a"));
    test.insert(make_pair(1, "b"));
    test.insert(make_pair(2, "a"));
    test.insert(make_pair(2, "c"));
    pair<int, string> a(1, "a");
    for (auto i : test)
    {
        if (i == a)
        {
            cout << "hi" << endl;
        }
    }
}