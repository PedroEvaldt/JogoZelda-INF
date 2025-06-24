#include "raylib.h"
#include "menujogo.h"

// Função que exibe o menu durante o jogo (pausado)
int exibirMenuJogo()
{
    // Cores usadas nos botões
    Color CorBotao = GRAY;
    Color CorMouseBotao = WHITE;
    Color CorBotaoPressionado = DARKGRAY;

    // Define os botões: CONTINUAR, VOLTAR AO MENU, SAIR
    Rectangle BotaoJogo = {LARGURA_TELA / 2 - 150, 300, 300, 60};
    Rectangle BotaoVoltar = {LARGURA_TELA / 2 - 150, 450, 300, 60};
    Rectangle BotaoSair = {LARGURA_TELA / 2 - 150, 600, 300, 60};   

    // Flags que registram se os botões foram pressionados
    bool BotaoJogoPressionado = false;
    bool BotaoVoltarPressionado = false;
    bool BotaoSairPressionado = false;

    while (!WindowShouldClose()) {

        // -------------------- ATALHOS POR TECLADO --------------------

        // C = Continuar o jogo
        if(IsKeyPressed(KEY_C))
            return 5;

        // V = Voltar ao menu
        if(IsKeyPressed(KEY_V))
            return 6;

        // S = Sair do jogo
        if(IsKeyPressed(KEY_S))
            return 7;

        // -------------------- INTERAÇÃO COM O MOUSE --------------------

        Vector2 posicaomouse = GetMousePosition();

        // ---------- BOTÃO CONTINUAR ----------
        Color CorBotaoJogo = CorBotao;
        if (CheckCollisionPointRec(posicaomouse, BotaoJogo)) {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                CorBotaoJogo = CorBotaoPressionado;
                BotaoJogoPressionado = true;
            } else {
                CorBotaoJogo = CorMouseBotao;
                if (BotaoJogoPressionado && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    return 5; // Continuar o jogo
                BotaoJogoPressionado = false;
            }
        } else {
            CorBotaoJogo = GRAY;
            BotaoJogoPressionado = false;
        }

        // ---------- BOTÃO VOLTAR AO MENU ----------
        Color CorBotaoVoltar = CorBotao;
        if (CheckCollisionPointRec(posicaomouse, BotaoVoltar)) {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                CorBotaoVoltar = CorBotaoPressionado;
                BotaoVoltarPressionado = true;
            } else {
                CorBotaoVoltar = CorMouseBotao;
                if (BotaoVoltarPressionado && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    return 6; // Voltar ao menu principal
                BotaoVoltarPressionado = false;
            }
        } else {
            CorBotaoVoltar = GRAY;
            BotaoVoltarPressionado = false;
        }

        // ---------- BOTÃO SAIR DO JOGO ----------
        Color CorBotaoSair = CorBotao;
        if (CheckCollisionPointRec(posicaomouse, BotaoSair)) {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                CorBotaoSair = CorBotaoPressionado;
                BotaoSairPressionado = true;
            } else {
                CorBotaoSair = CorMouseBotao;
                if (BotaoSairPressionado && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    return 7; // Encerrar o jogo
                BotaoSairPressionado = false;
            }
        } else {
            CorBotaoSair = GRAY;
            BotaoSairPressionado = false;
        }

        // -------------------- DESENHO DO MENU --------------------
        BeginDrawing();
            ClearBackground(BLACK); // Fundo preto

            // Título "MENU"
            int tamanho_menu = MeasureText("MENU", 60);
            DrawText("MENU", (LARGURA_TELA - tamanho_menu) / 2, 50, 60, DARKGREEN);

            // Botão CONTINUAR
            DrawRectangleRec(BotaoJogo, CorBotaoJogo);
            int tamanho_continuar = MeasureText("CONTINUAR", 24);
            DrawText("CONTINUAR", (LARGURA_TELA - tamanho_continuar) / 2 , 320, 24, BLACK);

            // Botão VOLTAR AO MENU
            DrawRectangleRec(BotaoVoltar, CorBotaoVoltar);
            int tamanho_voltaraomenu = MeasureText("VOLTAR AO MENU", 24);
            DrawText("VOLTAR AO MENU", (LARGURA_TELA - tamanho_voltaraomenu) / 2, 470, 24, BLACK);

            // Botão SAIR
            DrawRectangleRec(BotaoSair, CorBotaoSair);
            int tamanho_sair = MeasureText("SAIR", 24);
            DrawText("SAIR", (LARGURA_TELA - tamanho_sair) / 2 , 620, 24, BLACK);
        EndDrawing();

        // Pressionar TAB fecha o menu sem ação
        if (IsKeyPressed(KEY_TAB))
            break;
    }
}