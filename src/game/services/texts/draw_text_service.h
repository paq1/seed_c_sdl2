#ifndef __DRAW_TEXT_SERVICE_H__
#define __DRAW_TEXT_SERVICE_H__

#include "../../models/texts/text.h"

int draw_text(const text_t* text, SDL_Renderer *renderer, int x, int y);

#endif // __DRAW_TEXT_SERVICE_H__