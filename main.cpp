#include "raylib.h"
#include <iostream>
#include <cstdint>
#include <string>
using namespace std;

enum PieceType { EMPTY, WP, BP, WN, BN, WB, BB, WR, BR, WQ, BQ, WK, BK };

Color baishe = {241, 216, 179, 255};
Color brown = {169, 129, 97, 255};

string startingFenString = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
int tileSize = 128;
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

Texture2D pieceTextures[12];

void LoadPieceTextures() {
    pieceTextures[WP] = LoadTexture("assets/white-pawn.png");
    pieceTextures[BP] = LoadTexture("assets/black-pawn.png");
    pieceTextures[WN] = LoadTexture("assets/white-knight.png");
    pieceTextures[BN] = LoadTexture("assets/black-knight.png");         
    pieceTextures[WB] = LoadTexture("assets/white-bishop.png");
    pieceTextures[BB] = LoadTexture("assets/black-bishop.png");
    pieceTextures[WR] = LoadTexture("assets/white-rook.png");
    pieceTextures[BR] = LoadTexture("assets/black-rook.png");
    pieceTextures[WQ] = LoadTexture("assets/white-queen.png");
    pieceTextures[BQ] = LoadTexture("assets/black-queen.png");
    pieceTextures[WK] = LoadTexture("assets/white-king.png");
    pieceTextures[BK] = LoadTexture("assets/black-king.png");
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

void parseFen(Position position, string fen) {
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
        else if ((c <= '7') && (c >= 0)) {
            // c - '0' == convert to int
            col += (c - '0');
        }
        else {
            position.board[row][col].type = charToPieceType(c);
            col++;
        }
    }
};

int main() {
    InitWindow(windowWidth, windowHeight, "Chess");
    SetTargetFPS(60);

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
        EndDrawing();
    }
    CloseWindow();
    return 0;
};
