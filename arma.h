#ifndef ARMA_H
    #define ARMA_H
    #include "raylib.h"
    #include "mapa.h"
    #include "monstro.h"
    #include "stdio.h"


    typedef struct {
        int ativa;
        int velocidade_bala;
        Texture2D bala_norte;
        Texture2D bala_sul;
        Texture2D bala_leste;
        Texture2D bala_oeste;
    }arma;

    arma inicializarArma(Jogador *jogador);
    void atirarArma(arma *arma, Jogador *jogador, Monstro monstros[], qntmonstros, Mapa *mapa);
#endif

