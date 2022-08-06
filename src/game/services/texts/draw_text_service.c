#include "draw_text_service.h"

int draw_text(const text_t* text, SDL_Renderer *renderer, int x, int y) {
    SDL_Rect rect = {x, y, 0, 0};
    if (SDL_QueryTexture(text->texture, NULL, NULL, &rect.w, &rect.h) != 0) {
        return -1;
    }
    return SDL_RenderCopy(renderer, text->texture, NULL, &rect) != 0;
}
