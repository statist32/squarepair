export function initBoard(rows, columns, color, setHistory) {
  let row = []
  for (let i = 0; i < columns; i++) {
    row.push(color)
  }
  let board = []
  for (let i = 0; i < rows; i++) {
    //...row copies row otherwise shallow copy
    board.push([...row])
  }

  setHistory([board])
}

export function manageColor(color, colorAmount, colors) {
  const index = colors.indexOf(color)
  return colors[(index + 1) % colorAmount]
}
export function changeTile(
  row,
  column,
  board,
  colorAmount,
  colors,
  updateHistory,
) {
  //deep copy of board
  const tempBoard = [...board]
  const columns = tempBoard[0].length
  const rows = tempBoard.length
  tempBoard[row][column] = manageColor(
    tempBoard[row][column],
    colorAmount,
    colors,
  )

  for (let offset = -1; offset < 3; offset += 2) {
    if (row + offset >= 0 && row + offset < rows) {
      tempBoard[row + offset][column] = manageColor(
        tempBoard[row + offset][column],
        colorAmount,
        colors,
      )
    }
    if (column + offset >= 0 && column + offset < columns) {
      tempBoard[row][column + offset] = manageColor(
        tempBoard[row][column + offset],
        colorAmount,
        colors,
      )
    }
  }

  updateHistory(tempBoard)
}

export function shuffleBoard(
  shuffles,
  board,
  rows,
  columns,
  history,
  colorAmount,
  colors,
  updateHistory,
) {
  //click randomly  tiles
  const tempBoard = board.map(row => [...row])
  for (let i = 0; i < shuffles; i++) {
    let randomRow = Math.floor(Math.random() * rows)
    let randomColumn = Math.floor(Math.random() * columns)
    changeTile(
      randomRow,
      randomColumn,
      tempBoard,
      colorAmount,
      colors,
      updateHistory,
    )
  }
  //prevent case that it shuffles to the goal
  //theoretically infinite recursion
  if (checkWin(board, rows, columns)) {
    shuffleBoard(
      shuffles,
      tempBoard,
      rows,
      columns,
      history,
      colorAmount,
      colors,
      updateHistory,
    )
  }
  updateHistory(tempBoard)
}

export function undoMove(history, setHistory) {
  //removes current board from history
  if (history.length - 1 > 0) {
    let tempHistory = history
    tempHistory.pop()
    setHistory([...tempHistory])
  }
}

export function checkWin(board, rows, columns) {
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
