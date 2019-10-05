import React, { memo } from 'react'
import './Instruction.css'
function _Instruction() {
  return (
    <div className='instruction-wrapper'>
      <h2 className='instruction-header'>How to Play</h2>
      <ul className='rules'>
        <li>The goal of the game is to match the colors of all tiles</li>
        <li>
          On each click the tile itself and the adjacent ones (not diagonal)
          change the color
        </li>
        <li>
          Each change in color is following a determined order based on the
          amount of chosen colors
        </li>
      </ul>
    </div>
  )
}

export const Instruction = memo(_Instruction)
