#include "vida.h"

int inicializarVida(Mapa mapa, Vida vidas[]) {
    int contador = 0;
    Texture2D vida_textura = LoadTexture("sprites/vida.png");
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (mapa.celulas[i][j] == 'V') {
                vidas[contador].x = j;
                vidas[contador].y = i;
                vidas[contador].ativa = true;
                vidas[contador].vida_textura = vida_textura;
                contador++;
            }
        }
    }
    return contador;
}

void desenharVida(Vida vidas[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        if (vidas[i].ativa) {
            Texture2D sprite = vidas[i].vida_textura;
            Rectangle source = { 0.0f, 0.0f, (float)sprite.width, (float)sprite.height };
            Rectangle dest = { vidas[i].x * TAM_CELULA, vidas[i].y * TAM_CELULA + TAM_MENUJOGO, TAM_CELULA, TAM_CELULA };
            Vector2 origin = { 0.0f, 0.0f };
            DrawTexturePro(sprite, source, dest, origin, 0.0f, WHITE);
        }
    }
}
    
