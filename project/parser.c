#include "parser.h"
#include <stdio.h>
#include "panic.h"

bool parse_move(struct chess_move *move)
{
    char c;


    // Temp variable
    bool Test = false;

    // VARIABLES FOR CONTEXT
    bool promotion = false;

    // Get the first character of the move, ignoring any initial spaces.
    do
    {
        c = getc(stdin);
    } while (c == ' ');

    // Check if we are at the end of input.
    if (c == '\n' || c == '\r')
        return false;

    // before reusing the struct you must ensure that it is clear of information from the previous move
    Move_Initialize(move);

    // If error do similar to this output

    // if end of command return true

    // Main chunk of code to deal with

    if (Test) {
        printf("---Move Reset---\n");
        Display_Move(move);
    }


    // First character (determines the piece

    // Checks to ensure that start of command is valid
    if (c >= 'A' && c <= 'z') {

        // determines the moving piece
        switch (c) {

            // King is moving
            case 'K':
                // Blah Blah Blah
                move->piece_type = PIECE_KING;
                break;

            // Queen case
            case 'Q':
                // blah blah
                move->piece_type = PIECE_QUEEN;
                break;

            // Rook case
            case 'R':
                // blad blah
                move->piece_type = PIECE_ROOK;
                break;

            // Bishop case
            case 'B':
                // blah blah
                move->piece_type = PIECE_BISHOP;
                break;

            // Knight case
            case 'N':
                // blah blah
                move->piece_type = PIECE_KNIGHT;
                break;

            // Castle case
            case 'O':
                // blah blah
                move->piece_type = PIECE_KING;
                move->Castle = true;
                move->Origin_File = FILE_e;
                break;

            // Pawn Case
            default:
                move->piece_type = PIECE_PAWN;
                ungetc(c, stdin);


        }
        if (Test) {
            printf("---Piece Determined---\n");
            Display_Move(move);
        }
    }else {
        panicf("parse error at character '%c'\n", c);
    }

    // Special Case if Castling is being detected

    // determines if castle notation is correct and returns info supplied to move struct
    if (move->Castle) {
        // Test if Castle is long or short
        int num_of_Os = -1;
        bool loop_Castle = true;

        while (loop_Castle) {
            num_of_Os++;
            c = getc(stdin);

            if (c == '\n' || c == '\r') {
                loop_Castle = false;
                break;
            }
            if (c != '-') {
                loop_Castle = false;
            }

            c = getc(stdin);
            if (c == '\n' || c == '\r') {
                loop_Castle = false;
                break;
            }
            if (c != 'O') {
                loop_Castle = false;
            }

        }

        if (num_of_Os == 1) {
            move->Target_File = FILE_g;
        } else if (num_of_Os == 2) {
            move->Target_File = FILE_c;
        }



        if (Test) {
            printf("---Castle Target Determined---\n");
            Display_Move(move);
        }
        return true;
    }



    // Second Character : determines location (Unclear yet if it is starting or target)
    c = getc(stdin);



    int Limbo_File = FILE_NULL;
    int Limbo_Rank = RANK_NULL;


    // Checks if valid input
    if ((c >= 'a' && c <= 'h') || (c >= '1' && c <= '8')) {
        if (c <= '8') {
            Limbo_Rank = c - '1';
        } else {
            Limbo_File = c - 'a';
        }
    } else if (c == 'x') {
        move->Capture = true;
    } else {
        panicf("parse error at character '%c'\n", c);
    }

    if (Test) {
        printf("---Second Stage---\n");
        Display_Move(move);
    }

    // After Second stage must check if there is a _ or a \n or \r


    // THIRD STAGE
    c = getc(stdin);

    // makes sure we don't read next turn
    // MIGHT BE WRONG
    /*
    if (c == '\n' || c == '\r' || c == ' ') {
        return true;
    }
    */


    if (c >= '1' && c <= '8' && Limbo_File != FILE_NULL) {
        move->Target_File = Limbo_File;
        move->Target_Rank = c - '1';
        // printf("damn %d\n", move->Target_Rank + 1);
    } else if (c >= 'a' && c <= 'h') {
        move->Target_File = c - 'a';
        move->Origin_File = Limbo_File;
        move->Origin_Rank = Limbo_Rank;
    } else if (c == 'x') {
        move->Origin_File = Limbo_File;
        move->Origin_Rank = Limbo_Rank;
        move->Capture = true;
    } else {
        panicf("parse error at character '%c'\n", c);
    }

    if (Test) {
        printf("---THIRD STAGE---\n");
        Display_Move(move);
    }


    // FOURTH STAGE
    c = getc(stdin);



    // prevents next commands from being read
    if (c == '\n' || c == '\r' || c == ' ') {
        ungetc(c, stdin);
        return true;
    }

    if (c >= 'a' && c <= 'h') {
        move->Target_File = c - 'a';
    } else if (c >= '1' && c <= '8'  /* && !move->Capture */ && move->Target_Rank==RANK_NULL) {
        move->Target_Rank = c - '1';
        // might be more here
    } else if (c == '=') {
        // the variable change might be redundent
        /*
        move->Origin_File = Limbo_File;
        move->Origin_Rank = Limbo_Rank;
        */
        promotion = true;
    } /*else if (c == 'x') {
        move->Origin_File = Limbo_File;
        move->Origin_Rank = Limbo_Rank;
        move->Capture = true;
    } */else {
        panicf("parse error at character '%c'\n", c);
    }

    if (Test) {
        printf("---FOURTH STAGE---\n");
        Display_Move(move);
    }





    // FIFTH STAGE
    c = getc(stdin);



    // prevents next commands from being read
    if (c == '\n' || c == '\r' || c == ' ') {
        ungetc(c, stdin);
        return true;
    }

    /*if (c >= 'a' && c <= 'h') {
        move->Target_File = c - 'a';
    } else */ if (c >= '1' && c <= '8' && move->Target_Rank==RANK_NULL) {
        move->Target_Rank = c - '1';
        // might be more here
    } /* else if (c == '=') {
        move->Origin_File = Limbo_File;
        move->Origin_Rank = Limbo_Rank;
        promotion = true;
    } */else if (c >= 'A' && c <= 'Z' && promotion) {
        switch (c) {
            case 'Q':
                move->Promotion_Piece = PIECE_QUEEN;
                break;
            case 'R':
                move->Promotion_Piece = PIECE_ROOK;
                break;
            case 'B':
                move->Promotion_Piece = PIECE_BISHOP;
                break;
            case 'N':
                move->Promotion_Piece = PIECE_KNIGHT;
                break;
            default:
                panicf("parse error at character '%c'\n", c);

        }
    } else {
        panicf("parse error at character '%c'\n", c);
    }

    if (Test) {
        printf("---FIFTH STAGE---\n");
        Display_Move(move);
    }

    // SIXTH STAGE
    c = getc(stdin);

    if (c == '\n' || c == '\r' || c == ' ') {
        ungetc(c, stdin);
        return true;
    }

    if (c == '=') {
        promotion = true;
    } else {
        panicf("parse error at character '%c'\n", c);
    }

    if (Test) {
        printf("---SIXTH STAGE---\n");
        Display_Move(move);
    }

    // SEVENTH STAGE
    c = getc(stdin);

    if (c == '\n' || c == '\r' || c == ' ') {
        ungetc(c, stdin);
        return true;
    }

    if (c >= 'A' && c <= 'Z' && promotion) {
        switch (c) {
            case 'Q':
                move->Promotion_Piece = PIECE_QUEEN;
                break;
            case 'R':
                move->Promotion_Piece = PIECE_ROOK;
                break;
            case 'B':
                move->Promotion_Piece = PIECE_BISHOP;
                break;
            case 'N':
                move->Promotion_Piece = PIECE_KNIGHT;
                break;
            default:
                panicf("parse error at character '%c'\n", c);

        }
    } else {
        panicf("parse error at character '%c'\n", c);
    }

    if (Test) {
        printf("---SEVENTH STAGE---\n");
        Display_Move(move);
    }

    
    if (Test) {
        printf("--------END OF PARSING--------\n");
    }
    return true;
}
