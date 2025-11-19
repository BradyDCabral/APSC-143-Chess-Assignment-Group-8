#include "parser.h"
#include <stdio.h>
#include "panic.h"

bool parse_move(struct chess_move *move)
{
    char c;

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

    // Checks to ensure that start of command is valid
    if (c >= 'A' && c <= 'z') {

        // determines the moving piece
        switch (c) {

            // King is moving
            case 'K':
                // Blah Blah Blah
                break;

            // Queen case
            case 'Q':
                // blah blah
                break;

            // Rook case
            case 'R':
                // blad blah
                break;

            // Bishop case
            case 'B':
                // blah blah
                break;

            // Knight case
            case 'N':
                // blah blah
                break;

            // Castle case
            case 'O':
                // blah blah
                break;

            // Pawn Case
            default:
                move->piece_type = PIECE_PAWN;

        }
    }else {
        panicf("parse error at character 'c'\n", c);
    }


}
