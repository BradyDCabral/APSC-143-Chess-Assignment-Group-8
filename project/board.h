#ifndef APSC143__BOARD_H
#define APSC143__BOARD_H
#include <stdbool.h>

enum chess_player
{
    PLAYER_NULL = -1,
    PLAYER_WHITE,
    PLAYER_BLACK,
};

// Gets a lowercase string denoting the player.
const char *player_string(enum chess_player player);

// Gets a lowercase letter denoting the player
const char *player_string_short(enum chess_player player);

enum chess_piece
{
    PIECE_NULL = -1,
    PIECE_PAWN ,
    PIECE_KNIGHT,
    PIECE_BISHOP,
    PIECE_ROOK,
    PIECE_QUEEN,
    PIECE_KING,
};

enum chess_rank {
    RANK_a =0,
    RANK_b,
    RANK_c,
    RANK_d,
    RANK_e,
    RANK_f,
    RANK_g,
    RANK_h,
};

// This one is kind of redundent
enum chess_file {
    FILE_1 = 0,
    FILE_2,
    FILE_3,
    FILE_4,
    FILE_5,
    FILE_6,
    FILE_7,
    FILE_8,
};

// Gets a lowercase string denoting the piece type.
const char *piece_string(enum chess_piece piece);

// Gets a lowercase letter denoting the piece type
const char *piece_string_short(enum chess_piece piece);

struct chess_board
{
    enum chess_player next_move_player;

    // TODO: what other fields are needed?
    // 8x8(x2 this stores piece and color) chess board
    int Grid[8][8][2];

    // King position's (stored for convenience)
    int WKingPos[2];
    int BKingPos[2];

    // Castling booleans
    bool WLong;
    bool WShort;
    bool BLong;
    bool BShort;

    // En Passant Variables
    // Confused on this
};

struct chess_move
{
    enum chess_piece piece_type;

    // TODO: what other fields are needed?

    // Starting position of piece
    enum chess_rank Origin_Rank;
    enum chess_file Origin_File;

    // Target location of piece
    enum chess_rank Target_Rank;
    enum chess_file Target_File;

    // All move booleans
    bool Capture;
    bool Castle;

    // Used to determine promotion
    enum chess_piece Promotion_Piece;

};

// Initializes the state of the board for a new chess game.
void board_initialize(struct chess_board *board);

// Determine which piece is moving, and complete the move data accordingly.
// Panics if there is no piece which can make the specified move, or if there
// are multiple possible pieces.
void board_complete_move(const struct chess_board *board, struct chess_move *move);

// Apply move to the board. The move must already be complete, i.e., the initial
// square must be known. Panics if the move is not legal in the current board
// position.
void board_apply_move(struct chess_board *board, const struct chess_move *move);

// Classify the state of the board, printing one of the following:
// - game incomplete
// - white wins by checkmate
// - black wins by checkmate
// - draw by stalemate
void board_summarize(const struct chess_board *board);

// Prints out the state of the pieces in the board
void board_print(const struct chess_board *board);

#endif
