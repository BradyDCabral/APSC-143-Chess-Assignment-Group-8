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

    // Set enPassent to null
    board->EnPassant_Coord[0] = RANK_NULL;
    board->EnPassant_Coord[1] = FILE_NULL;

    // King bool
    // white castling
    board->WLong = true;
    board->WShort = true;

    // Black castling
    board->BLong = true;
    board->BShort = true;

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

int sign_int(int input_num) {
    if (input_num < 0) return -1;
    if (input_num == 0) return 0;
    if (input_num > 1) return 1;
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
static bool piece_can_move(const struct chess_board *board,
                           enum chess_piece pt,
                           int f, int r, int tf,
                           int tr) {

 //Get player's side
    enum chess_player side = board->Grid[r][f][1];

//Get contents of target square
    enum chess_piece target_piece = board->Grid[tr][tf][0];
    enum chess_player target_player = board->Grid[tr][tf][1];

 // Forbid moving to the same square
    if (tf == f && tr == r) { return false; }

//Forbid removing one's piece
    if (side == target_player && target_player != PLAYER_NULL) { return false; }

    // CHANGE OF POSITION AND SIGN OF CHANGE OF POSITION
    int delta_Rank = tr - r;
    int delta_Rank_Sign = sign_int(delta_Rank);
    int delta_File = tf - f;
    int delta_File_Sign = sign_int(delta_File);

 // Switch statement for each piece
    switch (pt) {
      case PIECE_PAWN:
        //pawn can only move one square forward and target must be empty
        if ((side == PLAYER_WHITE && tf == f && tr == r + 1 && target_piece == PIECE_NULL) ||
            (side == PLAYER_BLACK && tf == f && tr == r - 1 && target_piece == PIECE_NULL) ) {
              return true; }
        //double step from starting rank only, intermediate squares must be empty
        if ((side == PLAYER_WHITE
               && r == 1
               && tf == f
               && tr == r + 2
               && target_piece == PIECE_NULL
               && board->Grid[r+1][f][0] == PIECE_NULL) ||
            (side == PLAYER_BLACK
               && r == 6
               && tf == f
               && tr == r - 2
               && target_piece == PIECE_NULL
               && board->Grid[r-1][f][0] == PIECE_NULL) ) {
            return true; }
        //captures diagonally, only if target square isn't empty
            if (side == PLAYER_WHITE &&
            tr == r + 1 &&
            (tf == f + 1 || tf == f - 1) &&
            target_piece != PIECE_NULL) {
                return true;
            }

            if (side == PLAYER_BLACK &&
                tr == r - 1 &&
                (tf == f + 1 || tf == f - 1) &&
                target_piece != PIECE_NULL) {
                return true;
                }
            return false; //default to false, every other case is illegal for a pawn

      case PIECE_KNIGHT:
            //moves in L-shape => either (±1, ±2) or (±2, ±1)
            if ( (tf == f + 1 && (tr == r + 2 || tr == r - 2)) ||
                     (tf == f - 1 && (tr == r + 2 || tr == r - 2)) ||
                     (tf == f + 2 && (tr == r + 1 || tr == r - 1)) ||
                     (tf == f - 2 && (tr == r + 1 || tr == r - 1)) ) {
                return true; }
            return false; //default to false, every other case is illegal for a knight

        case PIECE_KING:
        //one square in any direction
          if ((tf == f + 1 && tr == r) ||
              (tf == f - 1 && tr == r) ||
              (tf == f && tr == r + 1) ||
              (tf == f && tr == r - 1) ||
              (tf == f + 1 && tr == r + 1) ||
              (tf == f + 1 && tr == r - 1) ||
              (tf == f - 1 && tr == r + 1) ||
              (tf == f - 1 && tr == r - 1)) {
                 return true;
              }
            // Castling is handled in board_complete_move
            return false; //default to false, every other case is illegal for a king
        case PIECE_ROOK:
            if (delta_File_Sign * delta_File_Sign + delta_Rank_Sign * delta_Rank_Sign == 1) {
                int temp_r = r;
                int temp_f = f;
                bool pass = true;
                do {
                    temp_r += delta_Rank_Sign;
                    temp_f += delta_File_Sign;
                    if (board->Grid[temp_r][temp_f][0] != PIECE_NULL) {
                        pass = false;
                        break;
                    }
                } while ((temp_r + delta_Rank_Sign >= RANK_1 && temp_r + delta_Rank_Sign <= RANK_8 && temp_f + delta_File_Sign >= FILE_a && temp_f + delta_File_Sign <= FILE_h)
                    & !(temp_r + delta_Rank_Sign == tr && temp_f + delta_File_Sign == tf ));

                return pass;
            }


            return false;
            break;
        case PIECE_BISHOP:

            // Check if it is moving diagonally
            if (delta_File * delta_File_Sign == delta_Rank * delta_Rank_Sign && delta_Rank_Sign != 0 && delta_File_Sign != 0) {
                int temp_r = r;
                int temp_f = f;
                bool pass = true;
                // check if it is lands on piece when moving
                do {
                    temp_r += delta_Rank_Sign;
                    temp_f += delta_File_Sign;
                    if (board->Grid[temp_r][temp_f][0] != PIECE_NULL) {
                        pass = false;
                        break;
                    }
                } while ((temp_r + delta_Rank_Sign >= RANK_1 && temp_r + delta_Rank_Sign <= RANK_8 && temp_f + delta_File_Sign >= FILE_a && temp_f + delta_File_Sign <= FILE_h)
                    & !(temp_r + delta_Rank_Sign == tr && temp_f + delta_File_Sign == tf ));

                return pass;
            }

            return false;
        case PIECE_QUEEN:

            // check if diagonal movement or horizontal or vertical movement
            if ((delta_File * delta_File_Sign == delta_Rank * delta_Rank_Sign && delta_Rank_Sign != 0 && delta_File_Sign != 0)
                || (delta_File_Sign * delta_File_Sign + delta_Rank_Sign * delta_Rank_Sign == 1)) {
                int temp_r = r;
                int temp_f = f;
                bool pass = true;
                // check if it is lands on piece when moving
                do {
                    temp_r += delta_Rank_Sign;
                    temp_f += delta_File_Sign;
                    if (board->Grid[temp_r][temp_f][0] != PIECE_NULL && !(temp_r == tr && temp_f == tf)) {
                        pass = false;
                        break;
                    }
                // TODO : Fix while loop conditions
                } while ((temp_r + delta_Rank_Sign >= RANK_1 && temp_r + delta_Rank_Sign <= RANK_8 && temp_f + delta_File_Sign >= FILE_a && temp_f + delta_File_Sign <= FILE_h)
                    & !(temp_r + delta_Rank_Sign == tr && temp_f + delta_File_Sign == tf ));

                return pass;
            }
            return false;
        default:
            return false;

     }

}

void board_complete_move(const struct chess_board *board, struct chess_move *move)
{
//Get playing side
enum chess_player side = board->next_move_player;
    //Define piece type (pt), target file (tf) and target rank (tr)
    enum chess_piece pt = move->piece_type;
    int tf = move->Target_File;
    int tr = move->Target_Rank;

//Step 1 - Handle Castling
if (move->Castle) {
//decide rank based on side
enum chess_rank rank;
   if (side == PLAYER_WHITE) {
       rank = RANK_1;
   } else if (side == PLAYER_BLACK) {
       rank = RANK_8;
   } else {
       panicf("move completion error: %s %s to %s%d\n",
           player_string(side),
           piece_string(pt),
           string_file(tf),
           tf + 1);
   }
//Panic if king isn't in place
   if (board->Grid[rank][FILE_e][0] != PIECE_KING || board->Grid[rank][FILE_e][1] != side) {
       panicf("move completion error: %s %s to %s%d\n",
            player_string(side),
            piece_string(pt),
            string_file(tf),
            tf + 1);
}
//Assign rank, which remains the same when castling
     move->Origin_Rank = rank;
     move->Target_Rank = rank;
  return;
}

//Step 2 - Candidate pieces for normal (non-castling) moves

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
   if (!piece_can_move(board, pt, f, r, tf, tr)) continue;
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
      panicf("no move : move completion error: %s %s to %s%d\n",
           player_string(side),
           piece_string(pt),
           string_file(tf),
           tr + 1);
   } else if (cand_count > 1) {
       panicf("too many moves : move completion error: %s %s to %s%d\n",
            player_string(side),
            piece_string(pt),
            string_file(tf),
            tr + 1);
  } else {
     move->Origin_File = cand_files[0];
     move->Origin_Rank = cand_ranks[0];
  }
}
// Owen
bool King_in_Check(struct chess_board *board, enum chess_player King_Color) {

    int King_rank, King_file;
    enum chess_player enemy;

    if (King_Color == PLAYER_WHITE) {
        King_rank = board->WKingPos[0];
        King_file = board->WKingPos[1];
        enemy = PLAYER_BLACK;
    } else if (King_Color == PLAYER_BLACK) {
        King_rank = board->BKingPos[0];
        King_file = board->BKingPos[1];
        enemy = PLAYER_WHITE;
    } else {
        panicf("King_in_Check called with invalid king color\n");
    }

    if (King_Color == PLAYER_WHITE) {
        int r = King_rank + 1;
        int f_left  = King_file - 1;
        int f_right = King_file + 1;
        if (r >= 0 && r < 8 && f_left >= 0 && f_left < 8) {
            if (board->Grid[r][f_left][0] == PIECE_PAWN && board->Grid[r][f_left][1] == PLAYER_BLACK) {
                return true;
            }
        }
        if (r >= 0 && r < 8 && f_right >= 0 && f_right < 8) {
            if (board->Grid[r][f_right][0] == PIECE_PAWN && board->Grid[r][f_right][1] == PLAYER_BLACK) {
                return true;
            }
        }
    } else {
        int r = King_rank - 1;
        int f_left  = King_file - 1;
        int f_right = King_file + 1;
        if (r >= 0 && r < 8 && f_left >= 0 && f_left < 8) {
            if (board->Grid[r][f_left][0] == PIECE_PAWN && board->Grid[r][f_left][1] == PLAYER_WHITE) {
                return true;
            }
        }
        if (r >= 0 && r < 8 && f_right >= 0 && f_right < 8) {
            if (board->Grid[r][f_right][0] == PIECE_PAWN && board->Grid[r][f_right][1] == PLAYER_WHITE) {
                return true;
            }
        }
    }

    const int knight_offsets[8][2] = {
        { 1,  2}, { 2,  1},
        { 2, -1}, { 1, -2},
        {-1, -2}, {-2, -1},
        {-2,  1}, {-1,  2}
    };
    for (int i = 0; i < 8; ++i) {
        int r = King_rank + knight_offsets[i][0];
        int f = King_file + knight_offsets[i][1];
        if (r < 0 || r >= 8 || f < 0 || f >= 8) continue;
        if (board->Grid[r][f][0] == PIECE_KNIGHT && board->Grid[r][f][1] == enemy) {
            return true;
        }
    }

    const int rook_dirs[4][2] = {
        { 1,  0}, {-1,  0},
        { 0,  1}, { 0, -1}
    };
    for (int d = 0; d < 4; ++d) {
        int dr = rook_dirs[d][0];
        int df = rook_dirs[d][1];
        int r = King_rank + dr;
        int f = King_file + df;
        while (r >= 0 && r < 8 && f >= 0 && f < 8) {
            enum chess_piece p = board->Grid[r][f][0];
            enum chess_player c = board->Grid[r][f][1];
            if (p != PIECE_NULL) {
                if (c == enemy && (p == PIECE_ROOK || p == PIECE_QUEEN)) {
                    return true;
                }
                break;
            }
            r += dr;
            f += df;
        }
    }

    const int bishop_dirs[4][2] = {
        { 1,  1}, { 1, -1},
        {-1,  1}, {-1, -1}
    };
    for (int d = 0; d < 4; ++d) {
        int dr = bishop_dirs[d][0];
        int df = bishop_dirs[d][1];
        int r = King_rank + dr;
        int f = King_file + df;
        while (r >= 0 && r < 8 && f >= 0 && f < 8) {
            enum chess_piece p = board->Grid[r][f][0];
            enum chess_player c = board->Grid[r][f][1];
            if (p != PIECE_NULL) {
                if (c == enemy && (p == PIECE_BISHOP || p == PIECE_QUEEN)) {
                    return true;
                }
                break;
            }
            r += dr;
            f += df;
        }
    }

    for (int dr = -1; dr <= 1; ++dr) {
        for (int df = -1; df <= 1; ++df) {
            if (dr == 0 && df == 0) continue;
            int r = King_rank + dr;
            int f = King_file + df;
            if (r < 0 || r >= 8 || f < 0 || f >= 8) continue;
            if (board->Grid[r][f][0] == PIECE_KING && board->Grid[r][f][1] == enemy) {
                return true;
            }
        }
    }

    return false;
}


