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
#include "score.h"
#include "caminho.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

typedef enum {MENU, JOGO, GAMEOVER} TelaDoJogo;
#define VELOCIDADE_MONSTROS 0.5
#define LARGURA_TELA 1200
#define ALTURA_TELA 860
#define VELOCIDADE_TELA 120 // FPS

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

void exibirvitoria(Jogador *jogador, TelaDoJogo *tela, Font fonte_vitoria, Font fonte_escrita, char *nomejogador) {
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);
        int espacamento = 0.7f;
        char vitoria[100];
        sprintf(vitoria, "Parabens %s, voce venceu!", nomejogador);
        float tamanhoFontevitoria = 30;
        Vector2 tamanhoTextovitoria = MeasureTextEx(fonte_vitoria, vitoria, tamanhoFontevitoria, espacamento);
        DrawTextEx(fonte_vitoria, vitoria, (Vector2){(LARGURA_TELA - tamanhoTextovitoria.x) / 2.0f, 80}, tamanhoFontevitoria, espacamento, RAYWHITE);

        char pontuacao[50];
        sprintf(pontuacao, "SCORE: %d", jogador->pontuacao);
        float tamanhoFonteScore = 30;
        float espacamentoScore = 1.0f;
        Vector2 tamanhoTextoScore = MeasureTextEx(fonte_escrita, pontuacao, tamanhoFonteScore, espacamentoScore);
        DrawTextEx(fonte_escrita, pontuacao, (Vector2){(LARGURA_TELA - tamanhoTextoScore.x) / 2.0f, 380}, tamanhoFonteScore, espacamentoScore, WHITE);

        const char *instrucao = "Pressione ESPACO para voltar ao menu";
        float tamanhoFonteInstrucao = 20;
        float espacamentoMsg = 0.7f;
        Vector2 tamanhoTextoMsg = MeasureTextEx(fonte_escrita, instrucao, tamanhoFonteInstrucao, espacamentoMsg);
        DrawTextEx(fonte_escrita, instrucao, (Vector2){(LARGURA_TELA - tamanhoTextoMsg.x) / 2.0f, 480}, tamanhoFonteInstrucao, espacamentoMsg, RED);
        EndDrawing();

        if (IsKeyPressed(KEY_SPACE)) {
            *tela = MENU;
            break;
        }
    }
}
void exibirGameOver(Jogador *jogador, TelaDoJogo *tela, Font fonte_gameover, Font fonte_escrita) {
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        const char *titulo = "GAME OVER";
        float tamanhoFonteTitulo = 50;
        float espacamento = 2.0f;
        Vector2 tamanhoTexto = MeasureTextEx(fonte_gameover, titulo, tamanhoFonteTitulo, espacamento);
        DrawTextEx(fonte_gameover, titulo, (Vector2){(LARGURA_TELA - tamanhoTexto.x) / 2.0f, 300}, tamanhoFonteTitulo, espacamento, RED);

        char pontuacao[50];
        sprintf(pontuacao, "SCORE: %d", jogador->pontuacao);
        float tamanhoFonteScore = 30;
        float espacamentoScore = 1.0f;
        Vector2 tamanhoTextoScore = MeasureTextEx(fonte_escrita, pontuacao, tamanhoFonteScore, espacamentoScore);
        DrawTextEx(fonte_escrita, pontuacao, (Vector2){(LARGURA_TELA - tamanhoTextoScore.x) / 2.0f, 380}, tamanhoFonteScore, espacamentoScore, WHITE);

        const char *instrucao = "Pressione ESPACO para voltar ao menu";
        float tamanhoFonteInstrucao = 20;
        float espacamentoMsg = 0.7f;
        Vector2 tamanhoTextoMsg = MeasureTextEx(fonte_escrita, instrucao, tamanhoFonteInstrucao, espacamentoMsg);
        DrawTextEx(fonte_escrita, instrucao, (Vector2){(LARGURA_TELA - tamanhoTextoMsg.x) / 2.0f, 480}, tamanhoFonteInstrucao, espacamentoMsg, WHITE);

        EndDrawing();

        if (IsKeyPressed(KEY_SPACE)) {
            *tela = MENU;
            break;
        }
    }
}

void TelaCarregamento(int faseAtual)
{
	double inicio = GetTime(); 
	char texto[20];
	
	while(GetTime() - inicio < 1)
	{
		BeginDrawing();
		ClearBackground(BLACK);
	
			sprintf(texto, "NIVEL %d", faseAtual);
   	 		int tamanhoFonte = 50;
            int larguraTexto = MeasureText(texto, tamanhoFonte);
            DrawText(texto, (LARGURA_TELA - larguraTexto) / 2, (ALTURA_TELA - tamanhoFonte) / 2, tamanhoFonte, RAYWHITE);
	
		EndDrawing();
	}
}


