#ifndef MAPA_H
    #define MAPA_H
    #include "raylib.h"
    #include <stdio.h>
    #define LINHAS 16
    #define COLUNAS 24
    #define TAM_MENUJOGO 60
    #define TAM_CELULA 50
    typedef struct mapa {
        char celulas[LINHAS][COLUNAS];
        Texture2D parede;
        Texture2D espada;
        Texture2D vida;
        Texture2D fundo_tela;
        Texture2D chao;
    } Mapa;

    Mapa carregarMapa(int fase);
    void desenharMapa(Mapa mapa);
    void descarregarTexturasMapa(Mapa *mapa);
#endif
