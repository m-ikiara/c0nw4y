#include "conway.h"
#include "raylib.h"
#include "rcamera.h"

typedef struct Animation_t {
    CLITERAL(Color) color;
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

void change_animation_state(Animation *animation, int state);
void fade_color_setting(Animation *animation);

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
    if (on_grid(cell_x, cell_y)) grid[cell_x * grid_size + cell_y] = value;
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
    int cell_x = x * cell_width, cell_y = y * cell_height;

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

void
change_animation_state(Animation *animation, int state)
{
    animation->state = state;
    animation->start = GetTime(); 
}

void
fade_color_setting(Animation *animation)
{
    Color color;
    double seconds_elapsed;

    switch (animation->state) {
        case FADE_IN:
            seconds_elapsed = abs_time - animation->start;
            if (seconds_elapsed >= animation->duration) {
                animation->state = IDLE;
                color = animation->color;
            } else
                color = Fade(animation->color, (seconds_elapsed / animation->duration) * 255.0);
            break;
        case FADE_OUT:
            seconds_elapsed = abs_time - animation->start;
            if (seconds_elapsed >= animation->duration) {
                animation->state = HIDDEN;
                color = animation->color;
            } else
                color = Fade(animation->color, ((animation->duration - seconds_elapsed) / animation->duration) * 255.0);
            break;
        case IDLE:
            color = animation->color;
            break;
        default:
            printf("[ERROR] Invalid Animation State\n");
            break;
    }
}

void
change_grid_size(int size)
{
    grid_size = size;
    DrawGrid(grid_size, .5);
}

void
game_mode_handler()
{
    if (IsKeyPressed(KEY_SPACE)) {
        paused = !paused;
        switch (pause_animation.state) {
            case FADE_IN:
                pause_animation.state = FADE_OUT;
                break;
            case FADE_OUT:
                pause_animation.state = FADE_IN;
                break;
            case IDLE:
                change_animation_state(&pause_animation, FADE_OUT);
                break;
            case HIDDEN:
                change_animation_state(&pause_animation, FADE_IN);
                break;
        }
    } else if (IsKeyPressed(KEY_R)) {
        DrawGrid(grid_size, .5);
        reset_t = GetTime();
    } else if (IsKeyPressed(KEY_MINUS)) {
        int new_size = grid_size - GRID_SIZE_CHANGE_STEP;
        if (new_size <= 0) return;
        change_grid_size(new_size);
    } else if (IsKeyPressed(KEY_EQUAL)) {
        change_grid_size(grid_size + GRID_SIZE_CHANGE_STEP);
    }
}

int
main(void)
{
    InitWindow(width, height, WINDOW_TITLE);

    cell_width = width / grid_size;
    cell_height = height / grid_size;

    Camera camera = {
        .position = (Vector3){0.0f, 2.0f, 4.0f},
        .target = (Vector3){0.0f, 2.0f, 0.0f},
        .up = (Vector3){0.0f, 1.0f, 0.0f},
        .fovy = 60.0f,
        .projection = CAMERA_PERSPECTIVE
    };

    DisableCursor();
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, camera_mode);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D();
                draw_cells();
            EndMode3D();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
