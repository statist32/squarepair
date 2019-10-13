import random
from copy import deepcopy
import pprint
rows = 3
columns = 3
colorAmount = 3


def manageColor(color):
    return (color + 1) % colorAmount


def click(row, column, board):
    tempBoard = deepcopy(board)
    tempBoard[row][column] = manageColor(tempBoard[row][column])
    for offset in [-1, 1]:
        if(0 <= row+offset < rows):
            tempBoard[row +
                      offset][column] = manageColor(tempBoard[row+offset][column])
        if(0 <= column+offset < columns):
            tempBoard[row][column +
                           offset] = manageColor(tempBoard[row][column+offset])
    return tempBoard


def checkWin(board):
    a = board[0][0]
    for row in range(rows):
        for column in range(columns):
            if a != board[row][column]:
                return False
    return True


def findSolution(history, clickAmount):
    # recursion which tests all possible clicks and checks the result of a given board/latest in History
    board = deepcopy(history[-1])
    # base case

    if clickAmount <= 0:
        if checkWin(board):
            print(f"gg@ ")
            print(history)
        else:
            pass
        return
    # main recursion
    for row in range(rows):
        for column in range(columns):
            tempBoard = click(row, column, deepcopy(board))
            tempHistory = deepcopy(history)
            tempHistory.append(tempBoard)
            # pp.pprint(tempHistory)
            findSolution(tempHistory, clickAmount-1)


a = 2
testBoard = [[1, 1, 1],
             [1, 1, a],
             [1, a, a]]


findSolution([deepcopy(testBoard)], 2)
