import random
from copy import deepcopy
testBoard = [[1, 1, 1], [1, 1, 0], [1, 0, 0]]
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


def findSolution():
    for row in range(rows):
        for column in range(columns):
            tempBoard = click(row, column, deepcopy(testBoard))
            if checkWin(tempBoard):
                print(f"gg@ row:{row} column:{column}")
                print(tempBoard)
            else:
                # reset board
                pass


findSolution()