// Might be necessary (Brady)
// Nevermind is redundent will be deleted later
bool King_in_Checkmate(struct chess_board *board, enum chess_player King_Color) {
    // finds piece on king_color that can move
    for (int piece_origin_rank = RANK_1; piece_origin_rank <= RANK_8; piece_origin_rank++) {
        for (int piece_origin_file = FILE_a; piece_origin_file <= FILE_h; piece_origin_file++) {

            if (board->Grid[piece_origin_rank][piece_origin_file][1] == King_Color) {
                // determine if piece can move to spot

            }
        }
    }


    return false;
}

// Brady
void board_apply_move(struct chess_board *board, const struct chess_move *move)
{
    // TODO: apply a completed move to the board.

    bool Legal = true;

    bool EnPassant = false;

    // Check if move is legal


    // Get king location as a pointer
    int *KingPosPtr = (board->next_move_player == PLAYER_WHITE ? &board->WKingPos[0] : &board->BKingPos[0]);


    // if Pawn moving 2 spaces then can be en passented
    if (move->piece_type == PIECE_PAWN) {
        if (move->Origin_Rank - move->Target_Rank == 2 || move->Origin_Rank - move->Target_Rank == -2) {
            board->EnPassant_Coord[0] = move->Target_Rank;
            board->EnPassant_Coord[1] = move->Origin_File;
        }
    }


    // Doesn't do the check if it is a castle as that requires a different form of check
    if (move->Castle == false && Legal == true) {
        // Puts king in Check
        // Simulate the move

        enum chess_piece Sim_Elimination = board->Grid[move->Target_Rank][move->Target_File][0];
        enum chess_player Sim_Elimination_Color = board->Grid[move->Target_Rank][move->Target_File][1];

        // special elimination if en passent
        if (move->piece_type == PIECE_PAWN && move->Capture && Sim_Elimination == PIECE_NULL) {
            if (board->EnPassant_Coord[0] == move->Origin_Rank && board->EnPassant_Coord[1] == move->Target_File) {
                EnPassant = true;
                Sim_Elimination = board->Grid[board->EnPassant_Coord[0]][board->EnPassant_Coord[1]][0];
                Sim_Elimination_Color = board->Grid[board->EnPassant_Coord[0]][board->EnPassant_Coord[1]][1];
            }
        }

        // Checks if piece marked to capture but doesnt capture
        if (move->Capture == true && Sim_Elimination == PIECE_NULL) {
            panicf("illegal move : %s from %s%d to %s%d", piece_string(move->piece_type), string_file(move->Origin_File),
                move->Origin_Rank + 1, string_file(move->Target_File), move->Target_Rank+1);
        }

        // if the king gets put in check then undo that move
        // Prevent piece from eliminating own piece or eliminating when not marked in notation
        if (Sim_Elimination_Color == board->next_move_player || (Sim_Elimination != PIECE_NULL && move->Capture == false)) {
            Legal = false;
        }

        // Gonnna make the move
        if (Legal == true) {
            board->Grid[move->Target_Rank][move->Target_File][0] = move->piece_type;
            board->Grid[move->Target_Rank][move->Target_File][1] = board->next_move_player;
            board->Grid[move->Origin_Rank][move->Origin_File][0] = PIECE_NULL;
            board->Grid[move->Origin_Rank][move->Origin_File][1] = PLAYER_NULL;

            if (EnPassant) {
                board->Grid[board->EnPassant_Coord[0]][board->EnPassant_Coord[1]][0] = PIECE_NULL;
                board->Grid[board->EnPassant_Coord[0]][board->EnPassant_Coord[1]][1] = PLAYER_NULL;
            }

            // promotes piece if necessary
            if (move->Promotion_Piece != PIECE_NULL && move->piece_type == PIECE_PAWN) {
                if (board->next_move_player == PLAYER_WHITE && move->Target_Rank == RANK_8) {
                    board->Grid[move->Target_Rank][move->Target_File][0] = move->Promotion_Piece;
                } else if (board->next_move_player == PLAYER_BLACK && move->Target_Rank == RANK_1) {
                    board->Grid[move->Target_Rank][move->Target_File][0] = move->Promotion_Piece;
                } else {
                    Legal = false;
                }

            } else if (move->Promotion_Piece != PIECE_NULL) {
                Legal = false;
            }

            if (move->piece_type == PIECE_KING) {
                if (board->next_move_player == PLAYER_WHITE) {
                    board->WKingPos[0] = move->Target_Rank;
                    board->WKingPos[1] = move->Target_File;
                } else if (board->next_move_player == PLAYER_BLACK) {
                    board->BKingPos[0] = move->Target_Rank;
                    board->BKingPos[1] = move->Target_File;
                }
            }

            // If move puts king in check then it isn't legal
            if (King_in_Check(board, board->next_move_player)) {
                // Might be unnecessary to put everything back but could be helpful when debugging
                if (EnPassant) {
                    board->Grid[board->EnPassant_Coord[0]][board->EnPassant_Coord[1]][0] = Sim_Elimination;
                    board->Grid[board->EnPassant_Coord[0]][board->EnPassant_Coord[1]][1] = Sim_Elimination_Color;
                } else {
                    board->Grid[move->Target_Rank][move->Target_File][0] = Sim_Elimination;
                    board->Grid[move->Target_Rank][move->Target_File][1] = Sim_Elimination_Color;
                }
                board->Grid[move->Origin_Rank][move->Origin_File][0] = move->piece_type;
                board->Grid[move->Origin_Rank][move->Origin_File][1] = board->next_move_player;

                if (move->piece_type == PIECE_KING) {
                    if (board->next_move_player == PLAYER_WHITE) {
                        board->WKingPos[0] = move->Origin_Rank;
                        board->WKingPos[1] = move->Origin_File;
                    } else if (board->next_move_player == PLAYER_BLACK) {
                        board->BKingPos[0] = move->Origin_Rank;
                        board->BKingPos[1] = move->Origin_File;
                    }
                }




                Legal = false;
            }

        }
    } else if (move->Castle == true && Legal == true) {
        // Determines if it is even legal to start the castling move
        if (move->Origin_File != FILE_e) {
            Legal = false;
        } else {
            if (board->next_move_player == PLAYER_WHITE) {
                if (move->Target_File == FILE_g && board->WShort == false) {
                    Legal = false;
                } else if (move->Target_File == FILE_c && board->WLong == false) {
                    Legal = false;
                }
            } else if (board->next_move_player == PLAYER_BLACK) {
                if (move->Target_File == FILE_g && board->BShort == false) {
                    Legal = false;
                } else if (move->Target_File == FILE_c && board->BLong == false) {
                    Legal = false;
                }
            } else {
                Legal = false;
            }
        }
        if (Legal == true) {
            int move_amount = (move->Target_File - move->Origin_File) /2;
            for (int i = 0; i < 2; i++) {
                if (board->Grid[move->Target_Rank][(board->next_move_player== PLAYER_WHITE ? board->WKingPos[1] : board->BKingPos[1]) + move_amount][0] != PIECE_NULL) {
                    Legal = false;
                    break;
                }
                board->Grid[move->Target_Rank]
                    [(board->next_move_player== PLAYER_WHITE ? board->WKingPos[1] : board->BKingPos[1]) + move_amount][0] = move->piece_type;
                board->Grid[move->Target_Rank]
                    [(board->next_move_player== PLAYER_WHITE ? board->WKingPos[1] : board->BKingPos[1]) + move_amount][1] = board->next_move_player;
                board->Grid[move->Target_Rank]
                    [(board->next_move_player== PLAYER_WHITE ? board->WKingPos[1] : board->BKingPos[1])][0] = PIECE_NULL;
                board->Grid[move->Target_Rank][(board->next_move_player== PLAYER_WHITE ? board->WKingPos[1] : board->BKingPos[1])][1] = PLAYER_NULL;


                if (board->next_move_player == PLAYER_WHITE) {
                    board->WKingPos[1] += move_amount;
                } else if (board->next_move_player == PLAYER_BLACK) {
                    board->BKingPos[1] += move_amount;
                }

                if (King_in_Check(board, board->next_move_player)) {
                    Legal = false;
                    break;
                }
            }

        }
        // Swap the rook into place
        if (Legal == true) {
            // Check if Rook is in right position
            // short castle
            if (move->Target_File == FILE_g
                && board->Grid[(board->next_move_player == PLAYER_WHITE ? RANK_1 : RANK_8)][FILE_h][0] == PIECE_ROOK) {
                enum chess_rank temp_Rook_Rank = (board->next_move_player == PLAYER_WHITE ? RANK_1 : RANK_8);

                // Swap Rook into place
                board->Grid[temp_Rook_Rank][FILE_f][0] = PIECE_ROOK;
                board->Grid[temp_Rook_Rank][FILE_f][1] = board->next_move_player;

                board->Grid[temp_Rook_Rank][FILE_h][0] = PIECE_NULL;
                board->Grid[temp_Rook_Rank][FILE_h][1] = PLAYER_NULL;
            } /* Long Castle */ else if (move->Target_File == FILE_c
                && board->Grid[(board->next_move_player == PLAYER_WHITE ? RANK_1 : RANK_8)][FILE_a][0] == PIECE_ROOK) {
                enum chess_rank temp_Rook_Rank = (board->next_move_player == PLAYER_WHITE ? RANK_1 : RANK_8);

                // Swap Rook into place
                board->Grid[temp_Rook_Rank][FILE_d][0] = PIECE_ROOK;
                board->Grid[temp_Rook_Rank][FILE_d][1] = board->next_move_player;

                board->Grid[temp_Rook_Rank][FILE_a][0] = PIECE_NULL;
                board->Grid[temp_Rook_Rank][FILE_a][1] = PLAYER_NULL;
            } else {
                Legal = false;
            }


        }

    }

    if (Legal == false) {
        panicf("illegal move : %s from %s%d to %s%d", piece_string(move->piece_type), string_file(move->Origin_File),
            move->Origin_Rank + 1, string_file(move->Target_File), move->Target_Rank+1);
    }



    // Designates if the Castling can be done started
    if (move->piece_type == PIECE_KING) {
        if (board->next_move_player == PLAYER_WHITE) {
            board->WLong = false;
            board->WShort = false;
        } else if (board->next_move_player == PLAYER_BLACK) {
            board->BLong = false;
            board->BShort = false;
        }
    }
    // Check if errors
    if (move->piece_type == PIECE_ROOK) {
        if (move->Origin_File - move->Target_File  != 0) {
            if (board->next_move_player == PLAYER_WHITE) {
                if (board->WLong == true && move->Origin_File == FILE_a) {
                    board->WLong = false;
                } else if (board->WShort == true && move->Origin_File == FILE_h) {
                    board->WShort = false;
                }

            } else if (board->next_move_player == PLAYER_BLACK) {
                if (board->BLong == true && move->Origin_File == FILE_a) {
                    board->BLong = false;
                } else if (board->BShort == true && move->Origin_File == FILE_h) {
                    board->BShort = false;
                }

            }
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
//does side_to move have a legal move left to do? helper function has_legal_move will determine this
    bool has_legal_move(const struct chess_board *board, enum chess_player side) {
        //loop over all origin squares
        for (int r = 0; r < 8; r++) {
            for (int f = 0; f < 8; f++) {

                enum chess_piece p = board->Grid[r][f][0];
                enum chess_player owner = board->Grid[r][f][1];

                //skip empty squares or enemy pieces
                if (p == PIECE_NULL || owner != side) {
                    continue;
                }

                //try every possible target square
                for (int tr = 0; tr < 8; tr++) {
                    for (int tf = 0; tf < 8; tf++) {

                        //skip same-square move
                        if (tr == r && tf == f) {
                            continue;
                        }

                        //check correct move logic
                        if (!piece_can_move(board, p, f, r, tf, tr)) {
                            continue;
                        }

                        //make a temporary copy of the board
                        struct chess_board temp = *board;

                        //apply the move on the temp board
                        temp.Grid[tr][tf][0] = p;
                        temp.Grid[tr][tf][1] = side;
                        temp.Grid[r][f][0] = PIECE_NULL;
                        temp.Grid[r][f][1] = PLAYER_NULL;

                        //update king location if needed
                        if (p == PIECE_KING) {
                            if (side == PLAYER_WHITE) {
                                temp.WKingPos[0] = tr;
                                temp.WKingPos[1] = tf;
                            } else {
                                temp.BKingPos[0] = tr;
                                temp.BKingPos[1] = tf;
                            }
                        }

                        //after the move, check if side's king is in check
                        if (!King_in_Check(&temp, side)) {
                            //found at least one legal move
                            return true;
                        }
                    }
                }
            }
        }
    //if no legal move found
    return false;
}


void board_summarize(const struct chess_board *board)
{
//decide side beign evaluated
    enum chess_player side_to_move = board->next_move_player;

//is side_to_move in check right now?
    bool in_check = King_in_Check((struct chess_board *)board, side_to_move);
    //evaluate has_legal_move
    bool has_move = has_legal_move(board, side_to_move);

//decide what to print => final game status

    //game incomplete
    if (has_move) {
        printf("game incomplete\n");
        return;
    }

    //checkmate
    if (!has_move && in_check) {
          if (side_to_move == PLAYER_WHITE) {
               printf("black wins by checkmate\n");
          } else {
              printf("white wins by checkmate\n");
          }
       return;
    }

    //stalemate
    printf("draw by stalemate\n");

}

void board_print(const struct chess_board *board) {
    for (int rank = RANK_8; rank >= RANK_1; --rank) {
        for (int file = FILE_a; file <= FILE_h; ++file) {

            printf("[%s|%s]", piece_string_short(board->Grid[rank][file][0]), player_string_short(board->Grid[rank][file][1]));
        }
        printf("\n");
    }
    printf("\n\n");
}
