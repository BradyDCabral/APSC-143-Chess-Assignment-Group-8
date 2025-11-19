#include "parser.h"
#include <stdio.h>
#include "panic.h"

bool parse_move(struct chess_move *move)
{
    char c;


    // Temp variable
    bool Test = true;

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
//        panicf("parse error at character '%c'\n", c);

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
                break;

            // Pawn Case
            default:
                move->piece_type = PIECE_PAWN;
                ungetc(c, stdin);


        }
        if (Test) {
            printf("---Piece Determined---");
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
            c = getc(stdin);
            if (c != '-') {
                loop_Castle = false;
            }
            c = getc(stdin);
            if (c != '0') {
                loop_Castle = false;
            }
            num_of_Os++;
        }


        // Test case for now just ends the function
        return false;
    }



    // Second Character : determines part of starting location
    c = (char)getc(stdin);

    // at the moment doesn't anticipate for castling
    // Checks if valid input
    if ((c >= 'a' && c <= 'h') || (c >= '1' && c <= '8')) {
    } else {
        panicf("parse error at character '%c'\n", c);
    }
    return false;
}
