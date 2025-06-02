#ifndef espada_H
    #define espada_H
    #include <stdbool.h>
    #include "mapa.h"
    #include "jogador.h"
    typedef struct {
        int x, y;
        bool espada;
        Texture2D espada_textura;


    } Espada;

    Espada inicializarespada(Mapa mapa);
    void desenharespada(Espada espada);
    void ataqueEspada(Espada *espada, Jogador *jogador, Texture2D sprite, Mapa *mapa, int qnt_monstros, Monstro monstros[]);
#endif