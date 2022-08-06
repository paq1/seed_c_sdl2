#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <SDL.h>

typedef struct {
    int x, y;
    int w, h;
    SDL_Texture *texture;
} sprite_t;

sprite_t * create_sprite_bmp(const char *path, SDL_Renderer *renderer);
void free_sprite(sprite_t** sprite);

#endif // __SPRITE_H__
