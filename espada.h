#ifndef espada_H
    #define espada_H
    #include <stdbool.h>
    #include "mapa.h"
    typedef struct {
        int x, y;
        bool espada;
        Texture2D espada_textura;


    } Espada;

    Espada inicializarespada(Mapa mapa);
    void desenharespada(Espada espada);
#endif