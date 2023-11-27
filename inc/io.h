#ifndef __IO__
#define __IO__

#include "coord.h"
#include "game_data.h"
#include <MLV/MLV_all.h>

#define IMG_H 512
#define IMG_W 512
#define SQR_H (IMG_H / BOARD_H)
#define SQR_W (IMG_W / BOARD_W)
#define TXT_BOX_H 32
#define TXT_BOX_W 256
#define WIN_MSG "YOU WON ! CONGRATULATIONS !"
#define COLOR_BLACK 0x000000ff
#define COLOR_WHITE 0xffffffff

typedef struct _InputData
{
    MLV_Event event;
    MLV_Keyboard_button key;
    MLV_Mouse_button mouse_button;
    MLV_Button_state state;
} InputData;

typedef enum _TaskType
{
    PASS,     /* skip turn */
    QUIT,     /* quit program */
    MOVE_ABS, /* move empty cell using absolute coordinates */
    MOVE_REL  /* move empty cell using relative coordinates */
} TaskType;

typedef struct _Task
{
    TaskType type;
    Coord coord;
} Task;

/* --------------- */
/* INPUT FUNCTIONS */
/* --------------- */

/**
 * @brief Get user input data and write it to input_p. Pause program until user
 * presses or release a key.
 *
 * @param input_p location to write input to
 */
void get_user_input(InputData *input_p);

/**
 * @brief Pause program until user presses a key.
 */
void wait_user_input(void);

/**
 * @brief Translate an InputData variable to a Task variable.
 *
 * @param task_p pointer to the Task to write result to
 * @param input_p pointer to the fetched input
 */
void read_input(Task *task_p, InputData *input_p);

/* ---------------- */
/* OUTPUT FUNCTIONS */
/* ---------------- */

/**
 * @brief Display current state of the game_data.
 *
 * @param board_p pointer to a board
 * @param img image used for the game_data
 */
void display_game_data(const Board *board_p, const MLV_Image *img);

/**
 * @brief Display new state of the game_data after the empty cell was swapped.
 *
 * @param board_p pointer to a board
 * @param previous previous coordinates of the empty cell
 * @param img image used for the game_data
 */
void update_display(const Board *board_p, Coord prev, const MLV_Image *img);

/**
 * @brief Display message msg in a box.
 *
 * @param msg winning message
 */
void display_win_msg(const char *msg);

/**
 * @brief Print current state of the board in console. Used for debugging.
 *
 * @param board_p pointer to the board
 */
void console_print_board(const Board *board_p);

/**
 * @brief Print input fields in console. Used for debugging.
 *
 * @param input_p pointer to the input
 */
void console_print_input(const InputData *input_p);

#endif