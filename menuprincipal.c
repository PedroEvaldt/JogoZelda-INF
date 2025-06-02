#include "menuprincipal.h"

int exibirMenuPrincipal(){
    Color CorBotao = GRAY;
    Color CorMouseBotao = WHITE;
    Color CorBotaoPressionado = DARKGRAY;

    Rectangle BotaoIniciar = {LARGURA_TELA / 2 - 100, 300, 200, 60};
    Rectangle BotaoScore = {LARGURA_TELA / 2 - 100, 450, 200, 60};
    Rectangle BotaoSair = {LARGURA_TELA / 2 - 100, 600, 200, 60};

    bool BotaoIniciarPressionado = false;
    bool BotaoScorePressionado = false;
    bool BotaoSairPressionado = false;

    Texture2D jogador = LoadTexture("sprites/jogador-sul.png");
    Texture2D monstro = LoadTexture("sprites/monstro-sul.png");

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

            Vector2 posicaoJ = {180,290};
            Vector2 posicaoM = {870,300};
            DrawTextureEx(jogador,posicaoJ,0,0.5,WHITE);
            DrawTextureEx(monstro,posicaoM,0,0.55,WHITE);
            DrawText("MENU PRINCIPAL", 342, 50, 60, RAYWHITE);
            DrawRectangleRec(BotaoIniciar, CorBotaoIniciar);
            DrawText("INICIAR",552,320,25,BLACK);
            DrawRectangleRec(BotaoScore, CorBotaoScore);
            DrawText("SCOREBOARD",520,470,25,BLACK);
            DrawRectangleRec(BotaoSair, CorBotaoSair);
            DrawText("SAIR",570,620,25,BLACK);

        EndDrawing();
    }
}

int exibirTelaInfo()
{   
    while(!WindowShouldClose()){

    BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Sobre o jogo:", 470, 80, 35, RAYWHITE);
        DrawText("Tecla TAB: Pausa o jogo e abre/fecha o menu do jogo", 100, 300, 20, RAYWHITE);
        DrawText("Teclas W/A/S/D e as setas: Move o jogador uma posição na direção indicada", 100, 400, 20, RAYWHITE);
        DrawText("Tecla J: Ativa a espada", 100, 500, 20, RAYWHITE);
        DrawText("Pressione SPACE para iniciar o jogo", 350, 650, 25, RED);

    EndDrawing();

    if(IsKeyPressed(KEY_SPACE))
             return 4;        
    }
}