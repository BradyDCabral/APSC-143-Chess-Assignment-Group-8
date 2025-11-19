#include "board.h"

#include <stdio.h>

// GOOD
const char *player_string(enum chess_player player)
{
    switch (player)
    {
    case PLAYER_NULL:
        return "null";
    case PLAYER_WHITE:
        return "white";
    case PLAYER_BLACK:
        return "black";
    }
}


const char *player_string_short(enum chess_player player)
{
    switch (player)
    {
        case PLAYER_NULL:
            return "_";
        case PLAYER_WHITE:
            return "w";
        case PLAYER_BLACK:
            return "b";
    }
}

const char *piece_string(enum chess_piece piece)
{
    switch (piece)
    {
    case PIECE_NULL:
        return "null";
    case PIECE_PAWN:
        return "pawn";
    case PIECE_KNIGHT:
        return "knight";
    case PIECE_BISHOP:
        return "bishop";
    case PIECE_ROOK:
        return "rook";
    case PIECE_QUEEN:
        return "queen";
    case PIECE_KING:
        return "king";
    }
}

const char *piece_string_short(enum chess_piece piece)
{
    switch (piece)
    {
        case PIECE_NULL:
            return "_";
        case PIECE_PAWN:
            return "P";
        case PIECE_KNIGHT:
            return "N";
        case PIECE_BISHOP:
            return "B";
        case PIECE_ROOK:
            return "R";
        case PIECE_QUEEN:
            return "Q";
        case PIECE_KING:
            return "K";
    }
}

void board_initialize(struct chess_board *board)
{
    board->next_move_player = PLAYER_WHITE;
    // TODO: initialize the board state for a new chess game.

    // Setting all values to Null
    for (int file = 0; file < 8; ++file) {
        for (int rank = 0; rank < 8; ++rank) {
            board->Grid[file][rank][0] = PIECE_NULL;
            board->Grid[file][rank][1] = PLAYER_NULL;
        }
    }

    // initializing pawns
    // W
    for (int i = 0; i < 8; ++i) {
        board->Grid[1][i][0] = PIECE_PAWN;
        board->Grid[1][i][1] = PLAYER_WHITE;
    }

    // B
    for (int i = 0; i < 8; ++i) {
        board->Grid[6][i][0] = PIECE_PAWN;
        board->Grid[6][i][1] = PLAYER_BLACK;
    }

    // Rooks
    // W
    board->Grid[FILE_1][RANK_a][0] = PIECE_ROOK;
    board->Grid[FILE_1][RANK_a][1] = PLAYER_WHITE;

    board->Grid[FILE_1][RANK_h][0] = PIECE_ROOK;
    board->Grid[FILE_1][RANK_h][1] = PLAYER_WHITE;

    // B
    board->Grid[FILE_8][RANK_a][0] = PIECE_ROOK;
    board->Grid[FILE_8][RANK_a][1] = PLAYER_BLACK;

    board->Grid[FILE_8][RANK_h][0] = PIECE_ROOK;
    board->Grid[FILE_8][RANK_h][1] = PLAYER_BLACK;

    // Knights
    // W
    board->Grid[FILE_1][RANK_b][0] = PIECE_KNIGHT;
    board->Grid[FILE_1][RANK_b][1] = PLAYER_WHITE;

    board->Grid[FILE_1][RANK_g][0] = PIECE_KNIGHT;
    board->Grid[FILE_1][RANK_g][1] = PLAYER_WHITE;

    // B
    board->Grid[FILE_8][RANK_b][0] = PIECE_KNIGHT;
    board->Grid[FILE_8][RANK_b][1] = PLAYER_BLACK;

    board->Grid[FILE_8][RANK_g][0] = PIECE_KNIGHT;
    board->Grid[FILE_8][RANK_g][1] = PLAYER_BLACK;

    // Bishops
    // W
    board->Grid[FILE_1][RANK_c][0] = PIECE_BISHOP;
    board->Grid[FILE_1][RANK_c][1] = PLAYER_WHITE;

    board->Grid[FILE_1][RANK_f][0] = PIECE_BISHOP;
    board->Grid[FILE_1][RANK_f][1] = PLAYER_WHITE;

    // B
    board->Grid[FILE_8][RANK_c][0] = PIECE_BISHOP;
    board->Grid[FILE_8][RANK_c][1] = PLAYER_BLACK;

    board->Grid[FILE_8][RANK_f][0] = PIECE_BISHOP;
    board->Grid[FILE_8][RANK_f][1] = PLAYER_BLACK;

    // Queen
    // W
    board->Grid[FILE_1][RANK_d][0] = PIECE_QUEEN;
    board->Grid[FILE_1][RANK_d][1] = PLAYER_WHITE;

    // B
    board->Grid[FILE_8][RANK_d][0] = PIECE_QUEEN;
    board->Grid[FILE_8][RANK_d][1] = PLAYER_BLACK;

    // King
    // W
    board->Grid[FILE_1][RANK_e][0] = PIECE_KING;
    board->Grid[FILE_1][RANK_e][1] = PLAYER_WHITE;

    // B
    board->Grid[FILE_8][RANK_e][0] = PIECE_KING;
    board->Grid[FILE_8][RANK_e][1] = PLAYER_BLACK;




}

// Resets the move struct so that carry over errors don't occur
void Move_Initialize(struct chess_move *New_Move) {
    New_Move->Capture = false;
    New_Move->Castle = false;
    New_Move->Promotion_Piece = PIECE_NULL;
    New_Move->piece_type = PIECE_NULL;
    New_Move->Origin_Rank = RANK_NULL;
    New_Move->Origin_File = FILE_NULL;
    New_Move->Target_Rank = RANK_NULL;
    New_Move->Target_File = FILE_NULL;

}

void board_complete_move(const struct chess_board *board, struct chess_move *move)
{
    // TODO: complete the move.
}

void board_apply_move(struct chess_board *board, const struct chess_move *move)
{
    // TODO: apply a completed move to the board.

    // The final step is to update the turn of players in the board state.
    switch (board->next_move_player)
    {
    case PLAYER_WHITE:
        board->next_move_player = PLAYER_BLACK;
        break;
    case PLAYER_BLACK:
        board->next_move_player = PLAYER_WHITE;
        break;
    }
}

void board_summarize(const struct chess_board *board)
{
    // TODO: print the state of the game.
}

void board_print(const struct chess_board *board) {
    for (int file = FILE_8; file >= FILE_1; --file) {
        for (int rank = RANK_a; rank <= RANK_h; ++rank) {

            printf("[%s|%s]", piece_string_short(board->Grid[file][rank][0]), player_string_short(board->Grid[file][rank][1]));
        }
        printf("\n");
    }
}
