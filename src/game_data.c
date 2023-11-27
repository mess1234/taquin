#include "../inc/game_data.h"
#include <stdlib.h>

Coord get_cell_at(const Board *board_p, Coord location)
{
    return board_p->cells[location.lin][location.col];
}

int is_solved(const Board *board_p)
{
    Coord current;
    for (current.lin = 0; current.lin < BOARD_H; current.lin++)
        for (current.col = 0; current.col < BOARD_W; current.col++)
            if (!coord_cmp(current, get_cell_at(board_p, current)))
                return 0;
    return 1;
}

int movable(const Board *board_p, Coord pos)
{
    Coord diff;
    /* check y coordinate */
    if (!(0 <= pos.lin && pos.lin < BOARD_H))
        return 0;
    /* check x coordinate */
    if (!(0 <= pos.col && pos.col < BOARD_W))
        return 0;
    /* check distance */
    diff = coord_sub(board_p->empty, pos);
    return (abs(diff.lin) + abs(diff.col)) == 1;
}