#include "raylib.h"
#include "menujogo.h"
#include <stdbool.h>

void exibirMenuJogo()
{
    Color CorBotao = BROWN;
    Color CorMouseBotao = WHITE;
    Color CorBotaoPressionado = DARKBROWN;

    Rectangle Botao = {LARGURA_TELA / 2 - 60, ALTURA_TELA / 2 - 20, 120, 40};

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
                    break;
                BotaoPressionado = false; 
            }
        }
        else
        {
            CorBotao = BROWN; 
            BotaoPressionado = false;
        }

        BeginDrawing();
            ClearBackground(BLACK);

            DrawText("MENU", 520, 50, 60, RAYWHITE);
            DrawRectangleRec(Botao, CorBotao);
            DrawText("SAIR",575,420,20,BLACK);

        EndDrawing();

        if (IsKeyPressed(KEY_TAB))
            break;
    }
}
