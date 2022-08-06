#include "font_factory.h"

TTF_Font* create_comic_font(int size) {
    return TTF_OpenFont("assets/fonts/dpcomic.ttf", 25);
}
