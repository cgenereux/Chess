#pragma once
#define SET_BIT(bb, sq) ((bb) |= (1ULL << (sq)))
#define CLEAR_BIT(bb, sq) ((bb) &= ~(1ULL << (sq)))
#define GET_BIT(bb, sq) (((bb) >> (sq)) & 1ULL)
#include <cstdint>

enum PieceType { EMPTY, WP, BP, WN, BN, WB, BB, WR, BR, WQ, BQ, WK, BK };

struct Piece {
    PieceType type;
};

struct Position {
    Piece board[64];
    uint64_t bitboards[13];
    uint64_t whitePieces;
    uint64_t blackPieces;
    uint64_t empty;
};

struct Move {
    uint8_t from;
    uint8_t to;
    uint8_t flags;
    uint8_t promotion;
};

struct MoveList {
    Move moves[256];
    int i = 0;
    void addMove(Move m) {
        moves[i++] = m;
    }
    int size() {
        return i;
    }
};