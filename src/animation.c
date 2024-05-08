#include "conway.h"

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
