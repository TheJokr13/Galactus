#pragma once
#include <SDL_ttf.h>
#include <math.h>

const TTF_Font* fontPixel;

typedef struct SCORE {
    int score;
    int player;
} SCORE;


TTF_Font *init_SCORE() {
    const char* fontPixelPath = "./Pixels.ttf";
    int size = 25;
    
    // Cette fonction doit �tre appel�e une fois au d�but de votre programme

    if (TTF_Init() == -1) {
        printf("Erreur lors de l'initialisation de SDL_ttf: %s\n", TTF_GetError());
    }
    fontPixel = TTF_OpenFont(fontPixelPath, size);
    // Charger la police TrueType � partir d'un fichier
    if (fontPixel == NULL) {
        printf("Erreur lors du chargement de la police : %s\n", TTF_GetError());
    }
    return fontPixel;
}




void DRAW_SCORE(SCORE p1, SCORE p2, render_info* r_i, TTF_Font *fontPixel) {
    int width = SW;
    int height = SH;
    int x = width / 2;
    int y = height / 2;

    // Allouez de la m�moire pour les cha�nes de caract�res score1 et score2
    char score1[20];
    sprintf_s(score1, sizeof(score1), "%d", p1.score);
    char score2[20];
    sprintf_s(score2, sizeof(score2), "%d", p2.score);

    // V�rifiez si le renderer est valide
    if (r_i->renderer == NULL) {
        printf("Renderer non valide\n");
        return;
    }

    SDL_Color White = {255, 255, 255};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(fontPixel, score1, White); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(r_i->renderer, surfaceMessage);
    SDL_Rect Message_rect; 
    Message_rect.x = 80;
    Message_rect.y = 0;
    int i;
    for (i = 0; score1[i] != '\0'; ++i);
    Message_rect.w = 50 * i;
    Message_rect.h = 100;
    SDL_RenderCopy(r_i->renderer, Message, NULL, &Message_rect);

    SDL_DestroyTexture(Message);


    SDL_Surface* surfaceMessage_ = TTF_RenderText_Solid(fontPixel, score2, White); 
    SDL_Texture* Message_ = SDL_CreateTextureFromSurface(r_i->renderer, surfaceMessage_);
    SDL_Rect Message_rect_; 
    for (i = 0; score2[i] != '\0'; ++i);
    Message_rect_.x = SW - 120 * i;
    Message_rect_.y = 0;
    Message_rect_.w = 50 * i;
    Message_rect_.h = 100;
    SDL_RenderCopy(r_i->renderer, Message_, NULL, &Message_rect_);



    SDL_DestroyTexture(Message_);
}