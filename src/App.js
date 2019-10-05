import React, { memo } from 'react'
import './App.css'
import { Board } from './components/screens/Board/Board'
import { Instruction } from './components/screens/Instruction/Instruction'
function _App() {
  return (
    <div className='app-wrapper'>
      <Board /> <Instruction />
    </div>
  )
}

export const App = memo(_App)
