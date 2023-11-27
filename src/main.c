#include "../inc/action.h"
#include "../inc/io.h"
#include "../inc/game_data.h"
#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WINDOW_NAME "Taquin"
#define ICON_NAME "Icone"
#define IMG_PATH "images/squirrel.jpg"

int main(void)
{
    MLV_Image *img;
    Board *board_p;
    InputData input;
    Task task;

    /* Initialize */
    srand(time(NULL));

    if ((board_p = create_board()) == NULL)
        return 1;
    MLV_create_window(WINDOW_NAME, ICON_NAME, IMG_W, IMG_H);
    if ((img = MLV_load_image(IMG_PATH)) == NULL)
        return 2;

    /* Show solved state */
    display_game_data(board_p, img);
    MLV_actualise_window();

    /* Wait user input to display shuffled board */
    wait_user_input();
    shuffle_board(board_p);
    display_game_data(board_p, img);
    MLV_actualise_window();

    /* Main loop : Get input -> convert to task -> execute */
    task.type = PASS;
    while (!is_solved(board_p) && task.type != QUIT)
    {
        get_user_input(&input);
        read_input(&task, &input);
        run_task(&task, board_p, img);
    }

    /* Won => display message and quit after user input */
    if (task.type != QUIT)
    {
        display_win_msg(WIN_MSG);
        wait_user_input();
    }

    /* Free memory and exit */
    MLV_free_image(img);
    MLV_free_window();
    free(board_p);
    return 0;
}
