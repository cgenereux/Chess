#include "raylib.h"
#include <iostream>
using namespace std;

enum class PieceType {
    Empty, Pawn, Knight, Bishop, Rook, Queen, King
};

struct Piece {
    PieceType type;
    Color color;

};

struct Position {
    Piece board[8][8];
    
};

int main() {

    int tileSize = 128;

    Color baishe = {241, 216, 179, 255};
	Color brown = {169, 129, 97, 255};

    InitWindow(tileSize*8, tileSize*8, "Chess");
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
