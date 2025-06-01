#ifndef VIDA_H
    #define VIDA_H
    #include "mapa.h"
    #include <stdbool.h>
    typedef struct {
        int x, y;
        bool ativa;
        Texture2D vida_textura; // Textura da vida
    }Vida;

    void desenharVida(Vida vidas[], int qtd);
    void inicializarVida(Mapa mapa, Vida vidas[]);
#endif