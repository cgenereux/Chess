#define SET_BIT(bb, sq) ((bb) |= (1ULL << (sq)))
#define CLEAR_BIT(bb, sq) ((bb) &= ~(1ULL << (sq)))
#define GET_BIT(bb, sq) (((bb) >> (sq)) & 1ULL)
#include "raylib.h"
#include "types.h"
#include <iostream>
#include <cstdint>
#include <string>
using namespace std;

Color baishe = {241, 216, 179, 255};
Color brown = {169, 129, 97, 255};

int tileSize = 96;
int windowWidth = tileSize * 8;
int windowHeight = tileSize * 8;

Texture2D pieceTextures[13];

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

PieceType charToPieceType(char c) {
    switch (c) {
        case 'P': return WP; case 'p': return BP;
        case 'N': return WN; case 'n': return BN;
        case 'B': return WB; case 'b': return BB;
        case 'R': return WR; case 'r': return BR;
        case 'Q': return WQ; case 'q': return BQ;
        case 'K': return WK; case 'k': return BK;
        default:  return EMPTY;
    }
};

void parseFen(Position &position, string fen) {
    // clear the board first 
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            position.board[(7 - row) * 8 + col] = {EMPTY};
        }
    }
    int row = 0, col = 0;
    for (char c: fen) {
        if (c == ' ') break;
        if (c == '/') {
            row++;
            col = 0;
        } 
        // you can do equality operations on a char int 
        else if (isdigit(c)) {
            // c - '0' == convert to int
            col += (c - '0');
        }
        else {
            PieceType pieceType = charToPieceType(c);
            position.board[(7 - row) * 8 + col].type = pieceType;

            // the 64 bit position 
            int piecePosition = (7 - row) * 8 + col;

            // 1ULL << n : nth bit in a 64 bit bitmask set to 1.
            // [pieceType - 1] because index 'EMPTY' is 0.
            position.bitboards[pieceType - 1] |= (1ULL << piecePosition);

            col++;
        }
    }
};

void move(Position &position, Move move) {
    Piece piece = position.board[move.from];
    position.board[move.from].type = EMPTY;
    position.board[move.to] = piece;
    
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

int main() {
    InitWindow(windowWidth, windowHeight, "Chess");
    SetTargetFPS(60);
    LoadPieceTextures();    

    Position position = {};
    parseFen(position, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"); // starting fen string

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                bool isWhiteTile = ((row + col) % 2 == 0);
                
                Color tileColor = isWhiteTile ? baishe : brown;

                DrawRectangle(
                    tileSize * col,
                    tileSize * row,
                    tileSize,
                    tileSize,
                    tileColor
                );
            }
        }
        drawPieces(position); 
        EndDrawing();
    }
    UnloadPieceTextures();  
    CloseWindow();
    return 0;
};
