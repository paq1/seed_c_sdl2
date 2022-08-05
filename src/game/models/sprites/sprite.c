#include "sprite.h"

sprite_t * create_sprite_bmp(const char *path, SDL_Renderer *renderer) {
    SDL_Surface *surfaceSmiley = SDL_LoadBMP("assets/sprites/smiley_sdl_seed.bmp");
    if (surfaceSmiley == NULL) {
        return NULL;
    }

    SDL_Texture *textureSmiley = SDL_CreateTextureFromSurface(renderer, surfaceSmiley);
    if (textureSmiley == NULL) {
        SDL_FreeSurface(surfaceSmiley);
        return NULL;
    }
    SDL_FreeSurface(surfaceSmiley);

    sprite_t *sprite = (sprite_t *) SDL_malloc(sizeof(sprite_t));
    *sprite = (sprite_t){0, 0, 0, 0, textureSmiley};

    return sprite;
}

void free_sprite(sprite_t *sprite) {
    SDL_DestroyTexture(sprite->texture);
    free(sprite);
}