#include "conway.h"

int
main(void)
{
    InitWindow(width, height, WINDOW_TITLE);

    cell_width = width / grid_size;
    cell_height = height / grid_size;

    DisableCursor();
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            draw_cells();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
