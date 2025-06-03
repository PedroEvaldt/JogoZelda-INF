#include "raylib.h"
#include "monstro.h"
#include "jogador.h"

int inicializarMonstros(Mapa mapa, Monstro monstros[]) {
    int contador = 0;
    srand(time(NULL)); // Semente para geração aleatória

    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (mapa.celulas[i][j] == 'M' && contador < 10) {
                monstros[contador].x = j;
                monstros[contador].y = i;
                monstros[contador].direcao = 'N';
                monstros[contador].pontuacao = rand() % 101;
                monstros[contador].ativo = true;
                monstros[contador].monstro = LoadTexture("sprites/monstro.png");
                monstros[contador].monstro_norte = LoadTexture("sprites/monstro-norte.png");
                monstros[contador].monstro_sul = LoadTexture("sprites/monstro-sul.png");
                monstros[contador].monstro_leste = LoadTexture("sprites/monstro-leste.png");
                monstros[contador].monstro_oeste = LoadTexture("sprites/monstro-oeste.png");
                contador++;
            }
        }
    }
    

    return contador;
}

void moverMonstros(Monstro monstros[], int qtd, Mapa mapa, Jogador *jogador, Barra *barra) {
    int raio_perseguir = 7;

    for (int i = 0; i < qtd; i++) {
        if (!monstros[i].ativo) continue;

        int dx = jogador->x - monstros[i].x;
        int dy = jogador->y - monstros[i].y;
        int distancia = abs(dx) + abs(dy);

        int novoX = monstros[i].x;
        int novoY = monstros[i].y;

        if (distancia <= raio_perseguir) {
            // Movimento inteligente em direção ao jogador
            if (abs(dx) > abs(dy)) {
                novoX += (dx > 0) ? 1 : -1;
                monstros[i].direcao = (dx > 0) ? 'L' : 'O';
            } else if (dy != 0) {
                novoY += (dy > 0) ? 1 : -1;
                monstros[i].direcao = (dy > 0) ? 'S' : 'N';
            }
        } 
        else {
            // Movimento aleatório
            int dir = rand() % 4;
            switch (dir) {
                case 0: novoY--; monstros[i].direcao = 'N'; break;
                case 1: novoY++; monstros[i].direcao = 'S'; break;
                case 2: novoX--; monstros[i].direcao = 'O'; break;
                case 3: novoX++; monstros[i].direcao = 'L'; break;
            }
        }

        // Verifica se destino é válido e não é parede
        if (novoX >= 0 && novoX < COLUNAS && novoY >= 0 && novoY < LINHAS && mapa.celulas[novoY][novoX] != 'P') {

            // Verifica colisão com jogador
            if (novoX == jogador->x && novoY == jogador->y) {
                if (GetTime() - jogador->tempo_ultimo_dano > 1.0) {
                    jogador->vidas--;
                    barra->vidas--;
                    sprintf(barra->vidasstr, "VIDAS: %d", barra->vidas);
                    jogador->tempo_ultimo_dano = GetTime();

                    // Knockback do jogador
                    int knockX = jogador->x - monstros[i].x;
                    int knockY = jogador->y - monstros[i].y;
                    int destinoX = jogador->x + knockX;
                    int destinoY = jogador->y + knockY;

                    if (destinoX >= 0 && destinoX < COLUNAS && destinoY >= 0 && destinoY < LINHAS && mapa.celulas[destinoY][destinoX] != 'P') {
                        jogador->x = destinoX;
                        jogador->y = destinoY;
                    }
                }
                // Monstro não se move se colidir com jogador
            } else {
                // Move monstro
                monstros[i].x = novoX;
                monstros[i].y = novoY;
            }
        }

        if (jogador->vidas <= 0) return;
    }
}

void desenharMonstros(Monstro monstros[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        if (monstros[i].ativo) {
            Texture2D sprite;
            switch (monstros[i].direcao) {
                case 'N': sprite = monstros[i].monstro_norte; break;
                case 'S': sprite = monstros[i].monstro_sul; break;
                case 'L': sprite = monstros[i].monstro_leste; break;
                case 'O': sprite = monstros[i].monstro_oeste; break;
                default:  sprite = monstros[i].monstro; break; // caso genérico
            }

            // Desenha o sprite redimensionado em 50x50 pixels
            Rectangle source = { 0.0f, 0.0f, (float)sprite.width, (float)sprite.height };
            Rectangle dest = { monstros[i].x * TAM_CELULA, monstros[i].y * TAM_CELULA + TAM_MENUJOGO, TAM_CELULA, TAM_CELULA };
            Vector2 origin = { 0.0f, 0.0f };
            DrawTexturePro(sprite, source, dest, origin, 0.0f, WHITE);}
        }
}