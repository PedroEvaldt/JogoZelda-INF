#ifndef barrastatus_H
    #define barrastatus_H
    #include <string.h>
    #include <stdbool.h>
    #include "jogador.h"
    #define N 20
    #define pY 20
    #define TAM 35

    typedef struct Barra{
        int vidas;
        int nivel;
        int escore;
        bool espada;
        char vidasstr[N];
        char nivelstr[N];
        char escorestr[N];
        char espada_str[N];
    } Barra;

    void desenharbarra(Barra barra);
    void atualizarbarra(Barra *barra);

#endif