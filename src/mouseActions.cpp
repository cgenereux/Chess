#include "mouseActions.h"

extern int tileSize;         
extern int screenWidth;
extern int screenHeight;
extern int isWhiteTurn;

bool dragging = false; 
int mouseClickedTile = -1;
int mouseReleasedTile = -1;

uint64_t selectedLegalMoves;

void move(Position &position, Move m); 

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
            } case WK: {
                generateKingLegalMoves(enemies, isWhiteTurn, position, legalMoveList);
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
        Vector2 currentMousePos = GetMousePosition();
        drawSelectedPiece(position, mouseClickedTile, currentMousePos.x, currentMousePos.y);
    }
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && dragging) {
        mouseReleasedTile = findMouseTile();
        dragging = false;
        Move m;
        m.from = mouseClickedTile;
        m.to = mouseReleasedTile;
        move(position, m);
        selectedLegalMoves = 0ULL;
    }
};