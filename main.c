#include "raylib.h"
#include "jogador.h"
#include "mapa.h"
#include "monstro.h"
#include "vida.h"
#include "espada.h"
#include <stdio.h>
#define VELOCIDADE_MONSTROS 0.2
#define LARGURA_TELA 1200
#define ALTURA_TELA 860

int main() {
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Zelda-INF"); // Cria janela principal
    SetTargetFPS(60); // Define FPS fixo

    int faseAtual = 1;
    Mapa mapa = carregarMapa(faseAtual); // Carrega mapa da fase
    Jogador jogador = inicializarJogador(mapa); // Define posição do jogador
    Monstro monstros[10]; // Até 10 monstros por fase
    Espada espada = inicializarespada(mapa); // Inicializa espada
    int qtdMonstros = inicializarMonstros(mapa, monstros);
    float tempoUltimoMovimento = 0.0f;
    float intervaloMovimento = VELOCIDADE_MONSTROS;

    int quantidade_vidas = 0; // Contador de vidas no mapa
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {
            if (mapa.celulas[i][j] == 'V') { // Verifica se há vida no mapa
                quantidade_vidas++;
            }
        }
    }
    Vida vidas[quantidade_vidas];
    inicializarVida(mapa, vidas); // Inicializa vidas no mapa
  

    while (!WindowShouldClose()) { // Loop principal do jogo
        BeginDrawing();
        ClearBackground(BLACK);

        desenharMapa(mapa); // Renderiza mapa
        atualizarJogador(&jogador, mapa); // Atualiza posição do jogador

        desenharespada(espada);
        desenharVida(vidas, quantidade_vidas); 

        float tempoAtual = GetTime();  // tempo desde que o jogo iniciou (em segundos)
        if (tempoAtual - tempoUltimoMovimento >= intervaloMovimento) {
            moverMonstros(monstros, qtdMonstros, mapa); // só move se passou o intervalo
            tempoUltimoMovimento = tempoAtual; // reinicia o contador
        }

        desenharJogador(jogador); // Desenh5a jogador
        desenharMonstros(monstros, qtdMonstros); // Desenha inimigos

        EndDrawing();
    }
    descarregarTexturasMapa(&mapa);
    CloseWindow(); // Fecha o jogo
    return 0;
}

// Fim do código principal
