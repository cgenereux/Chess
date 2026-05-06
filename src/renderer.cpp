#include "types.h"
#include "renderer.h"
using namespace std;

Texture2D pieceTextures[13];

int tileSize = 96;
int windowWidth = tileSize * 8;
int windowHeight = tileSize * 8;

void LoadPieceTextures() {
    pieceTextures[WP] = LoadTexture("res/white-pawn.png");
    pieceTextures[BP] = LoadTexture("res/black-pawn.png");
    pieceTextures[WN] = LoadTexture("res/white-knight-left.png");
    pieceTextures[BN] = LoadTexture("res/black-knight-left.png");         
    pieceTextures[WB] = LoadTexture("res/white-bishop.png");
    pieceTextures[BB] = LoadTexture("res/black-bishop.png");
    pieceTextures[WR] = LoadTexture("res/white-rook.png");
    pieceTextures[BR] = LoadTexture("res/black-rook.png");
    pieceTextures[WQ] = LoadTexture("res/white-queen.png");
    pieceTextures[BQ] = LoadTexture("res/black-queen.png");
    pieceTextures[WK] = LoadTexture("res/white-king.png");
    pieceTextures[BK] = LoadTexture("res/black-king.png");
};

void UnloadPieceTextures() {
    for (int i = 1; i < 13; i++) UnloadTexture(pieceTextures[i]);
};

void drawPieces(Position &position) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            PieceType pieceType = position.board[(7 - row) * 8 + col].type;
            if (pieceType == EMPTY) continue;

            Texture2D image = pieceTextures[pieceType];

            float scale = (float)tileSize / image.width;

            // default facing left
            float flipMultiplier = -1.0f;
            if (pieceType == WN || pieceType == BN) {
                if (col >= 4) {
                    // flip it to facing right
                    flipMultiplier = 1.0f;
                }
            }

            Rectangle sourceRectangle = { 
                0.0f, 
                0.0f, 
                (float)image.width * flipMultiplier, 
                (float)image.height 
            };

            Rectangle destRectangle = { 
                (float)col * tileSize, 
                (float)row * tileSize, 
                (float)tileSize, 
                (float)tileSize 
            };

            Vector2 origin = { 0.0f, 0.0f };

            DrawTexturePro(
                image, 
                sourceRectangle, 
                destRectangle, 
                origin, 
                0.0f,  // rotation (no rotation)
                WHITE  // tint (white == no tint)
            );
        }
    }
};
