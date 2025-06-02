#include "mapa.h"
#include <stdio.h>
#include "raylib.h"

Mapa carregarMapa(int fase) {
    Mapa mapa;
    char nomeArquivo[20];
    sprintf(nomeArquivo, "mapa%02d.txt", fase);


    FILE *fp = fopen(nomeArquivo, "r");
    if (!fp) {
        for (int i = 0; i < LINHAS; i++)
            for (int j = 0; j < COLUNAS; j++)
                mapa.celulas[i][j] = ' ';
        return mapa;
    }

    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++){
            int ch;
            do {
                ch = fgetc(fp);
            } while (ch == '\n' || ch == '\r');
            mapa.celulas[i][j] = (char)ch;
        }

    fclose(fp);
    mapa.parede = LoadTexture("sprites/parede.png");
    mapa.espada = LoadTexture("sprites/espada.png");
    mapa.vida = LoadTexture("sprites/vida.png");
    mapa.chao = LoadTexture("sprites/chao.png");
    return mapa;
}

void desenharMapa(Mapa mapa) {
    Texture2D sprite;
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            switch (mapa.celulas[i][j]) {
                case 'P': sprite = mapa.parede; break;
                case ' ': sprite = mapa.chao; break;
                default: sprite = mapa.chao; break;
            }
            Rectangle source = {0.0f, 0.0f, (float)sprite.width, (float)sprite.height};
            Rectangle dest = { j * TAM_CELULA, i * TAM_CELULA + TAM_MENUJOGO, TAM_CELULA, TAM_CELULA };
            Vector2 origin = { 0.0f, 0.0f };
            DrawTexturePro(sprite, source, dest, origin, 0.0f, WHITE);
        }
    }
}

void descarregarTexturasMapa(Mapa *mapa) {
    UnloadTexture(mapa->parede);
    UnloadTexture(mapa->espada);
    UnloadTexture(mapa->vida);
    UnloadTexture(mapa->chao);
}