#ifndef MONSTRO_H
    #define MONSTRO_H
    #include "mapa.h"
    #include "raylib.h"
    #include <stdlib.h>
    #include <stdbool.h>
    #include <time.h>
    #include "barrastatus.h"
    typedef struct Jogador Jogador;
    typedef struct Barra Barra;
    typedef struct {
        int x, y;
        char direcao; // N, S, L, O
        bool ativo; // se foi derrotado ou não
        int pontuacao; // pontuação do monstro
        Texture2D monstro;
        Texture2D monstro_norte;
        Texture2D monstro_sul;
        Texture2D monstro_leste;
        Texture2D monstro_oeste;
    } Monstro;

    int inicializarMonstros(Mapa mapa, Monstro monstros[]);
    void moverMonstros(Monstro monstros[], int qtd, Mapa mapa, Jogador *jogador, Barra *barra);
    void desenharMonstros(Monstro monstros[], int qtd);

#endif