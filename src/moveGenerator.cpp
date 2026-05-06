#include "moveGenerator.h"
#include <cstdint>

constexpr uint64_t colA = 0x0101010101010101ULL;
constexpr uint64_t colH = 0x8080808080808080ULL;
constexpr uint64_t row4 = 0x00000000FF000000ULL;
constexpr uint64_t row5 = 0x000000FF00000000ULL;

void generateLegalMoves(bool isWhiteTurn, Position &position, MoveList &out) {

    position.empty = ~(position.whitePieces | position.blackPieces);
    uint64_t enemies = isWhiteTurn ? (position.blackPieces) : (position.whitePieces);

    generatePawnLegalMoves(enemies, isWhiteTurn, position, out);
    generateKingLegalMoves(enemies, isWhiteTurn, position, out);
};

void generateKingLegalMoves(uint64_t enemies, bool isWhiteTurn, Position &position, MoveList &out) {

    uint64_t friendlyKing = isWhiteTurn ? position.bitboards[WK] : position.bitboards[BK];

    int moveDirections[8] = {7,8,9,1,-7,-8,-9,-1};
    Move move;

    // in cpp any non 0 value is true
    bool onColA = friendlyKing & colA;
    bool onColH = friendlyKing & colH;

    for (int i = 0; i < 8; i++) {

        if ((moveDirections[i] == 7 || moveDirections[i] == -1 || moveDirections[i] == -9) && onColA) continue;
        if ((moveDirections[i] == 9 || moveDirections[i] == 1 || moveDirections[i] == -7) && onColH) continue;

        uint64_t moveDirection;
        if (moveDirections[i] >= 0) {
            moveDirection = (friendlyKing << moveDirections[i]) & (position.empty | enemies);
        } else {
            moveDirection = (friendlyKing >> moveDirections[i]*-1) & (position.empty | enemies);
        }
        if (!moveDirection) continue;
        move.to = __builtin_ctzll(moveDirection);
        move.from = move.to-moveDirections[i];
        out.addMove(move);
    }
};

void generatePawnLegalMoves(uint64_t enemies, bool isWhiteTurn, Position &position, MoveList &out) {

    uint64_t advanceOne = isWhiteTurn ? ((position.bitboards[WP] << 8) & position.empty) : ((position.bitboards[BP] >> 8) & position.empty);
    uint64_t advanceTwo = isWhiteTurn ? ((advanceOne << 8) & position.empty & row4) : ((advanceOne >> 8) & position.empty & row5);

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

    uint64_t pawns = isWhiteTurn ? position.bitboards[WP] : position.bitboards[BP];

    uint64_t leftCaptures, rightCaptures;

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