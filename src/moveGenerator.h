#pragma once
#include "types.h"

void generateLegalMoves(bool isWhiteTurn, Position &position, MoveList &out);

void generatePawnLegalMoves(bool isWhiteTurn, Position &position, MoveList &out);

void generateKingLegalMoves(bool isWhiteTurn, Position &position, MoveList &out);