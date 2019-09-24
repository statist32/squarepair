import React, { memo } from 'react'
import './Tile.css'

function _Tile({ color, onClick }) {
  return (
    <div
      className='tile'
      style={{ background: color }}
      onClick={() => onClick()}></div>
  )
}

export const Tile = memo(_Tile)
