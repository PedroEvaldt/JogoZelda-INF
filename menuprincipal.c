#include "raylib.h"
#include "menuprincipal.h"
#include <stdbool.h>
#define LARGURA_TELA 1200 
#define ALTURA_TELA 860

int exibirMenuPrincipal()
{
    Color CorBotao = GRAY;
    Color CorMouseBotao = WHITE;
    Color CorBotaoPressionado = DARKGRAY;

    Rectangle BotaoIniciar = {LARGURA_TELA / 2 - 100, 300, 200, 60};
    Rectangle BotaoScore = {LARGURA_TELA / 2 - 100, 450, 200, 60};
    Rectangle BotaoSair = {LARGURA_TELA / 2 - 100, 600, 200, 60};

    bool BotaoIniciarPressionado = false;
    bool BotaoScorePressionado = false;
    bool BotaoSairPressionado = false;

    while (!WindowShouldClose())
    {
        Vector2 posicaomouse = GetMousePosition();

        //Botão INICIAR
        Color CorBotaoIniciar = CorBotao;
        if (CheckCollisionPointRec(posicaomouse, BotaoIniciar))
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                CorBotaoIniciar = CorBotaoPressionado; 
                BotaoIniciarPressionado = true;
            }
            else
            {
                CorBotaoIniciar = CorMouseBotao;
                if (BotaoIniciarPressionado && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) 
                    return 1;
                BotaoIniciarPressionado = false; 
            }
        }
        else
        {
            CorBotaoIniciar = GRAY; 
            BotaoIniciarPressionado = false;
        }
        //Botão SCOREBOARD
        Color CorBotaoScore = CorBotao;
        if (CheckCollisionPointRec(posicaomouse, BotaoScore))
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                CorBotaoScore = CorBotaoPressionado; 
                BotaoScorePressionado = true;
            }
            else
            {
                CorBotaoScore = CorMouseBotao;
                if (BotaoScorePressionado && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) 
                    return 2;
                BotaoScorePressionado = false; 
            }
        }
        else
        {
            CorBotaoScore = GRAY; 
            BotaoScorePressionado = false;
        }
        //Botão SAIR
        Color CorBotaoSair = CorBotao;
        if (CheckCollisionPointRec(posicaomouse, BotaoSair))
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                CorBotaoSair = CorBotaoPressionado; 
                BotaoSairPressionado = true;
            }
            else
            {
                CorBotaoSair = CorMouseBotao;
                if (BotaoSairPressionado && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) 
                    return 3;
                BotaoSairPressionado = false; 
            }
        }
        else
        {
            CorBotaoSair = GRAY; 
            BotaoSairPressionado = false;
        }
        
        BeginDrawing();
            ClearBackground(BLACK);

            DrawText("MENU PRINCIPAL", 350, 50, 60, RAYWHITE);
            DrawRectangleRec(BotaoIniciar, CorBotaoIniciar);
            DrawText("INICIAR",552,320,25,BLACK);
            DrawRectangleRec(BotaoScore, CorBotaoScore);
            DrawText("SCOREBOARD",520,470,25,BLACK);
            DrawRectangleRec(BotaoSair, CorBotaoSair);
            DrawText("SAIR",570,620,25,BLACK);

        EndDrawing();
    }
}