#include "raylib.h"
#include "types.h"
#include "moveGenerator.h"
#include "renderer.h"
#include "mouseActions.h"
#include <iostream>
#include <cstdint>
#include <string>
using namespace std;

int tileSize = 96;
int screenWidth = tileSize * 8;
int screenHeight = tileSize * 8;

bool isWhiteTurn = true;

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

int main() {
    InitWindow(screenWidth, screenHeight, "Chess");
    SetTargetFPS(140);
    LoadPieceTextures();    

    Position position;
    parseFen(position, "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"); // starting fen string

    while (!WindowShouldClose()) {

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        drawBoard(tileSize);
        drawPieces(position, tileSize); 
        update(position);

        EndDrawing();
    }
    UnloadPieceTextures();  
    CloseWindow();
    return 0;
};
