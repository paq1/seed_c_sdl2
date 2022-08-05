#ifndef __WINDOW_GROUP_H__
#define __WINDOW_GROUP_H__

#include <SDL.h>

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} window_group_t;

#endif // __WINDOW_GROUP_H__