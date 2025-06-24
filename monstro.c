#include "raylib.h"
#include "monstro.h"
#include "jogador.h"
#include "caminho.h"  // Para o algoritmo A* de movimentação

// Inicializa os monstros com base no mapa
int inicializarMonstros(Mapa mapa, Monstro monstros[]) {
    int contador = 0;

    // Inicializa o gerador de números aleatórios com base no tempo atual
    srand(time(NULL));

    // Percorre todas as células do mapa
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {

            // Verifica se há um monstro na célula ('M') e se ainda cabe no array (limite 10)
            if (mapa.celulas[i][j] == 'M' && contador < 10) {
                monstros[contador].x = j;
                monstros[contador].y = i;
                monstros[contador].direcao = 'N'; // Direção inicial

                // Define pontuação aleatória entre 0 e 100 para o monstro
                monstros[contador].pontuacao = rand() % 101;

                monstros[contador].ativo = true;

                // Carrega todas as direções possíveis do sprite do monstro
                monstros[contador].monstro = LoadTexture("sprites/monstro_sul.png");
                monstros[contador].monstro_norte = LoadTexture("sprites/monstro_norte.png");
                monstros[contador].monstro_sul = LoadTexture("sprites/monstro_sul.png");
                monstros[contador].monstro_leste = LoadTexture("sprites/monstro_leste.png");
                monstros[contador].monstro_oeste = LoadTexture("sprites/monstro_oeste.png");

                contador++;
            }
        }
    }

    // Retorna o número total de monstros inicializados
    return contador;
}

// Move todos os monstros do array conforme a lógica de perseguição ou movimento aleatório
void moverMonstros(Monstro monstros[], int qtd, Mapa mapa, Jogador *jogador, Barra *barra) {
    int raio_perseguir = 20; // Distância máxima para perseguir o jogador

    for (int i = 0; i < qtd; i++) {
        if (!monstros[i].ativo) continue; // Pula monstros inativos

        // Calcula distância de Manhattan até o jogador
        int dx = jogador->x - monstros[i].x;
        int dy = jogador->y - monstros[i].y;
        int distancia = abs(dx) + abs(dy);

        int novoX = monstros[i].x;
        int novoY = monstros[i].y;

        // Se jogador estiver perto, tenta seguir com A*
        if (distancia <= raio_perseguir) {
            int proximoX, proximoY;
            bool caminho_encontrado = encontrarCaminho(mapa, monstros[i].x, monstros[i].y, jogador->x, jogador->y, &proximoX, &proximoY);

            if (caminho_encontrado) {
                novoX = proximoX;
                novoY = proximoY;

                // Atualiza a direção do monstro com base no deslocamento
                if (novoX > monstros[i].x) monstros[i].direcao = 'L';
                else if (novoX < monstros[i].x) monstros[i].direcao = 'O';
                else if (novoY > monstros[i].y) monstros[i].direcao = 'S';
                else if (novoY < monstros[i].y) monstros[i].direcao = 'N';
            } else {
                // Se não encontrar caminho, move aleatoriamente
                int dir = rand() % 4;
                switch (dir) {
                    case 0: novoY--; monstros[i].direcao = 'N'; break;
                    case 1: novoY++; monstros[i].direcao = 'S'; break;
                    case 2: novoX--; monstros[i].direcao = 'O'; break;
                    case 3: novoX++; monstros[i].direcao = 'L'; break;
                }
            }
        } else {
            // Movimento aleatório fora do raio de perseguição
            int dir = rand() % 4;
            switch (dir) {
                case 0: novoY--; monstros[i].direcao = 'N'; break;
                case 1: novoY++; monstros[i].direcao = 'S'; break;
                case 2: novoX--; monstros[i].direcao = 'O'; break;
                case 3: novoX++; monstros[i].direcao = 'L'; break;
            }
        }

        // Verifica se o novo local é válido (não é parede e está dentro dos limites)
        if (novoX >= 0 && novoX < COLUNAS && novoY >= 0 && novoY < LINHAS && mapa.celulas[novoY][novoX] != 'P') {

            // Verifica colisão com o jogador
            if (novoX == jogador->x && novoY == jogador->y) {

                // Se jogador ainda pode levar dano (1 segundo de intervalo)
                if (GetTime() - jogador->tempo_ultimo_dano > 1.0) {
                    jogador->vidas--;
                    barra->vidas--;

                    // Atualiza string de status da barra
                    sprintf(barra->vidasstr, "VIDAS: %d", barra->vidas);

                    jogador->tempo_ultimo_dano = GetTime();

                    // Aplica knockback no jogador (empurra para trás)
                    int knockX = jogador->x - monstros[i].x;
                    int knockY = jogador->y - monstros[i].y;
                    int destinoX = jogador->x + knockX;
                    int destinoY = jogador->y + knockY;

                    // Só aplica knockback se o novo local for válido
                    if (destinoX >= 0 && destinoX < COLUNAS && destinoY >= 0 && destinoY < LINHAS && mapa.celulas[destinoY][destinoX] != 'P') {
                        jogador->x = destinoX;
                        jogador->y = destinoY;
                    }
                }

            } else {
                // Se não colidir com o jogador, move normalmente
                monstros[i].x = novoX;
                monstros[i].y = novoY;
            }
        }

        // Se o jogador morreu, termina a função
        if (jogador->vidas <= 0) return;
    }
}

// Desenha todos os monstros ativos na tela
void desenharMonstros(Monstro monstros[], int qtd) {
    for (int i = 0; i < qtd; i++) {
        if (monstros[i].ativo) {
            Texture2D sprite;

            // Seleciona o sprite de acordo com a direção atual
            switch (monstros[i].direcao) {
                case 'N': sprite = monstros[i].monstro_norte; break;
                case 'S': sprite = monstros[i].monstro_sul; break;
                case 'L': sprite = monstros[i].monstro_leste; break;
                case 'O': sprite = monstros[i].monstro_oeste; break;
                default:  sprite = monstros[i].monstro; break; // backup
            }

            // Define qual parte da textura usar (imagem inteira)
            Rectangle source = { 0.0f, 0.0f, (float)sprite.width, (float)sprite.height };

            // Calcula posição na tela baseada na posição no mapa
            Rectangle dest = { monstros[i].x * TAM_CELULA, monstros[i].y * TAM_CELULA + TAM_MENUJOGO, TAM_CELULA, TAM_CELULA };

            // Ponto de origem (canto superior esquerdo)
            Vector2 origin = { 0.0f, 0.0f };

            // Desenha o monstro na tela
            DrawTexturePro(sprite, source, dest, origin, 0.0f, WHITE);
        }
    }
}