#include "raylib.h"
#include <iostream>
#include <cstdint>
#include <string>
using namespace std;

enum PieceType { EMPTY, WP, BP, WN, BN, WB, BB, WR, BR, WQ, BQ, WK, BK };

Color baishe = {241, 216, 179, 255};
Color brown = {169, 129, 97, 255};

string startingFenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
int tileSize = 96;
int windowWidth = tileSize * 8;
int windowHeight = tileSize * 8;

struct Piece {
    PieceType type;
    Color color;
};

struct Position {
    Piece board[8][8];
    uint64_t bitboards[12];
};

Texture2D pieceTextures[13];

void LoadPieceTextures() {
    pieceTextures[WP] = LoadTexture("res/white-pawn.png");
    pieceTextures[BP] = LoadTexture("res/black-pawn.png");
    pieceTextures[WN] = LoadTexture("res/white-knight-left.png");
    pieceTextures[BN] = LoadTexture("res/black-knight-right.png");         
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
        case 'P': return WP;
        case 'p': return BP;
        case 'N': return WN;
        case 'n': return BN;
        case 'B': return WB;
        case 'b': return BB;
        case 'R': return WR;
        case 'r': return BR;
        case 'Q': return WQ;
        case 'q': return BQ;
        case 'K': return WK;
        case 'k': return BK;
        default:  return EMPTY;
    }
};

void parseFen(Position &position, string fen) {
    // clear the board first 
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            position.board[row][col] = {EMPTY, WHITE};
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
        else if ((c <= '7') && (c >= '1')) {
            // c - '0' == convert to int
            col += (c - '0');
        }
        else {
            position.board[row][col].type = charToPieceType(c);
            col++;
        }
    }
};

void drawPieces(Position &position) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            PieceType pieceType = position.board[row][col].type;
            if (pieceType == EMPTY) continue;

            Texture2D image = pieceTextures[pieceType];

            float scale = (float)tileSize / image.width;
            DrawTextureEx(
                image, // texture 
                {(float)col*tileSize, (float)row*tileSize}, // position
                float(0), // rotation (no rotation)
                scale, // scale
                WHITE // tint (white == no tint)
            );
        }
    }
};

int main() {
    InitWindow(windowWidth, windowHeight, "Chess");
    SetTargetFPS(60);
    LoadPieceTextures();    

    Position position = {};
    parseFen(position, startingFenString);

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
