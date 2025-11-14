#include <stdio.h>

#include "board.h"
#include "parser.h"

int main()
{

    struct chess_board board;
    board_initialize(&board);


    board_print(&board);

    struct chess_move move;
    while (parse_move(&move))
    {
        board_complete_move(&board, &move);
        board_apply_move(&board, &move);
    }

    board_summarize(&board);


    return 0;
}
