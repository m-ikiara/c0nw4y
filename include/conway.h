#ifndef _CONWAY_H_
#define _CONWAY_H_

#include <stdio.h>
#include <stdlib.h>

#include "raylib.h"
#include "rcamera.h"

#define WINDOW_TITLE  "Conway's Game of Life"
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

#define WIDTH         10
#define HEIGHT        10
#define DEPTH         10

#define DEAD          0
#define ALIVE         1

Camera camera = {
    .position = (Vector3){0.0f, 2.0f, 128.0f},
    .target = (Vector3){0.0f, 2.0f, 0.0f},
    .up = (Vector3){0.0f, 1.0f, 0.0f},
    .fovy = 60.0f,
    .projection = CAMERA_PERSPECTIVE
};
int grid[WIDTH][HEIGHT][DEPTH], new_grid[WIDTH][HEIGHT][DEPTH],
    camera_mode = CAMERA_THIRD_PERSON;

bool condition(int nx, int ny, int nz);

void init_grid();
void print_grid();
void update_grid();

int count_neighbours(int x, int y, int z);
void conway();

#endif // !_CONWAY_H_
