#pragma once
#include "raylib.h"
#include "types.h"
extern Texture2D pieceTextures[13];

void LoadPieceTextures();

void UnloadPieceTextures();

void drawPieces(Position &position);