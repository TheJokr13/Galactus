#pragma once

#include <SDL.h>
#include <SDL_TTF.h>


#define WS_UN SDL_WINDOWPOS_UNDEFINED
#define W_S SDL_WINDOW_SHOWN
#define R_P_S SDL_RENDERER_PRESENTVSYNC

//Taille de la fen�tre
#define SW 1920
#define SH 1080

typedef struct render_info {
    SDL_Window* window;
    SDL_Renderer* renderer;
    int err;
} render_info;

render_info init_render_info(SDL_Window* window, SDL_Renderer* renderer, int err) {
    render_info renderInfo = { .window = window,.renderer = renderer,.err = err };
    return renderInfo;
}

render_info init_renderer() {
    // Initialisation de la SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur lors de l'initialisation de la SDL : %s\n", SDL_GetError());
        return init_render_info(NULL, NULL, -1);
    }
    // Cr�ation de la fen�tre
    SDL_Window* window = SDL_CreateWindow("PONG !", WS_UN, WS_UN, SW, SH, W_S | R_P_S);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenètre : %s\n", SDL_GetError());
        SDL_Quit();
        return init_render_info(window, NULL, -1);
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Pong\n");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return init_render_info(window, renderer, -1);
    }
    return init_render_info(window, renderer, 0);
}


int handle_events(render_info* render_info, int* keys) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            // Fermeture de la fen�tre et de la SDL
            SDL_DestroyRenderer(render_info->renderer);
            SDL_DestroyWindow(render_info->window);
            SDL_Quit();
            return 1;
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_UP)keys[0] = 1;
            if (event.key.keysym.sym == SDLK_DOWN)keys[1] = 1;
            if (event.key.keysym.sym == SDLK_z)keys[2] = 1;
            if (event.key.keysym.sym == SDLK_s)keys[3] = 1;
        }
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_UP)keys[0] = 0;
            if (event.key.keysym.sym == SDLK_DOWN)keys[1] = 0;
            if (event.key.keysym.sym == SDLK_z)keys[2] = 0;
            if (event.key.keysym.sym == SDLK_s)keys[3] = 0;
        }
    }
    return 0;
}
// Function to load an image
SDL_Texture* loadTexture(SDL_Renderer *renderer, const char *file) {
    SDL_Surface* surface = SDL_LoadBMP(file);
    if (surface == NULL) {
        // Handle error
        printf("Unable to load image %s! SDL_image Error: %s\n", file);
        return NULL;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture == NULL)
    {
        printf("Unable to create texture from %s! SDL Error: %s\n", file);
    }
    //SDL_FreeSurface(surface);
    return texture;
}

