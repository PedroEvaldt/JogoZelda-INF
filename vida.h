#ifndef VIDA_H
    #define VIDA_H
    #include "raylib.h"
    #include "mapa.h"
    #include <stdbool.h>
    typedef struct {
        int x, y;
        bool ativa;
        Texture2D vida_textura; 
    }Vida;

    void desenharVida(Vida vidas[], int qtd);
    int inicializarVida(Mapa mapa, Vida vidas[]);
#endif