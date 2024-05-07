#ifndef _CONWAY_H_
#define _CONWAY_H_

#include <cstring>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_TITLE "Conway's Game of Life"
#define DEFAULT_GRID_SIZE 32
#define ALIVE             1
#define DEAD              0
#define DYING             2

#define GRID_SIZE(gs) (sizeof(int) * gs * gs)

typedef struct {
    int cell_x;
    int cell_y;
} Cell_Position;

int *grid = NULL, *next_grid = NULL, grid_size = DEFAULT_GRID_SIZE,
    cell_width, cell_height,
    paused = false;
short width = 800, height = 600;
double abs_time;
volatile int suspend;

bool on_grid(int cell_x, int cell_y);
Cell_Position *cell_index(int x, int y);
void toggle_cell(int x, int y, int val);
void draw_cell(int x, int y);
void draw_cells();

int count_neighbours(int x, int y);
void conway_rules(int x, int y, int neighbours);
void apply_rules(int x, int y);

#endif // !_CONWAY_H_
