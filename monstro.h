#ifndef MONSTRO_H
    #define MONSTRO_H
    #include <stdbool.h>
    #include "mapa.h"
    #include "jogador.h"
    #include "barrastatus.h"

    typedef struct {
        int x, y;
        char direcao; // N, S, L, O
        int pontuacao; // entre 0 e 100
        bool ativo; // se foi derrotado ou não
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