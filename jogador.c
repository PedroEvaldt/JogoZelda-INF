#include "jogador.h"
#include "raylib.h"
#include "monstro.h"
#include "barrastatus.h"
#define VELOCIDADE_JOGADOR 1

Jogador inicializarJogador(Mapa mapa) {
    Jogador jogador = {0};  // zera a struct
    jogador.vidas = 3;
    jogador.pontuacao = 0;
    jogador.espada = false;
    jogador.tempo_ultimo_dano = 0.0;

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

void atualizarJogador(Jogador *jogador, Mapa mapa, Monstro monstros[], int qnt_monstros, Barra *barra) {
    static double tempoUltimoMovimento = 0;
    double tempoAtual = GetTime();
    double intervaloMovimento = 0.15;

    if (tempoAtual - tempoUltimoMovimento < intervaloMovimento)
        return;

    int novoX = jogador->x;
    int novoY = jogador->y;
    bool moveu = false;

    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        novoX += 1;
        jogador->direcao = 'L';
        moveu = true;
    } else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        novoX -= 1;
        jogador->direcao = 'O';
        moveu = true;
    } else if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        novoY -= 1;
        jogador->direcao = 'N';
        moveu = true;
    } else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        novoY += 1;
        jogador->direcao = 'S';
        moveu = true;
    }

    if (!moveu)
        return;

    // Verifica se destino está dentro dos limites do mapa
    if (novoX < 0 || novoX >= COLUNAS || novoY < 0 || novoY >= LINHAS)
        return;

    // Verifica se é parede
    if (mapa.celulas[novoY][novoX] == 'P')
        return;

    // Verifica se há monstro no destino
    bool temMonstro = false;
    for (int i = 0; i < qnt_monstros; i++) {
        if (monstros[i].ativo && monstros[i].x == novoX && monstros[i].y == novoY) {
            temMonstro = true;
            break;
        }
    }

    if (temMonstro) {
        if (tempoAtual - jogador->tempo_ultimo_dano >= 1.0) {
            jogador->vidas--;
            barra->vidas--;
            sprintf(barra->vidasstr, "VIDAS: %d", barra->vidas);
            jogador->tempo_ultimo_dano = tempoAtual;

            // Knockback (empurra jogador para trás)
            int dx = jogador->x - novoX;
            int dy = jogador->y - novoY;
            int destinoX = jogador->x + dx;
            int destinoY = jogador->y + dy;

            // Verifica se o knockback é possível
            if (destinoX >= 0 && destinoX < COLUNAS &&
                destinoY >= 0 && destinoY < LINHAS &&
                mapa.celulas[destinoY][destinoX] != 'P') {
                jogador->x = destinoX;
                jogador->y = destinoY;
            }
        }
    } else {
        jogador->x = novoX;
        jogador->y = novoY;
        tempoUltimoMovimento = tempoAtual;
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
    Rectangle dest = { jogador.x * TAM_CELULA, jogador.y * TAM_CELULA + TAM_MENUJOGO, TAM_CELULA, TAM_CELULA };
    Vector2 origin = { 0.0f, 0.0f };
    DrawTexturePro(sprite, source, dest, origin, 0.0f, WHITE);
}