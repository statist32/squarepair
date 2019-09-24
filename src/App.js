import React, { memo } from 'react'
import { Board } from './components/screens/Board/Board'
import './App.css'
function _App() {
  return <Board />
}

export const App = memo(_App)
