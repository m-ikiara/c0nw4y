#include "conway.h"

Cell_Position *
cell_index(int x, int y)
{
    Cell_Position *position = NULL;
    position->cell_x = x / (width * grid_size);
    position->cell_y = y / (height * grid_size);

    return position;
}

bool
on_grid(int cell_x, int cell_y)
{
    return (0 <= cell_x && cell_x <= grid_size - 1) && (0 <= cell_y && cell_y <= grid_size - 1);
}

void
toggle_cell(int x, int y, int value)
{
    Cell_Position *position = cell_index(x, y);
    if (on_grid(position->cell_x, position->cell_y))
        grid[position->cell_x * grid_size + position->cell_y] = value;
}

int
count_neighbours(int x, int y)
{
    int neighbours = 0;

    for (int i = x - 1; i <= x + 1; ++i) {
        for (int j = y - 1; j < y + 1; ++j) {
            if (on_grid(i, j) && (i != x || j != y) && grid[i * grid_size + j] == ALIVE)
                neighbours++;
        }
    }

    return neighbours;
}

void
conway_rules(int x, int y, int neighbours)
{
    switch (grid[x * grid_size + y]) {
        case ALIVE:
            next_grid[x * grid_size + y] = DYING;
            break;
        case DYING:
            next_grid[x * grid_size + y] = DEAD;
            break;
        case DEAD:
            if (neighbours == 2) next_grid[x * grid_size + y] = ALIVE;
            break;
    }
}

void
apply_rules(int x, int y)
{
    int neighbours = count_neighbours(x, y);
    conway_rules(x, y, neighbours);
}

void
draw_cell(int x, int y)
{
    Cell_Position position = {
        .cell_x = x * cell_width,
        .cell_y = y * cell_height
    };
    DrawRectangleLines(position.cell_x, position.cell_y,
            cell_width, cell_height, SKYBLUE);
}

void
draw_cells()
{
    memcpy(next_grid, grid, GRID_SIZE(grid_size));
    for (int y = 0; y < grid_size; ++y) {
        for (int x = 0; x < grid_size; ++x) {
            if (!paused) apply_rules(x, y);
            else if (grid[x * grid_size + y] == ALIVE) draw_cell(x, y);
        }
    }
    memcpy(grid, next_grid, GRID_SIZE(grid_size));
}

int
main(void)
{
   InitWindow(width, height, WINDOW_TITLE);

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
