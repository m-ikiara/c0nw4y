#include "conway.h"

int
main(void)
{
   InitWindow(width, height, WINDOW_TITLE);

   DisableCursor();
   SetTargetFPS(60);
   while (!WindowShouldClose()) {
       BeginDrawing();
           ClearBackground(RAYWHITE);
        EndDrawing();
   }
   CloseWindow();

   return 0;
}
