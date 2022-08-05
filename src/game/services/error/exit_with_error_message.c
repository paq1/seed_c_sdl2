#include "exit_with_error_message.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>

void exitWithError(const char *message) {
    SDL_Log("ERREUR : %s > %s\n", message, SDL_GetError());
    TTF_Quit();
    SDL_Quit();
    exit(EXIT_FAILURE);
}
