// Inclusão das bibliotecas necessárias para o funcionamento do jogo
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

// Enumeração para controlar as telas do jogo
typedef enum {MENU, SCORE, JOGO, GAMEOVER} TelaDoJogo;

// Definições de constantes do jogo
#define VELOCIDADE_MONSTROS 0.5
#define LARGURA_TELA 1200
#define ALTURA_TELA 860
#define VELOCIDADE_TELA 200 // Frames por segundo

// ---------------- Funções utilitárias ----------------

// Libera da memória as texturas usadas pelo jogador
void descarregarJogador(Jogador *j) {
    UnloadTexture(j->jogador_norte);
    UnloadTexture(j->jogador_sul);
    UnloadTexture(j->jogador_leste);
    UnloadTexture(j->jogador_oeste);
}

// Libera a textura usada pela espada
void descarregarEspada(Espada *e) {
    UnloadTexture(e->espada_textura);
}

// Libera as texturas de todas as vidas
void descarregarVidas(Vida vidas[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        UnloadTexture(vidas[i].vida_textura);
    }
}

// Libera as texturas de todos os monstros
void descarregarMonstros(Monstro monstros[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        UnloadTexture(monstros[i].monstro);
        UnloadTexture(monstros[i].monstro_norte);
        UnloadTexture(monstros[i].monstro_sul);
        UnloadTexture(monstros[i].monstro_leste);
        UnloadTexture(monstros[i].monstro_oeste);
    }
}

// Exibe a tela de vitória com a pontuação do jogador
void exibirvitoria(Jogador *jogador, TelaDoJogo *tela, Font fonte_vitoria, Font fonte_escrita, char *nomejogador) {
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Mensagem de vitória personalizada
        char vitoria[100];
        sprintf(vitoria, "Parabens %s, voce venceu!", nomejogador);

        // Texto centralizado - Título de vitória
        float tamFonteVitoria = 36;
        float espacoVitoria = 1.0f;
        Vector2 tamTextoVitoria = MeasureTextEx(fonte_vitoria, vitoria, tamFonteVitoria, espacoVitoria);
        DrawTextEx(fonte_vitoria, vitoria,
                   (Vector2){(LARGURA_TELA - tamTextoVitoria.x) / 2.0f, 100},
                   tamFonteVitoria, espacoVitoria, DARKGREEN);

        // Pontuação final
        char pontuacao[50];
        sprintf(pontuacao, "SCORE: %d", jogador->pontuacao);

        float tamFonteScore = 30;
        float espacoScore = 1.0f;
        Vector2 tamTextoScore = MeasureTextEx(fonte_escrita, pontuacao, tamFonteScore, espacoScore);
        DrawTextEx(fonte_escrita, pontuacao,
                   (Vector2){(LARGURA_TELA - tamTextoScore.x) / 2.0f, 220},
                   tamFonteScore, espacoScore, WHITE);

        // Instrução para voltar ao menu
        const char *instrucao = "Pressione ESPACO para voltar ao menu";
        float tamFonteInstrucao = 20;
        float espacoInstrucao = 0.7f;
        Vector2 tamTextoInstrucao = MeasureTextEx(fonte_escrita, instrucao, tamFonteInstrucao, espacoInstrucao);
        DrawTextEx(fonte_escrita, instrucao,
                   (Vector2){(LARGURA_TELA - tamTextoInstrucao.x) / 2.0f, 320},
                   tamFonteInstrucao, espacoInstrucao, RED);

        EndDrawing();

        // Volta ao menu se espaço for pressionado
        if (IsKeyPressed(KEY_SPACE)) {
            *tela = MENU;
            break;
        }
    }
}


// Reinicia os dados do jogo para começar uma nova partida
void reiniciarJogo(Jogador *jogador, Mapa *mapa, Monstro monstros[], int *qtdMonstros, Espada *espada, Vida vidas[], int *quantidade_vidas, Barra *barra, int *faseAtual)
{
    *faseAtual = 1; // Reinicia a fase
    *mapa = carregarMapa(*faseAtual); 
    *jogador = inicializarJogador(*mapa); 
    *qtdMonstros = inicializarMonstros(*mapa,monstros);
    *espada = inicializarespada(*mapa);
    *quantidade_vidas = inicializarVida(*mapa, vidas);

    // Reseta a barra de status
    barra->vidas = 3; 
    barra->nivel = 1; 
    barra->escore = 0;
    barra->espada = false; 
    atualizarbarra(barra);
}

