#include "mapa.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_CELULAS 386

typedef struct NoAStar {
    int x, y;
    int g, h, f;
    struct NoAStar* pai;
} NoAStar;

// Heurística Manhattan (Ver distancia absoluta)
int heuristica(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Verifica se a posição está dentro dos limites e não é parede
bool posicaoValida(int x, int y, Mapa mapa) {
    return x >= 0 && x < COLUNAS &&
           y >= 0 && y < LINHAS &&
           mapa.celulas[y][x] != 'P';
}

// Gera até 4 vizinhos válidos (cima, baixo, esquerda, direita)
int gerarVizinhos(int x, int y, Mapa mapa, NoAStar vizinhos[4]) {
    int count = 0;
    // Combinação de vetores da as direções.
    // posX_FinalJogadoremplo: 0, -1 = Cima
    int dx[] = { 0,  0, -1, 1};  
    int dy[] = {-1,  1,  0, 0};

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        // Verifica se os x e y dos vizinhos são válidos
        if (posicaoValida(nx, ny, mapa)) {
            vizinhos[count].x = nx;
            vizinhos[count].y = ny;
            count++;
        }
    }

    return count;
}

// Função principal
bool encontrarCaminho(Mapa mapa, int posX_InicialMonstro, int posY_InicialMonstro, int posX_FinalJogador, int posY_FinalJogador, int* proximoX, int* proximoY) {
    // Inicializa numero maximo de celulas
    NoAStar abertos[MAX_CELULAS];
    bool fechado[LINHAS][COLUNAS] = { false };
    int total_abertos = 0;

    // Inicializa o nó inicial
    NoAStar inicio = {posX_InicialMonstro, posY_InicialMonstro, 0, heuristica(posX_InicialMonstro, posY_InicialMonstro, posX_FinalJogador, posY_FinalJogador), 0, NULL};
    inicio.f = inicio.g + inicio.h;
    abertos[0] = inicio;
    total_abertos = 1;

    while (total_abertos > 0) {
        // Seleciona o nó com menor f
        int melhorIndice = 0;
        for (int i = 1; i < total_abertos; i++) {
            if (abertos[i].f < abertos[melhorIndice].f)
                melhorIndice = i;
        }

        NoAStar atual = abertos[melhorIndice];

        // Se chegou ao destino
        if (atual.x == posX_FinalJogador && atual.y == posY_FinalJogador) {
            NoAStar* ptr = &atual;

            // Enquanto o pai não for nulo e não for o nó inicial, percorre os pais para encontrar o caminho
            while (ptr->pai != NULL && !(ptr->pai->x == posX_InicialMonstro && ptr->pai->y == posY_InicialMonstro)) {
                ptr = ptr->pai;
            }

            *proximoX = ptr->x;
            *proximoY = ptr->y;

            // Libera a memória dos pais
            while (ptr->pai != NULL) {
                NoAStar* temp = ptr->pai;
                free(ptr->pai);
                ptr->pai = temp->pai;
            }

            return true;
        }

        // Se ainda não chegou ao destino remove o atual da lista de abertos
        for (int i = melhorIndice; i < total_abertos - 1; i++) {
            abertos[i] = abertos[i + 1];
        }
        // Por conta do for duplicar o ultimo elemento, tira o ultimo elemento da lista para ficar certo
        total_abertos--;

        fechado[atual.y][atual.x] = true;

        // Pega os vizinhos do nó atual
        NoAStar vizinhos[4];
        int qntVizinhos = gerarVizinhos(atual.x, atual.y, mapa, vizinhos);

        for (int i = 0; i < qntVizinhos; i++) {
            int nx = vizinhos[i].x;
            int ny = vizinhos[i].y;

            if (fechado[ny][nx]) continue;

            int g_novo = atual.g + 1;

            bool jaAberto = false;
            // Verifica se o no já está na lista de abertos
            for (int j = 0; j < total_abertos; j++) {
                if (abertos[j].x == nx && abertos[j].y == ny) {
                    // Se estiver, verifica se o novo caminho é melhor
                    if (g_novo < abertos[j].g) {
                        abertos[j].g = g_novo;
                        abertos[j].f = g_novo + abertos[j].h;
                        abertos[j].pai = malloc(sizeof(NoAStar));
                        *abertos[j].pai = atual;
                    }
                    jaAberto = true;
                    break;
                }
            }
            // Se não estiver na lista de abertos, adiciona o novo nó
            if (!jaAberto) {
                NoAStar novo;
                novo.x = nx;
                novo.y = ny;
                novo.g = g_novo;
                novo.h = heuristica(nx, ny, posX_FinalJogador, posY_FinalJogador);
                novo.f = novo.g + novo.h;
                novo.pai = malloc(sizeof(NoAStar));
                *novo.pai = atual;
                abertos[total_abertos++] = novo;
            }
        }
    }

    return false;
}