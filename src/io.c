#include "../inc/io.h"
#include <stdio.h>

/**
 * @brief Convert board coordinates to window coodinates.
 *
 * @param board board coordinates
 * @param window location to write window coordinates
 */
static void _board_to_window(Coord board, Coord *window)
{
    window->lin = board.lin * SQR_H;
    window->col = board.col * SQR_W;
}

/**
 * @brief Convert window coordinates to board coodinates.
 *
 * @param window window coordinates
 * @param board location to write board coordinates
 */
static void _window_to_board(Coord window, Coord *board)
{
    board->lin = window.lin / SQR_H;
    board->col = window.col / SQR_W;
}

/**
 * @brief Translate an InputData variable whose event is MLV_KEY to a Task
 * variable.
 *
 * @param task_p pointer to the Task to write result to
 * @param key code of the pressed key
 */
static void _read_key_event(Task *task_p, MLV_Keyboard_button key)
{
    Coord vect;
    switch (key)
    {
        case MLV_KEYBOARD_UP:       vect.lin = -1;  vect.col = +0;  break;
        case MLV_KEYBOARD_LEFT:     vect.lin = +0;  vect.col = -1;  break;
        case MLV_KEYBOARD_DOWN:     vect.lin = +1;  vect.col = +0;  break;
        case MLV_KEYBOARD_RIGHT:    vect.lin = +0;  vect.col = +1;  break;
        case MLV_KEYBOARD_ESCAPE:   task_p->type = QUIT;            return;
        case MLV_KEYBOARD_q:        task_p->type = QUIT;            return;
        default:                    task_p->type = PASS;            return;
    }
    task_p->type = MOVE_REL;
    task_p->coord = vect;
}

/**
 * @brief Translate an InputData variable whose event is MLV_MOUSE_BUTTON to a Task
 * variable.
 *
 * @param task_p pointer to the Task to write result to
 */
static void _read_mouse_event(Task *task_p)
{
    Coord mouse;
    MLV_get_mouse_position(&mouse.col, &mouse.lin);
    _window_to_board(mouse, &(task_p->coord)); /* write woord to task */
    task_p->type = MOVE_ABS;
}

/**
 * @brief Draw *board_p's empty cell on the window.
 *
 * @param board_p pointer to a board
 */
static void _draw_empty_cell(const Board *board_p)
{
    Coord window;
    _board_to_window(board_p->empty, &window);
    MLV_draw_filled_rectangle(window.col, window.lin,
                              SQR_W, SQR_H,
                              COLOR_BLACK);
}

/**
 * @brief Let C be the cell at position board_pos in *board_p. Draw C on the
 * window.
 *
 * @param board_p pointer to a board
 * @param board_pos current board coordinate of the cell to draw
 * @param img image used for the game_data
 */
static void _draw_full_cell(const Board *board_p, Coord board_pos,
                            const MLV_Image *img)
{
    Coord init_pos, window, image;
    init_pos = get_cell_at(board_p, board_pos); /* initial position of cell */
    _board_to_window(board_pos, &window);       /* where to draw */
    _board_to_window(init_pos, &image);         /* what to draw */
    MLV_draw_partial_image(img, image.col, image.lin,
                           SQR_W, SQR_H,
                           window.col, window.lin);
}

/* ---------------------------- */
/* PUBLIC FUNCTIONS DEFINITIONS */
/* ---------------------------- */

void get_user_input(InputData *input_p)
{
    input_p->event = MLV_wait_event(&(input_p->key), NULL, NULL,
                                    NULL, NULL,
                                    NULL, NULL, &(input_p->mouse_button),
                                    &(input_p->state));
}

void wait_user_input(void)
{
    MLV_Button_state state;
    do
    {
        MLV_wait_event(NULL, NULL, NULL,
                       NULL, NULL,
                       NULL, NULL, NULL,
                       &state);
    } while (state == MLV_RELEASED);
}

void read_input(Task *task_p, InputData *input_p)
{
    /* Ignore key release events */
    if (input_p->state == MLV_RELEASED)
    {
        task_p->type = PASS;
        return;
    }
    if (input_p->event == MLV_KEY)
        _read_key_event(task_p, input_p->key);
    else if (input_p->event == MLV_MOUSE_BUTTON)
        _read_mouse_event(task_p);
    else
        task_p->type = PASS; /* default : do nothing */
}

void display_game_data(const Board *board_p, const MLV_Image *img)
{
    Coord current;
    for (current.lin = 0; current.lin < BOARD_H; current.lin++)
        for (current.col = 0; current.col < BOARD_W; current.col++)
            if (!coord_cmp(current, board_p->empty))
                _draw_full_cell(board_p, current, img);
    _draw_empty_cell(board_p);
}

void update_display(const Board *board_p, Coord prev, const MLV_Image *img)
{
    _draw_full_cell(board_p, prev, img);
    _draw_empty_cell(board_p);
}

void display_win_msg(const char *msg)
{
    MLV_draw_text_box((IMG_W - TXT_BOX_W) / 2, (IMG_H - TXT_BOX_H) / 2,
                      TXT_BOX_W, TXT_BOX_H,
                      WIN_MSG, 0,
                      COLOR_BLACK, COLOR_WHITE, COLOR_BLACK,
                      MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
    MLV_actualise_window();
}

void console_print_board(const Board *board_p)
{
    Coord curr, og;
    printf("empty y : %d\n", board_p->empty.lin);
    printf("empty x : %d\n", board_p->empty.col);
    for (curr.lin = 0; curr.lin < BOARD_H; curr.lin++)
    {
        for (curr.col = 0; curr.col < BOARD_W; curr.col++)
        {
            og = get_cell_at(board_p, curr);
            printf(" (%d, %d)", og.lin, og.col);
        }
    }
}

void console_print_input(const InputData *input_p)
{
    int mouse_y, mouse_x;
    MLV_get_mouse_position(&mouse_x, &mouse_y);
    printf("DEBUG\t");
    printf("event %d\t", input_p->event);
    printf("key %d\t", input_p->key);
    printf("mouse button %d\t", input_p->mouse_button);
    printf("(%d, %d)\t", mouse_y, mouse_x);
    printf("state %d\n", input_p->state);
}