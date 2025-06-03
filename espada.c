#include "raylib.h"
#include "espada.h"

Espada inicializarespada(Mapa mapa) {
    Espada espada = {0};  // zera a struct
    espada.espada = false;
    espada.espada_textura = LoadTexture("sprites/espada.png");

    for (int i = 0; i < LINHAS; i++) {
        for (int k = 0; k < COLUNAS; k++) {
            if (mapa.celulas[i][k] == 'E') {
                espada.x = k;
                espada.y = i;
                espada.espada = true; // marca que a espada foi encontrada
                return espada;
            }
        }
    }

    return espada;
}

void desenharespada(Espada espada) {
    if (!espada.espada) return; // Se a espada não estiver ativa, não desenha
    Texture2D sprite;
    sprite = espada.espada_textura;
    Rectangle source = { 0.0f, 0.0f, (float)sprite.width, (float)sprite.height };
    Rectangle dest = { espada.x * TAM_CELULA, espada.y * TAM_CELULA + TAM_MENUJOGO, TAM_CELULA, TAM_CELULA };
    Vector2 origin = { 0.0f, 0.0f };
    DrawTexturePro(sprite, source, dest, origin, 0.0f, WHITE);
    
}

int ataqueEspada(Espada *espada, Jogador *jogador, Texture2D sprite, Mapa *mapa, int qnt_monstros, Monstro monstros[]) {
    int monstros_mortos = 0;
    if (!(jogador->espada)) return 0;
    if (IsKeyDown(KEY_J)) {
    
        int dx = 0, dy = 0;
        float rotacao = 0;
        
        switch (jogador->direcao) {
            case 'N': dy = -1; rotacao = 0.0f; break;
            case 'S': dy =  1; rotacao = 180.0f; break;
            case 'L': dx =  1; rotacao = 90.0f; break;
            case 'O': dx = -1; rotacao = 270.0f; break;
            default: return 0;
        }

        for (int i = 1; i < 4; i++) {

            int celulaX = jogador->x + (i * dx);
            int celulaY = jogador->y + (i * dy);
            float destinoX = celulaX * TAM_CELULA;
            float destinoY = celulaY * TAM_CELULA + TAM_MENUJOGO;
        
            if (celulaY < 0 || celulaY >= LINHAS || celulaX < 0 || celulaX >= COLUNAS) break;

            if (mapa->celulas[celulaY][celulaX] == 'P') break;

            Rectangle source = { 0.0f, 0.0f, (float)sprite.width, (float)sprite.height };
            Rectangle dest = { destinoX, destinoY, TAM_CELULA, TAM_CELULA };
            Vector2 origin = { TAM_CELULA / 2.0f, TAM_CELULA / 2.0f };

            // Ajusta o centro para girar corretamente
            dest.x += TAM_CELULA / 2.0f;
            dest.y += TAM_CELULA / 2.0f;
            
            for (int a = 0; a < qnt_monstros; a++){
                if (celulaX == monstros[a].x && celulaY == monstros[a].y) {
                    if (monstros[a].ativo) {
                        monstros[a].ativo = false; // Derrota o monstro
                        jogador->pontuacao += monstros[a].pontuacao; // Adiciona pontuação
                        mapa->celulas[celulaY][celulaX] = ' '; // Remove o monstro do mapa
                        monstros_mortos++;
                    }
                }
            }

            DrawTexturePro(sprite, source, dest, origin, rotacao, WHITE);
        }
    }
    return monstros_mortos;
}