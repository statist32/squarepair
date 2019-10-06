import React, { memo, useState, useEffect } from 'react'
import './Board.css'
import { TileRow } from './TileRow'
import { StyledButton } from '../../universal/StyledButton/StyledButton'
//TODO: win condition with reduce or filter
//TODO: maybe switch to redux
function _Board() {
  const [history, setHistory] = useState([[]])
  const [hasWon, setHasWon] = useState(false)
  const [rows, setRows] = useState(3)
  const [columns, setColumns] = useState(3)
  const [colorAmount, setColorAmount] = useState(3)
  //deep deep copy of current board
  let board = history[history.length - 1].map(row => [...row])

  // const colors = ['#7800ff', '#FF7800', '#00FF78'].slice(0, colorAmount)
  const palettes = [
    ['#CE3141', '#31CEBE'],
    ['#7800ff', '#FF7800', '#00FF78'],
    ['#66D926', '#26BFD9', '#9926D9', '#D94026'],
  ]
  let colors = palettes[colorAmount - 2]

  function updateHistory(tempBoard) {
    const localHistory = [...history, tempBoard]
    setHistory(localHistory)
  }

  useEffect(() => {
    initBoard(rows, columns)
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [columns, rows])

  function initBoard(rows, columns) {
    let row = []
    for (let i = 0; i < columns; i++) {
      row.push(colors[0])
    }
    let board = []
    for (let i = 0; i < rows; i++) {
      //...row copies row otherwise shallow copy
      board.push([...row])
    }

    setHistory([board])
  }

  function manageColor(color) {
    console.log(colors)
    const index = colors.indexOf(color)
    return colors[(index + 1) % colorAmount]
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
    if (row + 1 < rows) {
      tempBoard[row + 1][column] = manageColor(tempBoard[row + 1][column])
    }
    if (column - 1 >= 0) {
      tempBoard[row][column - 1] = manageColor(tempBoard[row][column - 1])
    }
    if (column + 1 < columns) {
      tempBoard[row][column + 1] = manageColor(tempBoard[row][column + 1])
    }

    updateHistory(tempBoard)
  }

  function shuffleBoard(shuffles) {
    //click randomly  tiles
    for (let i = 0; i < shuffles; i++) {
      let randomRow = Math.floor(Math.random() * rows)
      let randomColumn = Math.floor(Math.random() * columns)
      changeTile(randomRow, randomColumn)
    }
    //prevent case that it shuffles to the goal
    //theoretically infinite recursion
    if (checkWin()) {
      shuffleBoard(shuffles)
    }
  }

  function undoMove() {
    //removes current board from history
    if (history.length - 1 > 0) {
      let tempHistory = history
      tempHistory.pop()
      setHistory([...tempHistory])
    }
  }

  function checkWin() {
    //simple win check
    let win = true
    const first = board[0][0]
    for (let i = 0; i < rows && win; i++) {
      for (let j = 0; j < columns && win; j++) {
        win = first === board[i][j] ? true : false
      }
    }
    return win
  }
  function handelChange(row, column) {
    changeTile(row, column)
    const win = checkWin()
    if (win) {
      //flashes the background green and removes it afterwards
      setHasWon(true)
      setTimeout(() => setHasWon(false), 1000)
      //delete history of last game to save memory and prevent undo
      initBoard(rows, columns)
    }
  }
  function handleRows(rows) {
    setRows(rows)
    initBoard(rows, columns)
  }
  function handleColumns(columns) {
    setColumns(columns)
    initBoard(rows, columns)
  }
  function handleColors(colorAmount) {
    setColorAmount(colorAmount)
    colors = palettes[colorAmount - 2]
    initBoard(rows, columns)
  }

  return (
    <div className='board-wrapper'>
      <div className='control-wrapper'>
        <StyledButton
          text={hasWon ? 'You did it!' : 'Shuffle'}
          onClick={() => shuffleBoard(20)}
        />
        <StyledButton text={'Undo'} onClick={() => undoMove()} />
        <StyledButton text={'Reset'} onClick={() => initBoard(rows, columns)} />
        <div className='input-wrapper'>
          <label>
            Rows:
            <input
              placeholder='Rows'
              value={rows}
              onChange={e => handleRows(e.target.value)}
              type='number'
              min='2'
              max='10'
            />
          </label>
          <label>
            Columns:{' '}
            <input
              placeholder='Columns'
              value={columns}
              onChange={e => handleColumns(e.target.value)}
              type='number'
              min='2'
              max='10'
            />
          </label>
          <label>
            Colors:
            <input
              placeholder='Colors'
              value={colorAmount}
              onChange={e => handleColors(e.target.value)}
              type='number'
              min='2'
              max='4'
            />
          </label>
        </div>
      </div>
      <div className={`board ${hasWon ? 'bg-green' : ''}`}>
        {board.map((row, index) => (
          <TileRow
            rowNumber={index}
            row={row}
            onClick={handelChange}
            key={index}
          />
        ))}
      </div>
    </div>
  )
}

export const Board = memo(_Board)
