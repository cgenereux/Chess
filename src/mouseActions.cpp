#include "mouseActions.h"

extern int tileSize;         
extern int screenWidth;
extern int screenHeight;
extern int isWhiteTurn;

bool dragging = false; 
int mouseClickedTile = -1;
int mouseReleasedTile = -1;

uint64_t selectedLegalMoves;

int findMouseTile() {
    Vector2 mousePosition = GetMousePosition();

    if (mousePosition.x > screenWidth || mousePosition.x < 0) return -1;
    if (mousePosition.y > screenHeight || mousePosition.y < 0) return -1;

    int col = mousePosition.x / tileSize;
    int row = mousePosition.y / tileSize;
    return ((7 - row) * 8) + col;

};

void update(Position &position) {

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        mouseClickedTile = findMouseTile();
        dragging = true;

        PieceType pieceType = position.board[mouseClickedTile].type;
        uint64_t enemies = isWhiteTurn ? (position.blackPieces) : (position.whitePieces);
        MoveList legalMoveList;
        switch (pieceType) {
            case WP: {
                generatePawnLegalMoves(enemies, isWhiteTurn, position, legalMoveList);
                break;
            } case WN: {
                generateKnightLegalMoves(enemies, isWhiteTurn, position, legalMoveList);
                break;
            }
            default:
                break;
        }
        for (int i = 0; i < legalMoveList.size(); i++) {
            if (legalMoveList.moves[i].from == mouseClickedTile) {
                selectedLegalMoves |= (1ULL << legalMoveList.moves[i].to);
            }
        }
    }
    if (dragging) {
        dragging = true;
        Vector2 currentMousePos = GetMousePosition();
        drawSelectedPiece(position, mouseClickedTile, currentMousePos.x, currentMousePos.y);
    }
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && dragging) {
        selectedLegalMoves = 0ULL;
        mouseReleasedTile = findMouseTile();
        dragging = false;
    }
};