#include "raylib.h"
#include "menuprincipal.h"

int exibirMenuPrincipal()
{   
    Font fonte_escrita = LoadFont("Fontes/PressStart2P.ttf");
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
            const char *menu_principal = "MENU PRINCIPAL";
            float tamanhoFonteMENUPRINCIPAL = 30;
            float espacamento = 0.7f;
            Vector2 tamanhoTextomenu = MeasureTextEx(fonte_escrita, menu_principal, tamanhoFonteMENUPRINCIPAL, espacamento);
            DrawTextEx(fonte_escrita, menu_principal, (Vector2){(LARGURA_TELA - tamanhoTextomenu.x) / 2.0f, 50}, tamanhoFonteMENUPRINCIPAL, espacamento, WHITE);
            DrawRectangleRec(BotaoIniciar, CorBotaoIniciar);
            const char *iniciar = "INICIAR";
            float tamanhoFonteiniciar = 15;
            Vector2 tamanhoTextoiniciar = MeasureTextEx(fonte_escrita, iniciar, tamanhoFonteiniciar, espacamento);
            DrawTextEx(fonte_escrita, iniciar, (Vector2){(LARGURA_TELA - tamanhoTextoiniciar.x) / 2.0f, 325}, tamanhoFonteiniciar, espacamento, BLACK);
            DrawRectangleRec(BotaoScore, CorBotaoScore);
            const char *scoreboard = "SCOREBOARD";
            float tamanhoFontescoreboard = 15;
            Vector2 tamanhoTextoscrboard = MeasureTextEx(fonte_escrita, scoreboard, tamanhoFontescoreboard, espacamento);
            DrawTextEx(fonte_escrita, scoreboard, (Vector2){(LARGURA_TELA - tamanhoTextoscrboard.x) / 2.0f, 475}, tamanhoFontescoreboard, espacamento, BLACK);
            DrawRectangleRec(BotaoSair, CorBotaoSair);
            const char *sair = "SAIR";
            float tamanhoFontesair = 15;
            Vector2 tamanhoTextosair = MeasureTextEx(fonte_escrita, sair, tamanhoFontesair, espacamento);
            DrawTextEx(fonte_escrita, sair, (Vector2){(LARGURA_TELA - tamanhoTextosair.x) / 2.0f, 625}, tamanhoFontesair, espacamento, BLACK);

        EndDrawing();
    }
}

int exibirTelaInfo()
{   
    Font fonte_escrita = LoadFont("Fontes/PressStart2P.ttf");
    float espacamento = 0.7f;
    while(!WindowShouldClose()){

    BeginDrawing();
        ClearBackground(BLACK);
        const char *sobre = "Sobre o jogo:";
        float tamanhoFontesobre = 30;
        Vector2 tamanhoTextofonte = MeasureTextEx(fonte_escrita, sobre, tamanhoFontesobre, espacamento);
        DrawTextEx(fonte_escrita, sobre, (Vector2){(LARGURA_TELA - tamanhoTextofonte.x) / 2.0f, 80}, tamanhoFontesobre, espacamento, RAYWHITE);
    

        const char *tab = "Tecla TAB: Pausa o jogo e abre/fecha o menu do jogo";
        float tamanhoFontetab = 14;
        Vector2 tamanhoTextotab = MeasureTextEx(fonte_escrita, tab, tamanhoFontetab, espacamento);
        DrawTextEx(fonte_escrita, tab, (Vector2){50, 200}, tamanhoFontetab, espacamento, RAYWHITE);

        const char *tab2 = "Teclas W/A/S/D e as setas: Move o jogador uma posicao na direcao indicada";
        float tamanhoFontetab2 = 14;
        Vector2 tamanhoTextotab2 = MeasureTextEx(fonte_escrita, tab2, tamanhoFontetab2, espacamento);
        DrawTextEx(fonte_escrita, tab2, (Vector2){50, 300}, tamanhoFontetab2, espacamento, RAYWHITE);

        const char *tab3 = "Tecla J: Ativa a espada";
        float tamanhoFontetab3 = 14;
        Vector2 tamanhoTextotab3 = MeasureTextEx(fonte_escrita, tab3, tamanhoFontetab3, espacamento);
        DrawTextEx(fonte_escrita, tab3, (Vector2){50, 400}, tamanhoFontetab3, espacamento, RAYWHITE);

        const char *tab4 = "Pressione SPACE para iniciar o jogo";
        float tamanhoFontetab4 = 14;
        Vector2 tamanhoTextotab4 = MeasureTextEx(fonte_escrita, tab4, tamanhoFontetab4, espacamento);
        DrawTextEx(fonte_escrita, tab4, (Vector2){(LARGURA_TELA - tamanhoTextotab4.x) / 2.0f, 550}, tamanhoFontetab4, espacamento, RED);

    EndDrawing();

    if(IsKeyPressed(KEY_SPACE))
             return 4;        
    }
}

char* pedirnomejogador(){
    Font fonte_escrita = LoadFont("Fontes/PressStart2P.ttf");
    static char nome[MAX_NOME] = "";
    int posicao = 0;
    nome[0] = '\0';

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        const char *digitar_nome = "Digite seu nome sem espaco:";
        float tamanhoFontedigitarnome = 30;
        float espacamento = 0.7f;
        Vector2 tamanhoTextodigitarnome = MeasureTextEx(fonte_escrita, digitar_nome, tamanhoFontedigitarnome, espacamento);
        DrawTextEx(fonte_escrita, digitar_nome, (Vector2){(LARGURA_TELA - tamanhoTextodigitarnome.x) / 2.0f, 100}, tamanhoFontedigitarnome, espacamento, RAYWHITE);
        float tamanhoFontenome = 30;
        Vector2 tamanhoTextonome = MeasureTextEx(fonte_escrita, nome, tamanhoFontenome, espacamento);
        DrawTextEx(fonte_escrita, nome, (Vector2){(LARGURA_TELA - tamanhoTextonome.x) / 2.0f, 200}, tamanhoFontenome, espacamento, RAYWHITE);
        //DrawText(nome, 450, 200, 30, RAYWHITE);
        const char *enter = "Pressione TAB para continuar";
        float tamanhoFonteenter = 15;
        Vector2 tamanhoTextoenter = MeasureTextEx(fonte_escrita, enter, tamanhoFonteenter, espacamento);
        DrawTextEx(fonte_escrita, enter, (Vector2){(LARGURA_TELA - tamanhoTextoenter.x) / 2.0f, 300}, tamanhoFonteenter, espacamento, GRAY);
        EndDrawing();

        int tecla = GetCharPressed();
        if (tecla >= 32 && tecla <= 126 && posicao < MAX_NOME - 1) {
            nome[posicao] = (char)tecla;
            posicao++;
            nome[posicao] = '\0';
            }
        if (IsKeyPressed(KEY_BACKSPACE) && posicao > 0) {
            posicao--;
            nome[posicao] = '\0';
        }
        if (IsKeyPressed(KEY_ENTER)) {
            nome[posicao] = ' ';
            posicao++;
            nome[posicao] = '\0';
            }
        if (IsKeyPressed(KEY_TAB)) break;
        }
        return nome;

    }
