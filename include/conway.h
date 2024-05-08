#ifndef _CONWAY_H_
#define _CONWAY_H_

#pragma once

#include <cstdint>
#include <cstring>
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_TITLE "Conway's Game of Life"
#define DEFAULT_GRID_SIZE     32
#define GRID_SIZE_CHANGE_STEP 8
#define ALIVE                 1
#define DEAD                  0
#define DYING                 2

#define FADE_IN               0
#define FADE_OUT              1
#define IDLE                  2
#define HIDDEN                3

#define GRID_SIZE(gs) (sizeof(int) * gs * gs)


int grid_size = DEFAULT_GRID_SIZE,
    cell_width, cell_height,
    paused = false, reset_t = 0;
short width = 800, height = 600;
double abs_time;
volatile int suspend;

typedef struct {
    Color color;
    int      state;
    double   start;
    double   duration;
} Animation;

Animation pause_animation = {
    .color    = BLACK,
    .state    = HIDDEN,
    .start    = 0.0,
    .duration = 0.5,
};

void cell_index(int x, int y, int *cell_x, int *cell_y);
int on_grid(int cell_x, int cell_y);
void toggle_cell(int x, int y, int val);
int count_neighbours(int x, int y);
void conway_rules(int x, int y, int neighbours);
void apply_rules(int x, int y);

void draw_cell(int x, int y);
void draw_cells();

void change_animation_state(Animation *animation, int state);
void fade_color_setting(Animation *animation);
void change_grid_size(int size);
void game_mode_handler();

#endif // !_CONWAY_H_