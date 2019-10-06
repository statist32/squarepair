import React, { memo } from 'react'
import './StyledButton.css'
function _StyledButton({ text, onClick, style }) {
  return (
    <div className='styled-button' style={style} onClick={() => onClick()}>
      {text}
    </div>
  )
}

export const StyledButton = memo(_StyledButton)
