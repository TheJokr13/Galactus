#define SDL_MAIN_HANDLED
#define FRAMERATE 1000/60
#include <stdio.h>
#include <stdlib.h>

#include "render.h"
#include "UTILS.h"
#include "SCORE.h"
#include "INIT_MAP.h"

float randomfloatinrange(float min, float max) {
    return min + (float)(rand()) * (float)(max - min) / RAND_MAX;
}

#include "PARTICLES.h"
#include "PHYSC.h"
// #include "AUDIO.h"



int randominrange(int min, int max) { return(rand() % (max - min + 1)) + min; }



int main(int argc, char* argv[]) {
    TTF_Init();
    render_info render_info = init_renderer();
    SDL_SetRenderDrawBlendMode(render_info.renderer, SDL_BLENDMODE_BLEND);
    if (render_info.err != 0)return render_info.err;
    int LAST_HITTED = -1;
    SCORE p1_score={0, 1};SCORE p2_score={0, 2};TTF_Font *fontPixel=init_SCORE();
    CUBE CUBE[1]; SLIDER SLIDERS[2]; init_MAP(CUBE, SLIDERS);
    int keys[4]; keys[0] = 0; keys[1] = 0; keys[2] = 0; keys[3] = 0;
    int PARTICLE_COUNT = 11; PARTICLE PARTICLES[11];
    int PARTICLE_COUNT_GOAL = 60; PARTICLE PARTICLES_GOAL[60];
    SDL_Texture*backgroundTexture = loadTexture(render_info.renderer, "back.bmp"); //le fond c'est pour vous troll vous pouvez mettre un autre avec le back.png (faut le convertir en.bmp)
    SDL_Event event;
    while (1) {
        int events_info = handle_events(&render_info, keys);
        if (events_info != 0)return events_info;
        SDL_SetRenderDrawColor(render_info.renderer, 0, 0, 0, 255);
        SDL_RenderClear(render_info.renderer); // more of a fill
        SDL_RenderCopy(render_info.renderer, backgroundTexture, NULL, NULL);
        LAST_HITTED = UPDATE_TICK_CUBE(CUBE, SLIDERS, &p1_score, &p2_score, LAST_HITTED, 
        &PARTICLES, PARTICLE_COUNT, &PARTICLES_GOAL, PARTICLE_COUNT_GOAL);
        UPDATE_TICK_SLIDERS(keys, SLIDERS);
        DRAW_OBJS(CUBE, SLIDERS, &render_info);
        UPDATE_PARTICLES(&PARTICLES, PARTICLE_COUNT, &render_info);
        UPDATE_PARTICLES(&PARTICLES_GOAL, PARTICLE_COUNT_GOAL, &render_info);
        DRAW_SCORE(p1_score, p2_score, &render_info, fontPixel);
        SDL_RenderPresent(render_info.renderer); // update display
        SDL_Delay(FRAMERATE);}
    SDL_DestroyRenderer(render_info.renderer);
    SDL_DestroyWindow(render_info.window);
    SDL_Quit(); return 0;
}