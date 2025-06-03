#ifndef espada_H
    #define espada_H
    #include <stdbool.h>
    #include "mapa.h"
    #include "jogador.h"
    #include "raylib.h"
    #include "monstro.h"
    typedef struct {
        int x, y;
        bool espada;
        Texture2D espada_textura;


    } Espada;

    Espada inicializarespada(Mapa mapa);
    void desenharespada(Espada espada);
    int ataqueEspada(Espada *espada, Jogador *jogador, Mapa *mapa, int qnt_monstros, Monstro monstros[]);
#endif