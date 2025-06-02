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
#include <time.h>

#define VELOCIDADE_MONSTROS 0.25
#define LARGURA_TELA 1200
#define ALTURA_TELA 860
#define VELOCIDADE_TELA 15 // FPS

// Funções para descarregar texturas
void descarregarJogador(Jogador *j) {
    UnloadTexture(j->jogador_norte);
    UnloadTexture(j->jogador_sul);
    UnloadTexture(j->jogador_leste);
    UnloadTexture(j->jogador_oeste);
}

void descarregarEspada(Espada *e) {
    UnloadTexture(e->espada_textura);
}

void descarregarVidas(Vida vidas[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        UnloadTexture(vidas[i].vida_textura);
    }
}

void descarregarMonstros(Monstro monstros[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        UnloadTexture(monstros[i].monstro);
        UnloadTexture(monstros[i].monstro_norte);
        UnloadTexture(monstros[i].monstro_sul);
        UnloadTexture(monstros[i].monstro_leste);
        UnloadTexture(monstros[i].monstro_oeste);
    }
}


int main() {
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Zelda-INF"); // Cria janela principal
    SetTargetFPS(VELOCIDADE_TELA); // Define FPS fixo
    

    int faseAtual = 1;
    int aux = 0;

    Texture2D sprite = LoadTexture("sprites/espada.png");
    Mapa mapa = carregarMapa(faseAtual); // Carrega mapa da fase
    Jogador jogador = inicializarJogador(mapa); // Define posição do jogador
    Monstro monstros[10]; // Até 10 monstros por fase
    Espada espada = inicializarespada(mapa); // Inicializa espada
    int qtdMonstros = inicializarMonstros(mapa, monstros);
    float tempoUltimoMovimento = 0.0f;
    float intervaloMovimento = VELOCIDADE_MONSTROS;

    typedef enum {MENU, JOGO} TelaDoJogo;
    TelaDoJogo tela = MENU;

    Vida vidas[100]; 
    int quantidade_vidas = inicializarVida(mapa, vidas); // Inicializa vidas
  
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
                atualizarJogador(&jogador, mapa, monstros, qtdMonstros, &barra); // Atualiza posição do jogador

                desenharespada(espada);
                atualizarespada(&espada, &jogador, &barra);
                ataqueEspada(&espada, &jogador, sprite, &mapa, qtdMonstros, monstros); // Atualiza espada do jogador

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

            
        descarregarTexturasMapa(&mapa);
        descarregarJogador(&jogador);
        descarregarEspada(&espada);
        descarregarVidas(vidas, quantidade_vidas);
        descarregarMonstros(monstros, qtdMonstros);
        UnloadTexture(sprite);
        CloseWindow(); // Fecha janela
        return 0;}
    }
}


    

// Fim do código principal
