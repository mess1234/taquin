#ifndef __ACTION__
#define __ACTION__

#include "game_data.h"
#include "io.h"
#include <MLV/MLV_all.h>

/**
 * @brief Create a board and return a pointer to it. Return NULL if error.
 *
 * @return Board* pointer to the board
 */
Board *create_board(void);

/**
 * @brief Shuffle the board's cells to a solvable arrangement.
 *
 * @param board_p pointer to the board
 */
void shuffle_board(Board *board_p);

/**
 * @brief Execute a task.
 *
 * @param task_p location of the task
 * @param board_p Pointer to the board affected the task
 * @param img Image used to display the board
 */
void run_task(Task *task_p, Board *board_p, const MLV_Image *img);

#endif