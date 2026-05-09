#pragma once
#include "raylib.h"
#include "types.h"
extern Texture2D pieceTextures[13];

void LoadPieceTextures();

void UnloadPieceTextures();

void drawPieces(Position &position, int tileSize);

void drawBoard(int tileSize);

void drawSelectedPiece(Position &position, int tile, float mouseX, float mouseY);

void drawLegalTiles(uint64_t selectedLegalMoves);