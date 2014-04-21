## Game of life

Simple implementation of Conways's »Game of Life«, written in C++ and using QT5.

#### Rules

1. Any live cell with fewer than two live neighbours dies, as if caused by under-population.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overcrowding.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

![ScreenShot](/screenshot.png)

#### Features

- start, pause and clear game
- randomly populate board with alive cells
- adjustable ratio of alive cells for population
- adjustable speed of iterations
- statistics (number of iterations and cells alive)
- create patterns by drawing on board

#### Todo

- zoom buttons: 100%, +, -
- custom board size
- toggle wrap
- prefabricated patterns
- save/load boards
