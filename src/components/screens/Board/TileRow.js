import React, { memo } from 'react'
import './TileRow.css'
import { Tile } from './Tile'

function _TileRow({ row, rowNumber, onClick }) {
  return (
    <div className='tile-row-wrapper'>
      {row.map((entry, index) => (
        <Tile
          color={entry}
          onClick={() => onClick(rowNumber, index)}
          key={index}
        />
      ))}
    </div>
  )
}
export const TileRow = memo(_TileRow)
