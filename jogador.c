#include "jogador.h"
#include "raylib.h"
#include "vida.h"

Jogador inicializarJogador(Mapa mapa) {
    Jogador jogador = {0};  // zera a struct
    jogador.vidas = 3;
    jogador.pontuacao = 0;
    jogador.espada = false;

    jogador.jogador_sul = LoadTexture("sprites/jogador-sul.png");
    jogador.jogador_norte = LoadTexture("sprites/jogador-norte.png");
    jogador.jogador_leste = LoadTexture("sprites/jogador-leste.png");
    jogador.jogador_oeste = LoadTexture("sprites/jogador-oeste.png");

    for (int i = 0; i < 16; i++) {
        for (int k = 0; k < 24; k++) {
            if (mapa.celulas[i][k] == 'J') {
                jogador.x = k;
                jogador.y = i;
                return jogador;
            }
        }
    }

    return jogador;
}

void atualizarJogador(Jogador *jogador, Mapa mapa) {

    int novoX = jogador->x;
    int novoY = jogador->y;
    if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) {
        novoX += 1;
        jogador->direcao = 'L'; // leste
    } else if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) {
        novoX -= 1;
        jogador->direcao = 'O'; // oeste
    } else if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) {
        novoY -= 1;
        jogador->direcao = 'N'; // norte
    } else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) {
        novoY += 1;
        jogador->direcao = 'S'; // sul
    }

    // Se a nova posição for válida (não for parede)
    if (mapa.celulas[novoY][novoX] != 'P' && novoX >= 0 && novoX < COLUNAS && novoY >= 0 && novoY < LINHAS) {
        jogador->x = novoX;
        jogador->y = novoY;
    }
}

void desenharJogador(Jogador jogador) {
    Texture2D sprite;
    switch (jogador.direcao) {
        case 'N': sprite = jogador.jogador_norte; break;
        case 'S': sprite = jogador.jogador_sul; break;
        case 'L': sprite = jogador.jogador_leste; break;
        case 'O': sprite = jogador.jogador_oeste; break;
        default:  sprite = jogador.jogador_sul; break; // caso genérico
    }
    Rectangle source = { 0.0f, 0.0f, (float)sprite.width, (float)sprite.height };
    Rectangle dest = { jogador.x * 50.0f, jogador.y * 50.0f + 60.0f, 50.0f, 50.0f };
    Vector2 origin = { 0.0f, 0.0f };
    DrawTexturePro(sprite, source, dest, origin, 0.0f, WHITE);
}

