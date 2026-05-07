#include "mouseActions.h"

extern int tileSize;         
extern int screenWidth;
extern int screenHeight;

bool dragging = false; 
int mouseClickedTile = -1;
int mouseReleasedTile = -1;

int findMouseTile() {
    Vector2 mousePosition = GetMousePosition();

    if (mousePosition.x > screenWidth || mousePosition.x < 0) return -1;
    if (mousePosition.y > screenHeight || mousePosition.y < 0) return -1;

    int col = mousePosition.x / tileSize;
    int row = mousePosition.y / tileSize;
    return ((7 - row) * 8) + col;
    
};

void update(Position &position) {

    if (dragging) {
        dragging = true;
        Vector2 currentMousePos = GetMousePosition();
        drawSelectedPiece(position, mouseClickedTile, currentMousePos.x, currentMousePos.y);
    }
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        mouseClickedTile = findMouseTile();
        dragging = true;
    }
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && dragging) {
        mouseReleasedTile = findMouseTile();
        dragging = false;
    }
};