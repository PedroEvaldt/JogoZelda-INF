#include "monstro.h"
#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include "jogador.h"
#include "barrastatus.h"

int inicializarMonstros(Mapa mapa, Monstro monstros[]) {
    int contador = 0;
    srand(time(NULL)); // Inicializa a semente do rand()

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
    for (int i = 0; i < qtd; i++) {
        if (!monstros[i].ativo) continue;

        int dir = rand() % 4;
        int novoX = monstros[i].x;
        int novoY = monstros[i].y;

        switch (dir) {
            case 0: novoY--; monstros[i].direcao = 'N'; break;
            case 1: novoY++; monstros[i].direcao = 'S'; break;
            case 2: novoX--; monstros[i].direcao = 'O'; break;
            case 3: novoX++; monstros[i].direcao = 'L'; break;
        }

        // Verifica se novo local é válido (não parede e dentro dos limites)
        if (novoX >= 0 && novoX < COLUNAS && novoY >= 0 && novoY < LINHAS && mapa.celulas[novoY][novoX] != 'P') {
            monstros[i].x = novoX;
            monstros[i].y = novoY;
        }
        
        if (novoX == jogador->x && novoY == jogador->y) {
            // Lógica de colisão com o jogador
            jogador->vidas--; // Decrementa a vida do jogador
            barra->vidas--;
            sprintf(barra->vidasstr, "VIDAS: %d", barra->vidas); // Atualiza a barra de status
            if (jogador->vidas <= 0) {
                // Lógica para quando o jogador perde todas as vidas
                //DrawText("GAME OVER", LARGURA_TELA / 2 - 100, ALTURA_TELA / 2, 20, RED);
                //EndDrawing();
                return; // Sai da função após perder todas as vidas
            }
        }
    }

}

void desenharMonstros(Monstro monstros[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        if (!monstros[i].ativo) continue;

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
        Rectangle dest = { monstros[i].x * 50.0f, monstros[i].y * 50.0f + 60.0f, 50.0f, 50.0f };
        Vector2 origin = { 0.0f, 0.0f };
        DrawTexturePro(sprite, source, dest, origin, 0.0f, WHITE);
    }
}