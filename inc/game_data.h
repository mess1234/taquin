#ifndef __GAME_DATA__
#define __GAME_DATA__

#include "coord.h"

#define BOARD_H 4
#define BOARD_W 4

typedef struct _Board
{
    Coord cells[BOARD_H][BOARD_W]; /* a cell contain its starting position */
    Coord empty;                   /* location of the empty cell in board */
} Board;

/**
 * @brief Return the cell at specified location in the board.
 *
 * @param board_p pointer to the board
 * @param location coordinates of cell to return
 * @return Coord the cell
 */
Coord get_cell_at(const Board *board_p, Coord location);

/**
 * @brief Return 1 if each square is in the right cell, 0 otherwise.
 *
 * @param board_p pointer to a board
 * @return int 1 or 0
 */
int is_solved(const Board *board_p);

/**
 * @brief Return 1 if it's possible to move the cell at location pos, 0
 * otherwise.
 *
 * @param board_p pointer to the board in wich we want to move a cell
 * @param pos coordinates of the cell to move
 * @return int 1 or 0
 */
int movable(const Board *board_p, Coord pos);

#endif