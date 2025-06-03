#ifndef ATUALIZARSTATUS_H
    #define ATUALIZARSTATUS_H
    #define VALOR_VIDA 5
    #define VALOR_ESPADA 10
    #define VALOR_MONSTRO 15

    #include "raylib.h"
    #include "jogador.h"
    #include "vida.h"
    #include "barrastatus.h"
    #include "monstro.h"
    #include "espada.h"

    void atualizarvida(Jogador *j, Vida vidas[], Barra *barra, int qntdVidas);
    void atualizarscore(Barra *barra, int qntdMonstrosMortos);
    void atualizarnivel();
    void atualizarespada(Espada *espada, Jogador *jogador, Barra *barra);
#endif