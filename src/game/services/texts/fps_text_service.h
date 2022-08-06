#ifndef __FPS_TEXT_SERVICE_H__
#define __FPS_TEXT_SERVICE_H__

#include <SDL.h>
#include <SDL_ttf.h>

#include "../../models/texts/text.h"

text_t* update_fps_text(
    SDL_Renderer* renderer,
    text_t* fps_text,
    int fps,
    TTF_Font* font
);

#endif