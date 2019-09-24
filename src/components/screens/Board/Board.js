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
      row.push('red')
    }
    let board = []
    for (let i = 0; i < rows; i++) {
      //...row copys row otherwise shallow copy
      board.push([...row])
    }

    setBoard(board)
  }

  function changeTile(row, column) {
    //cheap enum maybe replace with switch case
    const colors = {
      red: 'blue',
      blue: 'yellow',
      yellow: 'red',
    }
    //deep copy of board
    const tempBoard = [...board]
    const columns = tempBoard[0].length
    const rows = tempBoard.length
    tempBoard[row][column] = colors[tempBoard[row][column]]

    if (row - 1 >= 0) {
      tempBoard[row - 1][column] = colors[tempBoard[row - 1][column]]
    }
    if (row + 1 < columns) {
      tempBoard[row + 1][column] = colors[tempBoard[row + 1][column]]
    }
    if (column - 1 >= 0) {
      tempBoard[row][column - 1] = colors[tempBoard[row][column - 1]]
    }
    if (column + 1 < rows) {
      tempBoard[row][column + 1] = colors[tempBoard[row][column + 1]]
    }

    setBoard(tempBoard)
  }

  function shuffleBoard(shuffles) {
    for (let i = 0; i < shuffles; i++) {
      let randomRow = Math.floor(Math.random() * rows)
      let randomColumn = Math.floor(Math.random() * columns)
      changeTile(randomRow, randomColumn)
    }
  }

  return (
    <div className='board-wrapper'>
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
