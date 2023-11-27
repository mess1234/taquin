#include "../inc/action.h"
#include "../inc/coord.h"
#include <stdio.h>
#include <stdlib.h>

#define SHUFFLE_MOVES (2 * BOARD_H * BOARD_W)

/**
 * @brief Modify a cell inside the board.
 *
 * @param board_p pointer to the board
 * @param location coordinates of cell to change
 * @param cell new value of the cell
 */
static void _set_cell_at(Board *board_p, Coord location, Coord cell)
{
    board_p->cells[location.lin][location.col] = cell;
}

/**
 * @brief Swap the cell at specified location with the board's empty cell.
 *
 * @param board_p pointer to the board
 * @param location coordinates of the cell to swap
 */
static void _swap(Board *board_p, Coord location)
{
    Coord empty, other;
    /* Get cells */
    empty = get_cell_at(board_p, board_p->empty); /* get empty cell */
    other = get_cell_at(board_p, location);       /* get nonempty cell */
    /* Swap cells */
    _set_cell_at(board_p, location, empty);       /* move empty cell */
    _set_cell_at(board_p, board_p->empty, other); /* move nonempty cell */
    /* Update empty cells coordinates */
    board_p->empty = location;
}

/**
 * @brief Return a randomly chosen vector in the set
 * {(0, 1), (1, 0), (0, -1), (-1, 0)}.
 *
 * @return Coord (0, 1), (1, 0), (0, -1) or (-1, 0)
 */
static Coord _random_vector(void)
{
    Coord res;
    div_t division;
    division = div(rand() % 4, 2);
    res.lin = division.quot - division.rem;
    res.col = division.quot + division.rem - 1;
    return res;
}

/* ---------------------------- */
/* PUBLIC FUNCTIONS DEFINITIONS */
/* ---------------------------- */

Board *create_board(void)
{
    Board *board_p;
    Coord current;
    /* Allocate memory for the board */
    board_p = (Board *)malloc(1 * sizeof(Board));
    if (board_p == NULL)
    {
        fprintf(stderr, "Could not create board\n");
        return NULL;
    }
    /* Fill each cell of the board */
    for (current.lin = 0; current.lin < BOARD_H; current.lin++)
        for (current.col = 0; current.col < BOARD_W; current.col++)
            _set_cell_at(board_p, current, current);
    board_p->empty.lin = BOARD_W - 1;
    board_p->empty.col = BOARD_H - 1;
    return board_p;
}

void shuffle_board(Board *board_p)
{
    Coord neighbor;
    int i;
    for (i = SHUFFLE_MOVES; 0 < i; i--)
    {
        /* Choose neighbor */
        neighbor = coord_add(board_p->empty, _random_vector());
        /* Make a legal move */
        if (movable(board_p, neighbor))
            _swap(board_p, neighbor);
    }
}

void run_task(Task *task_p, Board *board_p, const MLV_Image *img)
{
    Coord previous, move;
    if (task_p->type == QUIT || task_p->type == PASS)
        return;
    /* Compute coordinates of the cell to move */
    if (task_p->type == MOVE_ABS)
        move = task_p->coord;
    else if (task_p->type == MOVE_REL)
        move = coord_add(task_p->coord, board_p->empty);
    /* Move */
    if (movable(board_p, move))
    {
        previous = board_p->empty;
        _swap(board_p, move);
        update_display(board_p, previous, img);
        MLV_actualise_window();
    }
}