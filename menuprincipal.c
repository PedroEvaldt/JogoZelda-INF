#include "raylib.h"
#include "menuprincipal.h"

// Função principal que exibe o menu com botões para iniciar, ver ranking, sair e ver tutorial
int exibirMenuPrincipal()
{   
    // Carrega a fonte personalizada
    Font fonte_escrita = LoadFont("Fontes/PressStart2P.ttf");

    // Define cores padrão dos botões
    Color CorBotao = GRAY;
    Color CorMouseBotao = WHITE;
    Color CorBotaoPressionado = DARKGRAY;

    // Define os retângulos (posição e tamanho) dos botões na tela
    Rectangle BotaoIniciar = {LARGURA_TELA / 2 - 100, 300, 200, 60};
    Rectangle BotaoScore = {LARGURA_TELA / 2 - 100, 450, 200, 60};
    Rectangle BotaoSair = {LARGURA_TELA / 2 - 100, 600, 200, 60};
    Rectangle BotaoTutorial = {20, 800, 200, 60};     

    // Flags para controle de cliques nos botões
    bool BotaoIniciarPressionado = false;
    bool BotaoScorePressionado = false;
    bool BotaoSairPressionado = false;
    bool BotaoTutorialPressionado = false;

    // Texturas dos personagens usados como decoração no menu
    Texture2D jogador = LoadTexture("sprites/jogador-sul.png");
    Texture2D monstro = LoadTexture("sprites/monstro_sul.png");

    while (!WindowShouldClose())
    {
        Vector2 posicaomouse = GetMousePosition();

        // ------------------ Botão INICIAR ------------------
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
                if (BotaoIniciarPressionado && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
                    UnloadTexture(jogador);
                    UnloadTexture(monstro);
                    return 1; // Iniciar o jogo
                }
                BotaoIniciarPressionado = false; 
            }
        }
        else
        {
            CorBotaoIniciar = GRAY; 
            BotaoIniciarPressionado = false;
        }

        // ------------------ Botão SCOREBOARD ------------------
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
                if (BotaoScorePressionado && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
                    UnloadTexture(jogador);
                    UnloadTexture(monstro);
                    return 2; // Ir para tela de score
                }
                BotaoScorePressionado = false; 
            }
        }
        else
        {
            CorBotaoScore = GRAY; 
            BotaoScorePressionado = false;
        }

        // ------------------ Botão SAIR ------------------
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
                if (BotaoSairPressionado && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)){
                    UnloadTexture(jogador);
                    UnloadTexture(monstro);
                    return 3; // Sair do jogo
                }
                BotaoSairPressionado = false; 
            }
        }
        else
        {
            CorBotaoSair = GRAY; 
            BotaoSairPressionado = false;
        }

        // ------------------ Renderização do Menu ------------------
        BeginDrawing();
            ClearBackground(BLACK);

            // Desenha o jogador e o monstro na tela
            Vector2 posicaoJ = {180,290};
            Vector2 posicaoM = {870,300};
            DrawTextureEx(jogador,posicaoJ,0,0.55,WHITE);
            DrawTextureEx(monstro,posicaoM,0,0.5,WHITE);

            // Título do menu
            const char *menu_principal = "MENU PRINCIPAL";
            float tamanhoFonteMENUPRINCIPAL = 50;
            float espacamento = 0.7f;
            Vector2 tamanhoTextomenu = MeasureTextEx(fonte_escrita, menu_principal, tamanhoFonteMENUPRINCIPAL, espacamento);
            DrawTextEx(fonte_escrita, menu_principal, (Vector2){(LARGURA_TELA - tamanhoTextomenu.x) / 2.0f, 50}, tamanhoFonteMENUPRINCIPAL, espacamento, WHITE);

            // Botão INICIAR
            DrawRectangleRec(BotaoIniciar, CorBotaoIniciar);
            const char *iniciar = "INICIAR";
            float tamanhoFonteiniciar = 15;
            Vector2 tamanhoTextoiniciar = MeasureTextEx(fonte_escrita, iniciar, tamanhoFonteiniciar, espacamento);
            DrawTextEx(fonte_escrita, iniciar, (Vector2){(LARGURA_TELA - tamanhoTextoiniciar.x) / 2.0f, 325}, tamanhoFonteiniciar, espacamento, BLACK);

            // Botão SCOREBOARD
            DrawRectangleRec(BotaoScore, CorBotaoScore);
            const char *scoreboard = "SCOREBOARD";
            float tamanhoFontescoreboard = 15;
            Vector2 tamanhoTextoscrboard = MeasureTextEx(fonte_escrita, scoreboard, tamanhoFontescoreboard, espacamento);
            DrawTextEx(fonte_escrita, scoreboard, (Vector2){(LARGURA_TELA - tamanhoTextoscrboard.x) / 2.0f, 475}, tamanhoFontescoreboard, espacamento, BLACK);

            // Botão SAIR
            DrawRectangleRec(BotaoSair, CorBotaoSair);
            const char *sair = "SAIR";
            float tamanhoFontesair = 15;
            Vector2 tamanhoTextosair = MeasureTextEx(fonte_escrita, sair, tamanhoFontesair, espacamento);
            DrawTextEx(fonte_escrita, sair, (Vector2){(LARGURA_TELA - tamanhoTextosair.x) / 2.0f, 625}, tamanhoFontesair, espacamento, BLACK);

        EndDrawing();
    }
}

