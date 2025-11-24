#include "board.h"

#include <stdio.h>

#include "panic.h"

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

const char *string_file(enum chess_file file) {
    switch (file) {
        case FILE_NULL:
            return "NULL";
        case FILE_a:
            return "a";
        case FILE_b:
            return "b";
        case FILE_c:
            return "c";
        case FILE_d:
            return "d";
        case FILE_e:
            return "e";
        case FILE_f:
            return "f";
        case FILE_g:
            return "g";
        case FILE_h:
            return "h";
        default:
            return "UNKNOWN";
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
    for (int rank = 0; rank < 8; ++rank) {
        for (int file = 0; file < 8; ++file) {
            board->Grid[rank][file][0] = PIECE_NULL;
            board->Grid[rank][file][1] = PLAYER_NULL;
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
    board->Grid[RANK_1][FILE_a][0] = PIECE_ROOK;
    board->Grid[RANK_1][FILE_a][1] = PLAYER_WHITE;

    board->Grid[RANK_1][FILE_h][0] = PIECE_ROOK;
    board->Grid[RANK_1][FILE_h][1] = PLAYER_WHITE;

    // B
    board->Grid[RANK_8][FILE_a][0] = PIECE_ROOK;
    board->Grid[RANK_8][FILE_a][1] = PLAYER_BLACK;

    board->Grid[RANK_8][FILE_h][0] = PIECE_ROOK;
    board->Grid[RANK_8][FILE_h][1] = PLAYER_BLACK;

    // Knights
    // W
    board->Grid[RANK_1][FILE_b][0] = PIECE_KNIGHT;
    board->Grid[RANK_1][FILE_b][1] = PLAYER_WHITE;

    board->Grid[RANK_1][FILE_g][0] = PIECE_KNIGHT;
    board->Grid[RANK_1][FILE_g][1] = PLAYER_WHITE;

    // B
    board->Grid[RANK_8][FILE_b][0] = PIECE_KNIGHT;
    board->Grid[RANK_8][FILE_b][1] = PLAYER_BLACK;

    board->Grid[RANK_8][FILE_g][0] = PIECE_KNIGHT;
    board->Grid[RANK_8][FILE_g][1] = PLAYER_BLACK;

    // Bishops
    // W
    board->Grid[RANK_1][FILE_c][0] = PIECE_BISHOP;
    board->Grid[RANK_1][FILE_c][1] = PLAYER_WHITE;

    board->Grid[RANK_1][FILE_f][0] = PIECE_BISHOP;
    board->Grid[RANK_1][FILE_f][1] = PLAYER_WHITE;

    // B
    board->Grid[RANK_8][FILE_c][0] = PIECE_BISHOP;
    board->Grid[RANK_8][FILE_c][1] = PLAYER_BLACK;

    board->Grid[RANK_8][FILE_f][0] = PIECE_BISHOP;
    board->Grid[RANK_8][FILE_f][1] = PLAYER_BLACK;

    // Queen
    // W
    board->Grid[RANK_1][FILE_d][0] = PIECE_QUEEN;
    board->Grid[RANK_1][FILE_d][1] = PLAYER_WHITE;

    // B
    board->Grid[RANK_8][FILE_d][0] = PIECE_QUEEN;
    board->Grid[RANK_8][FILE_d][1] = PLAYER_BLACK;

    // King
    // W
    board->Grid[RANK_1][FILE_e][0] = PIECE_KING;
    board->Grid[RANK_1][FILE_e][1] = PLAYER_WHITE;

    // B
    board->Grid[RANK_8][FILE_e][0] = PIECE_KING;
    board->Grid[RANK_8][FILE_e][1] = PLAYER_BLACK;

    //-----OTHER VARIABLE INITIALISATION-----

    // King location's

    // W
    board->WKingPos[0] = RANK_1;
    board->WKingPos[1] = FILE_e;

    // B
    board->BKingPos[0] = RANK_8;
    board->BKingPos[1] = FILE_e;


}

void Display_Move(struct chess_move *move) {
    printf("Current board state\n");
    printf("Piece Type = %s\n", piece_string(move->piece_type));
    printf("Origin position is (%d, %d)\n", move->Origin_File, move->Origin_Rank);
    printf("Target position is (%d, %d)\n", move->Target_File, move->Target_Rank);
    printf("Capture = %d\n", move->Capture);
    printf("Castle = %d\n", move->Castle);
    printf("Promoting Piece = %s\n\n", piece_string(move->Promotion_Piece));
}

void Move_Initialize(struct chess_move *New_Move) {
    New_Move->Capture = false;
    New_Move->Castle = false;
    New_Move->Promotion_Piece = PIECE_NULL;
    New_Move->piece_type = PIECE_NULL;
    New_Move->Origin_File = FILE_NULL;
    New_Move->Origin_Rank = RANK_NULL;
    New_Move->Target_File = FILE_NULL;
    New_Move->Target_Rank = RANK_NULL;
}

// Emily
// Determine what piece is moving, complete move accordingly
// Panic if no piece can complete specified move, or if multiple pieces can do it

//Declare helper function to verify if specific move is allowed for the piece.
static bool piece_can_move(const struct chess_board *board, enum chess_piece pt, int f, int r, int tf, int tr, const struct chess_move *move) {
  // TODO: implement real conditions later
 return true;
}
void board_complete_move(const struct chess_board *board, struct chess_move *move)
{
//Get playing side
enum chess_player side = board->next_move_player;

//Step 1 - Handle Castling
if (move->Castle) {
//decide rank based on side
enum chess_rank rank;
   if (side == PLAYER_WHITE) {
       rank = RANK_1;
   } else if (side == PLAYER_BLACK) {
       rank = RANK_8;
   } else {
       panicf("invalid player in board_complete_move\n");
}
//Panic if king isn't in place
   if (board->Grid[rank][FILE_e][0] != PIECE_KING || board->Grid[rank][FILE_e][1] != side) {
      panicf("no king on starting square for castling\n");
}
//Assign rank, which remains the same when castling
     move->Origin_Rank = rank;
     move->Target_Rank = rank;
  return;
}

//Step 2 - Candidate pieces for normal (non-castling) moves

//Define piece type (pt), target file (tf) and target rank (tr)
enum chess_piece pt = move->piece_type;
int tf = move->Target_File;
int tr = move->Target_Rank;

//Create array to store candidates
int cand_files[16];
int cand_ranks[16];
int cand_count = 0;

//Scan the whole board
for (int r = 0; r < 8; r++) {
   for (int f = 0; f <8; f++) {
       enum chess_piece p_now = board->Grid[r][f][0]; //current piece
       enum chess_player c_now = board->Grid[r][f][1]; //curent color
   if (p_now != pt || c_now != side) continue; // if wrong piece or color, skip loop iterarion

   //Skip squares that don't match origin file or origin rank
   if (move->Origin_File != FILE_NULL && f != move->Origin_File) continue;
   if (move->Origin_Rank != RANK_NULL && r != move->Origin_Rank) continue;

   //Check move legality for chess piece, otherwise skip loop iteration
   if (!piece_can_move(board, pt, f, r, tf, tr, move)) continue;
//where piece_can_move is a helper function that determines whether that
//piece can move in that certain way (like if a pawn is allowed to move diagonally etc)
//Do we have something like that?

//at this point, there should be a valid candidate
      cand_files[cand_count] = f;
      cand_ranks[cand_count] = r;
      cand_count++;
   }
  }

//Step 3 - Handle Candidate Number
  if (cand_count == 0) {
      panicf("no piece can make this move\n");
   } else if (cand_count > 1) {
      panicf("multiple pieces can make this move\n");
  } else {
     move->Origin_File = cand_files[0];
     move->Origin_Rank = cand_ranks[0];
  }
}
// Owen
bool King_in_Check(struct chess_board *board, enum chess_player King_Color) {

    return false;
}

// Might be necessary (Brady)
bool King_in_Checkmate(struct chess_board *board, enum chess_player King_Color) {
    return false;
}

// Brady
void board_apply_move(struct chess_board *board, const struct chess_move *move)
{
    // TODO: apply a completed move to the board.

    bool Legal = true;

    // Check if move is legal


    // Get king location as a pointer
    int *KingPosPtr = (board->next_move_player == PLAYER_WHITE ? &board->WKingPos[0] : &board->BKingPos[0]);

    // King
    // Normal King moves
    if (move->piece_type == PIECE_KING) {
        if (KingPosPtr[0] - move->Target_Rank > 1 || KingPosPtr[1] - move->Target_File > 1) {
            Legal = false;
        }

    }



    if (Legal == false) {
        panicf("illegal move : %s from %s%d to %s%d", piece_string(move->piece_type), string_file(move->Origin_File),
            move->Origin_Rank + 1, string_file(move->Target_File), move->Target_Rank+1);
    }

    // Doesn't do the check if it is a castle as that requires a different form of check
    if (move->Castle == true && Legal == true) {
        // Puts king in Check
        // Simulate the move

        enum chess_piece Sim_Elimination = board->Grid[move->Target_Rank][move->Target_File][0];
        enum chess_player Sim_Elimination_Color = board->Grid[move->Target_Rank][move->Target_File][1];

        // if the king gets put in check then undo that move
        // Prevent piece from eliminating own piece
        if (Sim_Elimination_Color == board->next_move_player) {
            Legal = false;
        }
        // Gonnna make the move
        if (Legal ==  true) {

        }
    }

    // The final step is to update the turn of players in the board state.
    switch (board->next_move_player)
    {
    case PLAYER_WHITE:
        board->next_move_player = PLAYER_BLACK;
        break;
    case PLAYER_BLACK:
        board->next_move_player = PLAYER_WHITE;
        break;
    default:
        panicf("Error Swapping current Player");
    }
}

// Emily
void board_summarize(const struct chess_board *board)
{
    // TODO: print the state of the game.
}

void board_print(const struct chess_board *board) {
    for (int rank = RANK_8; rank >= RANK_1; --rank) {
        for (int file = FILE_a; file <= FILE_h; ++file) {

            printf("[%s|%s]", piece_string_short(board->Grid[rank][file][0]), player_string_short(board->Grid[rank][file][1]));
        }
        printf("\n");
    }
}