void reiniciarJogo(Jogador *jogador, Mapa *mapa, Monstro monstros[], int *qtdMonstros, Espada *espada, Vida vidas[], int *quantidade_vidas, Barra *barra, int faseAtual)
{
    faseAtual = 1;
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

bool todosMonstrosMortos(Monstro monstros[], int qnt){
    for (int i = 0; i < qnt; i++){
        if (monstros[i].ativo){
            return false; 
        }
    }
    return true;
}


int main() {
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Zelda-INF");
    SetTargetFPS(VELOCIDADE_TELA);

    TelaDoJogo tela = MENU;
    int faseAtual = 1;
    int retornoMenu = 0, retornoTelaInfo = 0, retornoTelaScore = 0;
    char nomejogador[21] = "";

    Texture2D sprite = LoadTexture("sprites/espada.png");
    Mapa mapa = carregarMapa(faseAtual);
    Jogador jogador = inicializarJogador(mapa);
    Monstro monstros[10];
    Espada espada = inicializarespada(mapa);
    int qtdMonstros = inicializarMonstros(mapa, monstros);
    float tempoUltimoMovimento = 0.0f;
    float intervaloMovimento = VELOCIDADE_MONSTROS;

    Vida vidas[100];
    int quantidade_vidas = inicializarVida(mapa, vidas);

    Barra barra = {3, 1, 0, false};
    atualizarbarra(&barra);

    Font fonte_gameover = LoadFont("Fontes/GAMEOVER.TTF");
    Font fonte_escrita = LoadFont("Fontes/PressStart2P.ttf");

    while (!WindowShouldClose()) {
        switch(tela) {
            case MENU:
                retornoMenu = exibirMenuPrincipal();
                if (retornoMenu == 1) {
                    retornoTelaInfo = exibirTelaInfo();
                    if (retornoTelaInfo == 4) {
                        reiniciarJogo(&jogador, &mapa, monstros, &qtdMonstros, &espada, vidas, &quantidade_vidas, &barra, faseAtual);
                        tempoUltimoMovimento = 0.0f;
                        TelaCarregamento(1);
                        tela = JOGO;
                    }
                } else if (retornoMenu == 2) {
                        retornoTelaScore = mostrarTop5();
                       if (retornoTelaScore == 1) 
                        tela = MENU;
                } else if (retornoMenu == 3) {
                    CloseWindow();
                    return 0;
                }
                break;

            case GAMEOVER:
                jogador.pontuacao = barra.escore;
                descarregarMonstros(monstros, qtdMonstros);
                descarregarVidas(vidas, quantidade_vidas);
                descarregarJogador(&jogador);
                descarregarEspada(&espada);
                exibirGameOver(&jogador, &tela, fonte_gameover, fonte_escrita);
                faseAtual = 1;
                break;

            case JOGO:
                BeginDrawing();
                ClearBackground(BLACK);

                desenharMapa(mapa);
                desenharbarra(barra);
                atualizarbarra(&barra);
                atualizarJogador(&jogador, mapa, monstros, qtdMonstros, &barra);

                desenharespada(espada);
                atualizarespada(&espada, &jogador, &barra);

                int monstrosMortos = ataqueEspada(&espada, &jogador, &mapa, qtdMonstros, monstros);
                atualizarscore(&barra, monstrosMortos);

                atualizarvida(&jogador, vidas, &barra, quantidade_vidas);
                desenharVida(vidas, quantidade_vidas);

                float tempoAtual = GetTime();
                if (tempoAtual - tempoUltimoMovimento >= intervaloMovimento) {
                    moverMonstros(monstros, qtdMonstros, mapa, &jogador, &barra);
                    tempoUltimoMovimento = tempoAtual;
                }

                desenharJogador(jogador);
                desenharMonstros(monstros, qtdMonstros);

                if (IsKeyPressed(KEY_TAB)) {
                    retornoMenu = exibirMenuJogo();
                    if (retornoMenu == 6) {
                        descarregarMonstros(monstros, qtdMonstros);
                        descarregarVidas(vidas, quantidade_vidas);
                        descarregarJogador(&jogador);
                        descarregarEspada(&espada);
                        faseAtual = 1;
                        tela = MENU;
                    }
                    else if (retornoMenu == 7) {
                        descarregarMonstros(monstros, qtdMonstros);
                        descarregarVidas(vidas, quantidade_vidas);
                        descarregarJogador(&jogador);
                        descarregarEspada(&espada);
                        faseAtual = 1;
                        CloseWindow();
                    }
                }

                if (todosMonstrosMortos(monstros, qtdMonstros)) {

                        faseAtual++;

                    if (faseAtual == 11) {
                        strcpy(nomejogador, pedirnomejogador());
                        jogador.pontuacao = barra.escore;
                        salvarScore(nomejogador, jogador.pontuacao);
                        exibirvitoria(&jogador, &tela, fonte_gameover, fonte_escrita, nomejogador);
                        descarregarMonstros(monstros, qtdMonstros);
                        descarregarVidas(vidas, quantidade_vidas);
                        descarregarJogador(&jogador);
                        descarregarEspada(&espada);
                        faseAtual = 1;
                        break;
                    }

                    BeginDrawing();
                    ClearBackground(BLACK);
                        TelaCarregamento(faseAtual);
                    EndDrawing();

                    descarregarTexturasMapa(&mapa);
                    descarregarJogador(&jogador);
                    descarregarEspada(&espada);
                    descarregarVidas(vidas, quantidade_vidas);
                    descarregarMonstros(monstros, qtdMonstros);

                    mapa = carregarMapa(faseAtual);
                    int vidas_restantes = jogador.vidas;
                    int score_atual = jogador.pontuacao;

                    jogador = inicializarJogador(mapa);
                    jogador.vidas = vidas_restantes;
                    jogador.pontuacao = score_atual;

                    espada = inicializarespada(mapa);
                    qtdMonstros = inicializarMonstros(mapa, monstros);
                    quantidade_vidas = inicializarVida(mapa, vidas);
                    barra.espada = false;
                    barra.nivel = faseAtual;
                    atualizarbarra(&barra);
                }

                if (jogador.vidas <= 0) {
                    jogador.pontuacao = barra.escore;
                    tela = GAMEOVER;
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
    UnloadFont(fonte_escrita);
    CloseWindow();

    return 0;
}

    

// Fim do código principal
