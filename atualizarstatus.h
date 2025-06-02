#ifndef ATUALIZARSTATUS_H
    #define ATUALIZARSTATUS_H
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