// Exibe a tela com instruções e informações sobre os controles
int exibirTelaInfo()
{   
    Font fonte_escrita = LoadFont("Fontes/PressStart2P.ttf");
    float espacamento = 0.7f;

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(BLACK);

        // Título
        const char *sobre = "Sobre o jogo:";
        float tamanhoFontesobre = 30;
        Vector2 tamanhoTextofonte = MeasureTextEx(fonte_escrita, sobre, tamanhoFontesobre, espacamento);
        DrawTextEx(fonte_escrita, sobre, (Vector2){(LARGURA_TELA - tamanhoTextofonte.x) / 2.0f, 80}, tamanhoFontesobre, espacamento, RAYWHITE);

        // Instruções de controle
        const char *tab = "Tecla TAB: Pausa o jogo e abre/fecha o menu do jogo";
        DrawTextEx(fonte_escrita, tab, (Vector2){50, 200}, 14, espacamento, RAYWHITE);

        const char *tab2 = "Teclas W/A/S/D e as setas: Move o jogador uma posicao na direcao indicada";
        DrawTextEx(fonte_escrita, tab2, (Vector2){50, 300}, 14, espacamento, RAYWHITE);

        const char *tab3 = "Tecla J: Ativa a espada";
        DrawTextEx(fonte_escrita, tab3, (Vector2){50, 400}, 14, espacamento, RAYWHITE);

        const char *tab4 = "Pressione SPACE para iniciar o jogo";
        Vector2 tamanhoTextotab4 = MeasureTextEx(fonte_escrita, tab4, 14, espacamento);
        DrawTextEx(fonte_escrita, tab4, (Vector2){(LARGURA_TELA - tamanhoTextotab4.x) / 2.0f, 550}, 14, espacamento, RED);

        EndDrawing();

        if(IsKeyPressed(KEY_SPACE)){
            UnloadFont(fonte_escrita);
            return 4;  // Iniciar o jogo após ler instruções
        }
    }
}

// Função que permite o jogador digitar seu nome
char* pedirnomejogador(){
    Font fonte_escrita = LoadFont("Fontes/PressStart2P.ttf");

    static char nome[MAX_NOME] = "";
    int posicao = 0;
    nome[0] = '\0'; // Garante que a string esteja vazia no início

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Título da tela de entrada de nome
        const char *digitar_nome = "Digite seu nome:";
        Vector2 tamanhoTextodigitarnome = MeasureTextEx(fonte_escrita, digitar_nome, 30, 0.7f);
        DrawTextEx(fonte_escrita, digitar_nome, (Vector2){(LARGURA_TELA - tamanhoTextodigitarnome.x) / 2.0f, 100}, 30, 0.7f, RAYWHITE);

        // Mostra o nome digitado até o momento
        Vector2 tamanhoTextonome = MeasureTextEx(fonte_escrita, nome, 30, 0.7f);
        DrawTextEx(fonte_escrita, nome, (Vector2){(LARGURA_TELA - tamanhoTextonome.x) / 2.0f, 200}, 30, 0.7f, RAYWHITE);

        const char *enter = "Pressione ENTER para continuar";
        Vector2 tamanhoTextoenter = MeasureTextEx(fonte_escrita, enter, 15, 0.7f);
        DrawTextEx(fonte_escrita, enter, (Vector2){(LARGURA_TELA - tamanhoTextoenter.x) / 2.0f, 300}, 15, 0.7f, GRAY);

        EndDrawing();

        // Lê teclas digitadas
        int tecla = GetCharPressed();
        if (tecla >= 32 && tecla <= 126 && posicao < MAX_NOME - 1) {
            nome[posicao] = (char)tecla;
            posicao++;
            nome[posicao] = '\0';
        }

        // Apaga último caractere
        if (IsKeyPressed(KEY_BACKSPACE) && posicao > 0) {
            posicao--;
            nome[posicao] = '\0';
        }

        // Finaliza entrada com ENTER
        if (IsKeyPressed(KEY_ENTER)) {
            break;
        }
    }

    UnloadFont(fonte_escrita);
    return nome;
}