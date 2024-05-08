#include "conway.h"

void
cell_index(int x, int y, int *cell_x, int *cell_y)
{
    *cell_x = x / (width * grid_size);
    *cell_y = y / (height * grid_size);
}

int
on_grid(int cell_x, int cell_y)
{
    return (0 <= cell_x && cell_x <= grid_size - 1) && (0 <= cell_y && cell_y <= grid_size - 1);
}

void
toggle_cell(int x, int y, int value)
{
    int cell_x, cell_y;
    cell_index(x, y, &cell_x, &cell_y);
    if (on_grid(cell_x, cell_y))
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
    int cell_x = x * cell_width,
    int cell_y = y * cell_height

    DrawRectangleLines(cell_x, cell_y, cell_width, cell_height, SKYBLUE);
}

void
draw_cells()
{
    for (int y = 0; y < grid_size; ++y) {
        for (int x = 0; x < grid_size; ++x) {
            if (!paused) apply_rules(x, y);
            else if (grid[x * grid_size + y] == ALIVE) draw_cell(x, y);
        }
    }
}
