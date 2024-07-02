#include "conway.h"

bool
condition(int nx, int ny, int nz)
{
    return (nx >= 0 && nx < WIDTH && ny >= 0 && ny < HEIGHT && nz >= 0 && nz < DEPTH);
}

void
init_grid()
{
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            for (int z = 0; z < DEPTH; ++z) {
                grid[x][y][z] = rand() % 2;
            }
        }
    }
}

void
print_grid()
{
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            for (int z = 0; z < DEPTH; ++z) {
                printf("%d ", grid[x][y][z]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

void
update_grid()
{
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            for (int z = 0; z < DEPTH; ++z) {
                int neighbours = count_neighbours(x, y, z);

                if (grid[x][y][z] == ALIVE) {
                    if (neighbours < 2 || neighbours > 3) new_grid[x][y][z] = DEAD;
                    else new_grid[x][y][z] = ALIVE;
                } else {
                    if (neighbours == 3) new_grid[x][y][z] = ALIVE;
                    else new_grid[x][y][z] = DEAD;
                }
            }
        }
    }

    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            for (int z = 0; z < DEPTH; ++z) {
                grid[x][y][z] = new_grid[x][y][z];
            }
        }
    }
}

int
count_neighbours(int x, int y, int z)
{
    int count = 0;

    for (int i = 0; i <= 1; ++i) {
        for (int j = 0; j <= 1; ++j) {
            for (int k = 0; k <= 1; ++k) {
                if (i == 0 && j == 0 && k == 0) continue;

                int nx = x + i;
                int ny = y + j;
                int nz = z + k;

                if (condition(nx, ny, nz)) count += grid[nx][ny][nz];
            }
        }
    }

    return count;
}

void
conway() {
    for (int x = 0; x < WIDTH; ++x) {
        for (int y = 0; y < HEIGHT; ++y) {
            for (int z = 0; z < DEPTH; ++z) {
                if (grid[x][y][z] == ALIVE) {
                    DrawCube((Vector3) {(float) x, (float) y, (float) z}, 1.0f, 1.0f, 1.0f, SKYBLUE);
                }
            }
        }
    }
}

int
main(void)
{
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE);

    init_grid();

    DisableCursor();
    SetTargetFPS(60);

    int frames = 0;
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, camera_mode);

        if (frames % 10 == 0) update_grid();
        frames++;

        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                conway();
            EndMode3D();
        EndDrawing();
    }
    CloseWindow();

    return 0;
}
