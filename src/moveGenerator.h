#pragma once
#include "types.h"

void generateLegalMoves(bool isWhiteTurn, Position &position, MoveList &out);

void generatePawnLegalMoves(uint64_t enemies, bool isWhiteTurn, Position &position, MoveList &out);

void generateKingLegalMoves(uint64_t enemies, bool isWhiteTurn, Position &position, MoveList &out);