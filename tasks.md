## States
3 states to start with:
> **Game intro**: Will display 'Tetris' with a start button.

> **Play area**: Will contain the play area.

> **Game over**: Game over screen.

Update:
> get the current tetronomio as `currentTetronomio`.

> move downwards `currentTetronomio`.

> if tetronomio collides with a `Component as c`:

>> save `currentTetronmio`.

>> if line is completed:

>>> increment score.

>>> remove line.

>>> insert row at top.

>> generate a new `currentTetronomio`.


save `currentTetronmio`:
> get position of `currentTetronomio` as `pos`.

> set in `playfield` the join with `currentTetronomio` starting at `pos` as filled.

>> for row in range(4):

>>> for col in range(4):

>>>> if tetronomio[row][col]:

>>>>> const x = pos.x; const y = pos.y;

>>>>> playfield[y + row][x + col] = 1
