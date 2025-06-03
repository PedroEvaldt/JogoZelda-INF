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

typedef enum {MENU, JOGO, GAMEOVER} TelaDoJogo;
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

void exibirGameOver(Jogador *jogador, TelaDoJogo *tela, Font fonte_gameover, Font font_pontuacao) {
    while (!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(BLACK);

            // Texto principal
            const char *titulo = "GAME OVER";
            float tamanhoFonteTitulo = 50;
            float espacamento = 2.0f;
            Vector2 tamanhoTexto = MeasureTextEx(fonte_gameover, titulo, tamanhoFonteTitulo, espacamento);
            DrawTextEx(fonte_gameover, titulo, (Vector2){(LARGURA_TELA - tamanhoTexto.x) / 2.0f, 300}, tamanhoFonteTitulo, espacamento, RED);

            //(ALTURA_TELA - tamanhoTexto.y) / 2.0f
            // Pontuação
            char pontuacao[50];
            sprintf(pontuacao, "SCORE: %d", jogador->pontuacao);
            float tamanhoFonteScore = 30;
            float espacamentoScore = 1.0f;
            Vector2 tamanhoTextoScore = MeasureTextEx(font_pontuacao, pontuacao, tamanhoFonteScore, espacamentoScore);
            DrawTextEx(font_pontuacao, pontuacao, (Vector2){(LARGURA_TELA - tamanhoTextoScore.x) / 2.0f, 380}, tamanhoFonteScore, espacamentoScore, WHITE);

            // Instrução
            const char *instrucao = "Pressione ESPACO para voltar ao menu";
            float tamanhoFonteInstrucao = 20;
            float espacamentoMsg = 0.7f;
            Vector2 tamanhoTextoMsg = MeasureTextEx(font_pontuacao, instrucao, tamanhoFonteInstrucao, espacamentoMsg);
            DrawTextEx(font_pontuacao, instrucao, (Vector2){(LARGURA_TELA - tamanhoTextoMsg.x) / 2.0f, 480}, tamanhoFonteInstrucao, espacamentoMsg, WHITE);

        EndDrawing();

        if (IsKeyPressed(KEY_SPACE)) {
            *tela = MENU;
            break;
        }
    }
}

void reiniciarJogo(Jogador *jogador, Mapa *mapa, Monstro monstros[], int *qtdMonstros, Espada *espada, Vida vidas[], int *quantidade_vidas, Barra *barra, int faseAtual)
{
    *mapa = carregarMapa(faseAtual); 
    *jogador = inicializarJogador(*mapa); 
    *qtdMonstros = inicializarMonstros(*mapa,monstros);
    *espada = inicializarespada(*mapa);
    *quantidade_vidas = inicializarVida(*mapa, vidas);

    barra->vidas = 3; 
    barra->nivel= 1; 
    barra->escore = 0;
    barra->espada = false; 
    atualizarbarra(barra);
}


int main() {
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Zelda-INF"); // Cria janela principal
    SetTargetFPS(VELOCIDADE_TELA); // Define FPS fixo
    

    int faseAtual = 1;
    int aux = 0, space = 0;

    Texture2D sprite = LoadTexture("sprites/espada.png");
    Mapa mapa = carregarMapa(faseAtual); // Carrega mapa da fase
    Jogador jogador = inicializarJogador(mapa); // Define posição do jogador
    Monstro monstros[10]; // Até 10 monstros por fase
    Espada espada = inicializarespada(mapa); // Inicializa espada
    int qtdMonstros = inicializarMonstros(mapa, monstros);
    float tempoUltimoMovimento = 0.0f;
    float intervaloMovimento = VELOCIDADE_MONSTROS;


    TelaDoJogo tela = MENU;

    sprite = LoadTexture("sprites/espada.png"); 
    Font fonte_gameover = LoadFont("Fontes/GAMEOVER.TTF"); 
    Font font_pontuacao = LoadFont("Fontes/PressStart2P.ttf");

    Vida vidas[100]; 
    int quantidade_vidas = inicializarVida(mapa, vidas); // Inicializa vidas
  
    Barra barra = {3, 1, 0, false};
    atualizarbarra(&barra); // Atualiza a barra de status

    while (!WindowShouldClose()) { // Loop principal do jogo
        switch(tela) {
            case MENU:
                aux = exibirMenuPrincipal();
                if(aux == 1){
                    space = exibirTelaInfo();
                    if(space == 4)
                        reiniciarJogo(&jogador, &mapa, monstros, &qtdMonstros, &espada, vidas, &quantidade_vidas, &barra, faseAtual);
                        tempoUltimoMovimento = 0.0f;
                        tela = JOGO;
                }
                else if(aux == 3){
                    CloseWindow();
                    return 0;
                }
                break;     

            case GAMEOVER:
                    jogador.pontuacao = barra.escore;
                    exibirGameOver(&jogador, &tela,fonte_gameover, font_pontuacao);
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
                int qntmonstros_mortos = ataqueEspada(&espada, &jogador, sprite, &mapa, qtdMonstros, monstros); // Atualiza espada do jogador

                atualizarscore(&barra, qntmonstros_mortos); // Atualiza escore do jogador
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
                if (jogador.vidas <= 0) { 
                    tela = GAMEOVER; 
                    break;
                }
                    EndDrawing();
                    break;

        }
    }
        descarregarTexturasMapa(&mapa);
        descarregarJogador(&jogador);
        descarregarEspada(&espada);
        descarregarVidas(vidas, quantidade_vidas);
        descarregarMonstros(monstros, qtdMonstros);
        UnloadTexture(sprite);

        UnloadFont(fonte_gameover);
        UnloadFont(font_pontuacao);

        CloseWindow(); // Fecha janela
        return 0;
    
}


    

// Fim do código principal
