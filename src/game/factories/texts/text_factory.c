#include "text_factory.h"

text_t* create_fps_text(SDL_Renderer* renderer, TTF_Font* font) {
    text_t* text = create_text(renderer, "FPS: 0", 0, 0, font, (SDL_Color){255, 255, 255, 255});
    return text;
}
