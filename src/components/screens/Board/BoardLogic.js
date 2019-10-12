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

  if (row - 1 >= 0) {
    tempBoard[row - 1][column] = manageColor(
      tempBoard[row - 1][column],
      colorAmount,
      colors,
    )
  }
  if (row + 1 < rows) {
    tempBoard[row + 1][column] = manageColor(
      tempBoard[row + 1][column],
      colorAmount,
      colors,
    )
  }
  if (column - 1 >= 0) {
    tempBoard[row][column - 1] = manageColor(
      tempBoard[row][column - 1],
      colorAmount,
      colors,
    )
  }
  if (column + 1 < columns) {
    tempBoard[row][column + 1] = manageColor(
      tempBoard[row][column + 1],
      colorAmount,
      colors,
    )
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
