#include "draw_sprite_service.h"

int draw_sprite(const sprite_t *sprite, SDL_Renderer *renderer) {

    SDL_Rect rect = {sprite->x, sprite->y, sprite->w, sprite->h};

    // on recupere la taille de la texture
    if (SDL_QueryTexture(sprite->texture, NULL, NULL, &rect.w, &rect.h) != 0) {
        return -1;
    }

    if (SDL_RenderCopy(renderer, sprite->texture, NULL, &(SDL_Rect){sprite->x, sprite->y, rect.w, rect.h}) != 0) {
        return -1;
    }
}

int draw_sprite_with_scale(const sprite_t *sprite, SDL_Renderer *renderer, double scaleX, double scaleY) {
    SDL_Rect rect = {sprite->x, sprite->y, sprite->w, sprite->h};

    // on recupere la taille de la texture
    if (SDL_QueryTexture(sprite->texture, NULL, NULL, &rect.w, &rect.h) != 0) {
        return -1;
    }

    return SDL_RenderCopy(renderer, sprite->texture, NULL, &(SDL_Rect){sprite->x, sprite->y, rect.w * scaleX, rect.h * scaleY});
}
