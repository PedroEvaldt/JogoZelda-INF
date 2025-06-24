#include "raylib.h"
#include "jogador.h"

// Função que inicializa a struct Jogador com suas propriedades básicas
Jogador inicializarJogador(Mapa mapa) {
    Jogador jogador = {0};  // Inicializa todos os campos com zero/false

    // Define valores iniciais
    jogador.vidas = 3;
    jogador.pontuacao = 0;
    jogador.espada = false;
    jogador.tempo_ultimo_dano = 0.0;

    // Carrega as texturas (sprites) do jogador para cada direção
    jogador.jogador_sul   = LoadTexture("sprites/jogador-sul.png");
    jogador.jogador_norte = LoadTexture("sprites/jogador-norte.png");
    jogador.jogador_leste = LoadTexture("sprites/jogador-leste.png");
    jogador.jogador_oeste = LoadTexture("sprites/jogador-oeste.png");

    // Busca a posição inicial do jogador no mapa (marcado por 'J')
    for (int i = 0; i < 16; i++) {
        for (int k = 0; k < 24; k++) {
            if (mapa.celulas[i][k] == 'J') {
                jogador.x = k; // coluna (horizontal)
                jogador.y = i; // linha (vertical)
                return jogador;
            }
        }
    }

    return jogador; // Se não encontrar, retorna na posição 0
}

// Atualiza o estado e posição do jogador conforme entrada do usuário e colisões
void atualizarJogador(Jogador *jogador, Mapa mapa, Monstro monstros[], int qnt_monstros, Barra *barra) {
    static double tempoUltimoMovimento = 0; // Controla o intervalo entre movimentos
    double tempoAtual = GetTime();
    double intervaloMovimento = 0.15; // Tempo mínimo entre dois movimentos

    // Se o intervalo ainda não passou, não movimenta
    if (tempoAtual - tempoUltimoMovimento < intervaloMovimento)
        return;

    int novoX = jogador->x;
    int novoY = jogador->y;
    bool moveu = false;

    // Detecta teclas de movimentação e altera posição alvo
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        novoX += 1;
        jogador->direcao = 'L'; // Leste (direita)
        moveu = true;
    } else if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        novoX -= 1;
        jogador->direcao = 'O'; // Oeste (esquerda)
        moveu = true;
    } else if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        novoY -= 1;
        jogador->direcao = 'N'; // Norte (cima)
        moveu = true;
    } else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        novoY += 1;
        jogador->direcao = 'S'; // Sul (baixo)
        moveu = true;
    }

    // Se nenhuma tecla foi pressionada, sai da função
    if (!moveu)
        return;

    // Impede movimentação fora dos limites do mapa
    if (novoX < 0 || novoX >= COLUNAS || novoY < 0 || novoY >= LINHAS)
        return;

    // Impede movimentação para cima de uma parede
    if (mapa.celulas[novoY][novoX] == 'P')
        return;

    // Verifica se existe monstro na nova posição
    bool temMonstro = false;
    for (int i = 0; i < qnt_monstros; i++) {
        if (monstros[i].ativo && monstros[i].x == novoX && monstros[i].y == novoY) {
            temMonstro = true;
            break;
        }
    }

    if (temMonstro) {
        // Aplica dano se o jogador ainda pode ser atingido
        if (tempoAtual - jogador->tempo_ultimo_dano >= 1.0) {
            jogador->vidas--;
            barra->vidas--;

            // Atualiza o texto da barra de status
            sprintf(barra->vidasstr, "VIDAS: %d", barra->vidas);
            jogador->tempo_ultimo_dano = tempoAtual;

            // Calcula direção do knockback (empurrar para trás)
            int dx = jogador->x - novoX;
            int dy = jogador->y - novoY;
            int destinoX = jogador->x + dx;
            int destinoY = jogador->y + dy;

            // Só aplica knockback se a nova posição for válida
            if (destinoX >= 0 && destinoX < COLUNAS &&
                destinoY >= 0 && destinoY < LINHAS &&
                mapa.celulas[destinoY][destinoX] != 'P') {
                jogador->x = destinoX;
                jogador->y = destinoY;
            }
        }
    } else {
        // Movimento válido e sem colisão: atualiza posição
        jogador->x = novoX;
        jogador->y = novoY;
        tempoUltimoMovimento = tempoAtual;
    }
}

// Desenha o sprite do jogador na tela com base na direção
void desenharJogador(Jogador jogador) {
    Texture2D sprite;

    // Seleciona sprite correspondente à direção atual
    switch (jogador.direcao) {
        case 'N': sprite = jogador.jogador_norte; break;
        case 'S': sprite = jogador.jogador_sul; break;
        case 'L': sprite = jogador.jogador_leste; break;
        case 'O': sprite = jogador.jogador_oeste; break;
        default:  sprite = jogador.jogador_sul; break; // fallback
    }

    // Define qual parte da imagem usar (imagem toda)
    Rectangle source = { 0.0f, 0.0f, (float)sprite.width, (float)sprite.height };

    // Define onde e em que tamanho o sprite será desenhado
    Rectangle dest = {
        jogador.x * TAM_CELULA,
        jogador.y * TAM_CELULA + TAM_MENUJOGO, // Compensação da barra superior
        TAM_CELULA,
        TAM_CELULA
    };

    Vector2 origin = { 0.0f, 0.0f }; // Sem rotação

    // Desenha o sprite do jogador na tela
    DrawTexturePro(sprite, source, dest, origin, 0.0f, WHITE);
}