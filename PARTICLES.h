#pragma once

typedef struct PARTICLE { int r; int g; int b; int x; int y; int vx; int vy; float opacity; float MAX_life_time; float C_life_time;}PARTICLE;

PARTICLE init_particle(int r, int g, int b, int x, int y, int vx, int vy, float opacity, float MAX_life_time, float C_life_time) {
    PARTICLE _ = {.r = r, .g = g, .b = b, .x = x, .y = y, .vx = vx, .vy = vy, .opacity = opacity, .MAX_life_time = MAX_life_time,.C_life_time = C_life_time};
    return _;
}

void UPDATE_PARTICLES(PARTICLE* PARTICLES, int PARTICLE_COUNT, render_info* r_i) {
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        // PARTICLES[i].
        if (PARTICLES[i].C_life_time >= PARTICLES[i].MAX_life_time) continue;
        PARTICLES[i].x += PARTICLES[i].vx;
        PARTICLES[i].y += PARTICLES[i].vy;
        if (PARTICLES[i].y < 0) PARTICLES[i].vy *= -1;
        if (PARTICLES[i].y + 5 > SH) PARTICLES[i].vy *= -1;
        PARTICLES[i].opacity = 255.0 - (255.0 * (PARTICLES[i].C_life_time/PARTICLES[i].MAX_life_time));
        PARTICLES[i].C_life_time += 1;
        SDL_Rect sq = { PARTICLES[i].x, PARTICLES[i].y, 5, 5};
        SDL_SetRenderDrawColor(r_i->renderer, PARTICLES[i].r, PARTICLES[i].g, PARTICLES[i].b, PARTICLES[i].opacity);
        SDL_RenderFillRect(r_i->renderer, &sq);
    }
}

void init_BLOW_EFFECT(PARTICLE* PARTICLES, int PARTICLE_COUNT, CUBE C, int life_time) {
    for (int i = 0; i < PARTICLE_COUNT; i++) {
        float vx = randomfloatinrange((float)2.0, (float)5.0);
        float vy = randomfloatinrange((float)-5.0, (float)5.0);
        vx = (C.vx > 0) ? vx : -vx;
        PARTICLES[i] = init_particle(randominrange(0, 255), randominrange(0, 255), randominrange(0, 255), C.px, C.py, vx, vy, 255, life_time, 1);
    }
}
