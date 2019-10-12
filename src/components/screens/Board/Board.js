import React, { memo, useState, useEffect } from 'react'
import './Board.css'
import { TileRow } from './TileRow'
import { StyledButton } from '../../universal/StyledButton/StyledButton'
import {
  initBoard,
  changeTile,
  checkWin,
  undoMove,
  shuffleBoard,
} from './BoardLogic'
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

  function updateHistory(board) {
    const localHistory = [...history, board]
    setHistory(localHistory)
  }

  useEffect(() => {
    initBoard(rows, columns, colors[0], setHistory)
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, [columns, rows, colorAmount, hasWon])

  /* handleFunctions are the only non pure functions due to amount of parameter*/
  function handelChange(row, column) {
    changeTile(row, column, board, colorAmount, colors, updateHistory)

    const win = checkWin(board, rows, columns)
    if (win) {
      //flashes the background green and removes it afterwards
      setHasWon(true)
      setTimeout(() => setHasWon(false), 1000)
    }
  }
  function handleRows(rows) {
    setRows(rows)
  }
  function handleColumns(columns) {
    setColumns(columns)
  }
  function handleColorAmount(colorAmount) {
    setColorAmount(colorAmount)
  }
  function handleUndo() {
    undoMove(history, setHistory)
  }
  function handleShuffle(shuffleAmount = 20) {
    shuffleBoard(
      shuffleAmount,
      board,
      rows,
      columns,
      history,
      colorAmount,
      colors,
      updateHistory,
    )
  }
  function handleReset() {
    initBoard(rows, columns, colors[0], setHistory)
  }

  return (
    <div className='board-wrapper'>
      <div className='control-wrapper'>
        <StyledButton
          text={hasWon ? 'You did it!' : 'Shuffle'}
          onClick={() => handleShuffle()}
        />
        <StyledButton text={'Undo'} onClick={() => handleUndo()} />
        <StyledButton text={'Reset'} onClick={() => handleReset()} />
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
              onChange={e => handleColorAmount(e.target.value)}
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
