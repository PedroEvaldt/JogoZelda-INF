#include "raylib.h"
#include "jogador.h"
#include "mapa.h"
#include "monstro.h"
#include "vida.h"
#include "espada.h"
#include "barrastatus.h"
#include "menujogo.h"
#include "atualizarstatus.h"
#include "menuprincipal.h"
#include <stdio.h>
#include <stdbool.h>
#define VELOCIDADE_MONSTROS 0.2
#define LARGURA_TELA 1200
#define ALTURA_TELA 860

int main() {
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Zelda-INF"); // Cria janela principal
    SetTargetFPS(60); // Define FPS fixo

    int faseAtual = 1;
    int aux = 0;
    Mapa mapa = carregarMapa(faseAtual); // Carrega mapa da fase
    Jogador jogador = inicializarJogador(mapa); // D5efine posição do jogador
    Monstro monstros[10]; // Até 10 monstros por fase
    Espada espada = inicializarespada(mapa); // Inicializa espada
    int qtdMonstros = inicializarMonstros(mapa, monstros);
    float tempoUltimoMovimento = 0.0f;
    float intervaloMovimento = VELOCIDADE_MONSTROS;
    typedef enum {MENU, JOGO} TelaDoJogo;

    TelaDoJogo tela = MENU;

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
  
    Barra barra = {3, 1, 0, false};
    atualizarbarra(&barra); // Atualiza a barra de status

    while (!WindowShouldClose()) { // Loop principal do jogo
        switch(tela) {
            case MENU:
                aux = exibirMenuPrincipal();
                if(aux == 1)
                    tela = JOGO;
                else if (aux == 3){
                    CloseWindow();
                    return 0;
                }
                break;
            
            case JOGO:
                BeginDrawing();
                ClearBackground(BLACK);

        desenharMapa(mapa); // Renderiza mapa
        desenharbarra(barra);
        atualizarbarra(&barra); // Desenha a barra de status
        atualizarJogador(&jogador, mapa); // Atualiza posição do jogador

        desenharespada(espada);
        atualizarespada(&espada, &jogador, &barra); // Atualiza espada do jogador

        atualizarvida(&jogador, vidas, &barra, quantidade_vidas); // Atualiza vidas do jogador
        desenharVida(vidas, quantidade_vidas); 

        float tempoAtual = GetTime();  // tempo desde que o jogo iniciou (em segundos)
        if (tempoAtual - tempoUltimoMovimento >= intervaloMovimento) {
            moverMonstros(monstros, qtdMonstros, mapa, &jogador, &barra); // só move se passou o intervalo
            tempoUltimoMovimento = tempoAtual; // reinicia o contador
        }

        desenharJogador(jogador); // Desenh5a jogador
        desenharMonstros(monstros, qtdMonstros); // Desenha inimigos

        if(IsKeyPressed(KEY_TAB)) //Abre o menu do jogo caso clique TAB
            {
                aux = exibirMenuJogo();
                if(aux == 5)
                    tela = MENU;
            }

            EndDrawing();
            break;

        EndDrawing();
        descarregarTexturasMapa(&mapa);
        CloseWindow(); // Fecha o jogo
        return 0;}
    }
}


    

// Fim do código principal
