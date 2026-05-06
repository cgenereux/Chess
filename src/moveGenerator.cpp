#include "moveGenerator.h"
#include <cstdint>

void generateLegalMoves(bool isWhiteTurn, Position &position, MoveList &out) {

};

void generatePawnLegalMoves(bool isWhiteTurn, Position &position, MoveList &out) {

    // EMPTY is already defined to [0] in my PieceType enum so i can't AND it 
    uint64_t emptySquares = ~(position.whitePieces | position.blackPieces); 

    uint64_t row4 = 0x00000000FF000000ULL;
    uint64_t row5 = 0x000000FF00000000ULL;

    uint64_t advanceOne = isWhiteTurn ? ((position.bitboards[WP] << 8) & emptySquares) : ((position.bitboards[BP] >> 8) & emptySquares);
    uint64_t advanceTwo = isWhiteTurn ? ((advanceOne << 8) & emptySquares & row4) : ((advanceOne >> 8) & emptySquares & row5);

    int direction = isWhiteTurn ?  -8 : +8;

    while (advanceOne) {
        uint8_t toSquare = __builtin_ctzll(advanceOne);
        uint8_t fromSquare = toSquare+direction;

        Move move;
        move.from = fromSquare;
        move.to = toSquare;

        out.addMove(move);
        advanceOne &= advanceOne-1;
    }

    while (advanceTwo) {
        uint8_t toSquare = __builtin_ctzll(advanceTwo);
        uint8_t fromSquare = toSquare+(2*direction);

        Move move;
        move.from = fromSquare;
        move.to = toSquare;

        out.addMove(move);
        advanceTwo &= advanceTwo-1;
    }

    uint64_t enemies = isWhiteTurn ? (position.blackPieces) : (position.whitePieces);
    uint64_t pawns = isWhiteTurn ? position.bitboards[WP] : position.bitboards[BP];

    uint64_t colA = 0x0101010101010101ULL;
    uint64_t colH = 0x8080808080808080ULL;

    uint64_t leftCaptures;
    uint64_t rightCaptures;

    leftCaptures = isWhiteTurn ? ((pawns << 7) & enemies & ~colH) : ((pawns >> 9) & enemies & ~colH);
    int moveLength = isWhiteTurn ? -7 : 9;

    while (leftCaptures) {
        uint8_t toSquare = __builtin_ctzll(leftCaptures);
        uint8_t fromSquare = toSquare+moveLength;

        Move move;
        move.from = fromSquare;
        move.to = toSquare;

        out.addMove(move);
        leftCaptures &= leftCaptures-1;
    }

    rightCaptures = isWhiteTurn ? ((pawns << 9) & enemies & ~colA) : ((pawns >> 7) & enemies & ~colA);
    moveLength = isWhiteTurn ? -9 : 7;
    
    while (rightCaptures) {
        uint8_t toSquare = __builtin_ctzll(rightCaptures);
        uint8_t fromSquare = toSquare+moveLength;

        Move move;
        move.from = fromSquare;
        move.to = toSquare;

        out.addMove(move);
        rightCaptures &= rightCaptures-1;
    }
};