// Exibe tela de carregamento temporária entre as fases
void TelaCarregamento(int faseAtual)
{
    double inicio = GetTime(); 
    char texto[20];
    
    while(GetTime() - inicio < 1) // Aguarda 1 segundo
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Mostra o nível atual
        sprintf(texto, "NIVEL %d", faseAtual);
        int tamanhoFonte = 50;
        int larguraTexto = MeasureText(texto, tamanhoFonte);
        DrawText(texto, (LARGURA_TELA - larguraTexto) / 2, (ALTURA_TELA - tamanhoFonte) / 2, tamanhoFonte, DARKGREEN);

        EndDrawing();
    }
}

// Exibe a tela de Game Over com pontuação e opções de retorno/reinício
void exibirGameOver(Jogador *jogador, TelaDoJogo *tela, Font fonte_gameover, Font fonte_escrita, Mapa *mapa, Monstro monstros[], int *qtdMonstros, Espada *espada, Vida vidas[], int *quantidade_vidas, Barra *barra, int *faseAtual) {
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(BLACK);

        // Texto "GAME OVER" centralizado
        const char *titulo = "GAME OVER";
        float tamanhoFonteTitulo = 50;
        float espacamento = 2.0f;
        Vector2 tamanhoTexto = MeasureTextEx(fonte_gameover, titulo, tamanhoFonteTitulo, espacamento);
        DrawTextEx(fonte_gameover, titulo, (Vector2){(LARGURA_TELA - tamanhoTexto.x) / 2.0f, 300}, tamanhoFonteTitulo, espacamento, RED);

        // Pontuação final do jogador
        char pontuacao[50];
        sprintf(pontuacao, "SCORE: %d", jogador->pontuacao);
        float tamanhoFonteScore = 30;
        float espacamentoScore = 1.0f;
        Vector2 tamanhoTextoScore = MeasureTextEx(fonte_escrita, pontuacao, tamanhoFonteScore, espacamentoScore);
        DrawTextEx(fonte_escrita, pontuacao, (Vector2){(LARGURA_TELA - tamanhoTextoScore.x) / 2.0f, 380}, tamanhoFonteScore, espacamentoScore, WHITE);

        // Instrução para voltar ao menu
        const char *instrucaoMenu = "Pressione ESPACO para voltar ao menu";
        float tamanhoFonteInstrucaoMenu = 20;
        float espacamentoMsg = 0.7f;
        Vector2 tamanhoTextoMsg = MeasureTextEx(fonte_escrita, instrucaoMenu, tamanhoFonteInstrucaoMenu, espacamentoMsg);
        DrawTextEx(fonte_escrita, instrucaoMenu, (Vector2){(LARGURA_TELA - tamanhoTextoMsg.x) / 2.0f, 480}, tamanhoFonteInstrucaoMenu, espacamentoMsg, WHITE);

        // Instrução para reiniciar o jogo diretamente
        const char *instrucaoReiniciar = "Pressione R para reiniciar o jogo";
        float tamanhoFonteReiniciar = 20;
        float espacamentoReiniciar = 0.7f;
        Vector2 tamanhoTextoReiniciar = MeasureTextEx(fonte_escrita, instrucaoReiniciar, tamanhoFonteReiniciar, espacamentoReiniciar);
        DrawTextEx(fonte_escrita, instrucaoReiniciar, (Vector2){(LARGURA_TELA - tamanhoTextoReiniciar.x) / 2.0f, 580}, tamanhoFonteReiniciar, espacamentoReiniciar, WHITE);

        EndDrawing();

        // Volta ao menu
        if (IsKeyPressed(KEY_SPACE)) {
            *tela = MENU;
            break;
        }

        // Reinicia o jogo
        if(IsKeyPressed(KEY_R)){
            reiniciarJogo(jogador, mapa, monstros, qtdMonstros, espada, vidas, quantidade_vidas, barra, faseAtual);
            TelaCarregamento(*faseAtual);
            *tela = JOGO;
            break;
        }
    }
}

