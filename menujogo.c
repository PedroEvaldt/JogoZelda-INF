#include "raylib.h"
#include "menujogo.h"
#include "menuprincipal.h"
#include <stdbool.h>

int exibirMenuJogo()
{
    Color CorBotao = GRAY;
    Color CorMouseBotao = WHITE;
    Color CorBotaoPressionado = DARKGRAY;

    Rectangle Botao = {LARGURA_TELA / 2 - 100, 400, 200, 60};

    bool BotaoPressionado = false;

    while (!WindowShouldClose()) 
    {
        Vector2 posicaomouse = GetMousePosition();

        if (CheckCollisionPointRec(posicaomouse, Botao))
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                CorBotao = CorBotaoPressionado; 
                BotaoPressionado = true;
            }
            else
            {
                CorBotao = CorMouseBotao;
                if (BotaoPressionado && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) 
                    return 5;
                BotaoPressionado = false; 
            }
        }
        else
        {
            CorBotao = GRAY;
            BotaoPressionado = false;
        }

        BeginDrawing();
            ClearBackground(BLACK);

            DrawText("MENU", 520, 50, 60, RAYWHITE);
            DrawRectangleRec(Botao, CorBotao);
            DrawText("SAIR DO JOGO",513,420,25,BLACK);

        EndDrawing();

        if (IsKeyPressed(KEY_TAB))
            break;
    }
}
