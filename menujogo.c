#include "raylib.h"
#include "menujogo.h"

int exibirMenuJogo()
{
    Color CorBotao = GRAY;
    Color CorMouseBotao = WHITE;
    Color CorBotaoPressionado = DARKGRAY;

    Rectangle BotaoJogo = {LARGURA_TELA / 2 - 150, 300, 300, 60};
    Rectangle BotaoVoltar = {LARGURA_TELA / 2 - 150, 450, 300, 60};
    Rectangle BotaoSair = {LARGURA_TELA / 2 - 150, 600, 300, 60};   

    bool BotaoJogoPressionado = false;
    bool BotaoVoltarPressionado = false;
    bool BotaoSairPressionado = false;

    while (!WindowShouldClose())
    {

        //Uso das teclas
        if(IsKeyPressed(KEY_C))
            return 5;
        if(IsKeyPressed(KEY_V))
            return 6;
        if(IsKeyPressed(KEY_S))
            return 7;

        //Uso dos botões
        Vector2 posicaomouse = GetMousePosition();

        //Botão VOLTAR
        Color CorBotaoJogo = CorBotao;
        if (CheckCollisionPointRec(posicaomouse, BotaoJogo))
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                CorBotaoJogo = CorBotaoPressionado; 
                BotaoJogoPressionado = true;
            }
            else
            {
                CorBotaoJogo = CorMouseBotao;
                 if (BotaoJogoPressionado && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    return 5;
                BotaoJogoPressionado = false; 
            }
        }
        else
        {
            CorBotaoJogo = GRAY; 
            BotaoJogoPressionado = false;
        }
        //Botão VOLTAR
        Color CorBotaoVoltar = CorBotao;
        if (CheckCollisionPointRec(posicaomouse, BotaoVoltar))
        {
            if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            {
                CorBotaoVoltar = CorBotaoPressionado; 
                BotaoVoltarPressionado = true;
            }
            else
            {
                CorBotaoVoltar = CorMouseBotao;
                 if (BotaoVoltarPressionado && IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
                    return 6;
                BotaoVoltarPressionado = false; 
            }
        }
        else
        {
            CorBotaoVoltar = GRAY; 
            BotaoVoltarPressionado = false;
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
                    return 7;
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

            int tamanho_menu = MeasureText("MENU", 60);
            DrawText("MENU", (LARGURA_TELA - tamanho_menu) / 2, 50, 60, RAYWHITE);
            DrawRectangleRec(BotaoJogo, CorBotaoJogo);
            int tamanho_continuar = MeasureText("CONTINUAR", 24);
            DrawText("CONTINUAR",(LARGURA_TELA - tamanho_continuar) / 2 ,320,24,BLACK);
            DrawRectangleRec(BotaoVoltar, CorBotaoVoltar);
            int tamanho_voltaraomenu = MeasureText("VOLTAR AO MENU", 24);
            DrawText("VOLTAR AO MENU",(LARGURA_TELA - tamanho_voltaraomenu) / 2,470,24,BLACK);
            DrawRectangleRec(BotaoSair, CorBotaoSair);
            int tamanho_sair = MeasureText("SAIR", 24);
            DrawText("SAIR",(LARGURA_TELA - tamanho_sair) / 2 ,620,24,BLACK);

        EndDrawing();

        if (IsKeyPressed(KEY_TAB))
            break;
    }
}
