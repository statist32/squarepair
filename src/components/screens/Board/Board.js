import React, { memo, useState, useEffect } from 'react'
import './Board.css'
import { TileRow } from './TileRow'
//TODO: win condition with reduce or filter
function _Board({ columns = 3, rows = 3 }) {
  const [board, setBoard] = useState([[]])
  useEffect(() => {
    initBoard(rows, columns)
  }, [columns, rows])

  function initBoard(rows, columns) {
    let row = []
    for (let i = 0; i < columns; i++) {
      row.push('#7800ff')
    }
    let board = []
    for (let i = 0; i < rows; i++) {
      //...row copys row otherwise shallow copy
      board.push([...row])
    }

    setBoard(board)
  }
  function manageColor(color) {
    switch (color) {
      case '#7800ff':
        return '#FF7800'
      case '#FF7800':
        return '#00FF78'
      case '#00FF78':
        return '#7800ff'

      default:
        return 'black'
    }
  }
  function changeTile(row, column) {
    //deep copy of board
    const tempBoard = [...board]
    const columns = tempBoard[0].length
    const rows = tempBoard.length
    tempBoard[row][column] = manageColor(tempBoard[row][column])

    if (row - 1 >= 0) {
      tempBoard[row - 1][column] = manageColor(tempBoard[row - 1][column])
    }
    if (row + 1 < columns) {
      tempBoard[row + 1][column] = manageColor(tempBoard[row + 1][column])
    }
    if (column - 1 >= 0) {
      tempBoard[row][column - 1] = manageColor(tempBoard[row][column - 1])
    }
    if (column + 1 < rows) {
      tempBoard[row][column + 1] = manageColor(tempBoard[row][column + 1])
    }

    setBoard(tempBoard)
    checkWin()
  }

  function shuffleBoard(shuffles) {
    for (let i = 0; i < shuffles; i++) {
      let randomRow = Math.floor(Math.random() * rows)
      let randomColumn = Math.floor(Math.random() * columns)
      changeTile(randomRow, randomColumn)
    }
  }
  function checkWin() {
    let win = true
    const first = board[0][0]
    for (let i = 0; i < columns && win; i++) {
      for (let j = 0; j < rows && win; j++) {
        win = first === board[i][j] ? true : false
      }
    }
    if (win) {
      alert('You solved it!')
    }
  }
  return (
    <div className='board-wrapper'>
      <div className='shuffle-btn' onClick={() => shuffleBoard(1)}>
        Shuffle
      </div>
      <div className='board'>
        {board.map((row, index) => (
          <TileRow
            rowNumber={index}
            row={row}
            onClick={changeTile}
            key={index}
          />
        ))}
      </div>
    </div>
  )
}

export const Board = memo(_Board)