// Verifica se todos os monstros estão mortos
bool todosMonstrosMortos(Monstro monstros[], int qnt){
    for (int i = 0; i < qnt; i++){
        if (monstros[i].ativo){
            return false; // Ainda há monstros vivos
        }
    }
    return true; // Todos foram derrotados
}

// --------------------- FUNÇÃO PRINCIPAL ---------------------
int main() {
    InitWindow(LARGURA_TELA, ALTURA_TELA, "Zelda-INF");  // Cria a janela do jogo
    SetTargetFPS(VELOCIDADE_TELA);                       // Define o FPS alvo

    TelaDoJogo tela = MENU;   // Começa na tela de menu
    int faseAtual = 1;        // Começa na fase 1
    int retornoMenu = 0, retornoTelaInfo = 0, retornoTelaScore = 0;
    char nomejogador[21] = "";  // Armazena nome do jogador

    // Carrega sprite da espada (não usado diretamente aqui)
    Texture2D sprite = LoadTexture("sprites/espada.png");

    // Inicializa estruturas principais do jogo
    Mapa mapa = carregarMapa(faseAtual);
    Jogador jogador = inicializarJogador(mapa);
    Monstro monstros[10];
    Espada espada = inicializarespada(mapa);
    int qtdMonstros = inicializarMonstros(mapa, monstros);
    float tempoUltimoMovimento = 0.0f;
    float intervaloMovimento = VELOCIDADE_MONSTROS;

    // Inicializa vidas espalhadas no mapa
    Vida vidas[100];
    int quantidade_vidas = inicializarVida(mapa, vidas);

    // Inicializa barra de status
    Barra barra = {3, 1, 0, false};
    atualizarbarra(&barra);

    // Carrega fontes personalizadas para escrita e game over
    Font fonte_gameover = LoadFont("Fontes/GAMEOVER.TTF");
    Font fonte_escrita = LoadFont("Fontes/PressStart2P.ttf");

    while (!WindowShouldClose()) {
        // Switch define o comportamento com base na tela atual
        switch(tela) {

            // -------------------- MENU PRINCIPAL --------------------
            case MENU:
                retornoMenu = exibirMenuPrincipal();

                if (retornoMenu == 1) {
                    // Vai para a tela de instruções
                    retornoTelaInfo = exibirTelaInfo();
                    if (retornoTelaInfo == 4) {
                        // Inicia o jogo após o tutorial
                        reiniciarJogo(&jogador, &mapa, monstros, &qtdMonstros, &espada, vidas, &quantidade_vidas, &barra, &faseAtual);
                        tempoUltimoMovimento = 0.0f;
                        TelaCarregamento(faseAtual);
                        tela = JOGO;
                    }

                } else if (retornoMenu == 2) {
                    // Vai para a tela de scores
                    tela = SCORE;

                } else if (retornoMenu == 3) {
                    // Sai do jogo
                    CloseWindow();
                    return 0;
                }
                break;

            // -------------------- TELA DE SCORE --------------------
            case SCORE:
                mostrarTop5();  // Exibe os 5 melhores
                tela = MENU;    // Retorna ao menu
                break;

            // -------------------- GAME OVER --------------------
            case GAMEOVER:
                jogador.pontuacao = barra.escore;

                // Descarrega dados antigos
                descarregarMonstros(monstros, qtdMonstros);
                descarregarVidas(vidas, quantidade_vidas);
                descarregarJogador(&jogador);
                descarregarEspada(&espada);

                // Exibe tela de Game Over
                exibirGameOver(&jogador, &tela, fonte_gameover, fonte_escrita, &mapa, monstros, &qtdMonstros, &espada, vidas, &quantidade_vidas, &barra, &faseAtual);

                faseAtual = 1;
                break;

                case JOGO:
                BeginDrawing();
                ClearBackground(BLACK); // Limpa a tela com fundo preto

                // Desenha o mapa, a barra de status e atualiza seu conteúdo
                desenharMapa(mapa);
                desenharbarra(barra);
                atualizarbarra(&barra);

                // Atualiza a posição e estado do jogador (movimento e direção)
                atualizarJogador(&jogador, mapa, monstros, qtdMonstros, &barra);

                // Desenha e atualiza a espada (visualmente e internamente)
                desenharespada(espada);
                atualizarespada(&espada, &jogador, &barra);

                // Detecta ataques com a espada e atualiza score com base nos monstros mortos
                int monstrosMortos = ataqueEspada(&espada, &jogador, &mapa, qtdMonstros, monstros);
                atualizarscore(&barra, monstrosMortos);

                // Atualiza interações com as vidas e as desenha
                atualizarvida(&jogador, vidas, &barra, quantidade_vidas);
                desenharVida(vidas, quantidade_vidas);

                // Move os monstros com base no tempo decorrido
                float tempoAtual = GetTime();
                if (tempoAtual - tempoUltimoMovimento >= intervaloMovimento) {
                    moverMonstros(monstros, qtdMonstros, mapa, &jogador, &barra);
                    tempoUltimoMovimento = tempoAtual;
                }

                // Desenha o jogador e os monstros na tela
                desenharJogador(jogador);
                desenharMonstros(monstros, qtdMonstros);

                // --------------------- MENU IN-GAME ---------------------
                if (IsKeyPressed(KEY_TAB)) {
                    retornoMenu = exibirMenuJogo();

                    if (retornoMenu == 6) {
                        // Voltar ao menu e salvar score se for novo recorde
                        jogador.pontuacao = barra.escore;
                        if(NovoRecorde(jogador.pontuacao)){
                            strcpy(nomejogador, pedirnomejogador());
                            salvarScore(nomejogador, jogador.pontuacao);
                        }

                        // Limpa todos os dados carregados
                        descarregarMonstros(monstros, qtdMonstros);
                        descarregarVidas(vidas, quantidade_vidas);
                        descarregarJogador(&jogador);
                        descarregarEspada(&espada);

                        faseAtual = 1;
                        tela = MENU;
                    }
                    else if (retornoMenu == 7) {
                        // Fecha o jogo diretamente
                        descarregarMonstros(monstros, qtdMonstros);
                        descarregarVidas(vidas, quantidade_vidas);
                        descarregarJogador(&jogador);
                        descarregarEspada(&espada);

                        faseAtual = 1;
                        CloseWindow();
                    }
                }

                // --------------------- PASSAGEM DE FASE ---------------------
                if (todosMonstrosMortos(monstros, qtdMonstros)) {
                    if (faseAtual > 10) { // Condição de vitória final
                        jogador.pontuacao = barra.escore;
                        if (NovoRecorde(jogador.pontuacao)){
                            strcpy(nomejogador, pedirnomejogador());
                            salvarScore(nomejogador, jogador.pontuacao);
                        }

                        // Tela de vitória e descarregamento de dados
                        exibirvitoria(&jogador, &tela, fonte_gameover, fonte_escrita, nomejogador);
                        descarregarMonstros(monstros, qtdMonstros);
                        descarregarJogador(&jogador);
                        descarregarEspada(&espada);
                        faseAtual = 1;
                        break;
                    }

                    // Avança para próxima fase
                    faseAtual++;
                    if(faseAtual != 11)
                        TelaCarregamento(faseAtual);

                    // Reinicializa tudo para a próxima fase
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

                // --------------------- GAME OVER ---------------------
                if (jogador.vidas <= 0) {
                    jogador.pontuacao = barra.escore;
                    if (NovoRecorde(jogador.pontuacao)){
                        strcpy(nomejogador, pedirnomejogador());
                        salvarScore(nomejogador, jogador.pontuacao);
                    }
                    tela = GAMEOVER;
                }

                EndDrawing();
                break;
        } // fim do switch
    } // fim do while

 // Libera recursos carregados antes de sair do programa
 descarregarTexturasMapa(&mapa);       // Libera texturas do mapa
 descarregarJogador(&jogador);         // Libera sprites do jogador
 descarregarEspada(&espada);           // Libera sprite da espada
 descarregarVidas(vidas, quantidade_vidas); // Libera texturas das vidas
 descarregarMonstros(monstros, qtdMonstros); // Libera sprites dos monstros

 UnloadTexture(sprite);        // Libera sprite carregado diretamente
 UnloadFont(fonte_gameover);   // Libera fonte de game over
 UnloadFont(fonte_escrita);    // Libera fonte do jogo

 CloseWindow();  // Fecha a janela do Raylib e encerra o jogo

 return 0;       // Finalização do programa com sucesso
}
