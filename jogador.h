#ifndef JOGADOR_H
    #define JOGADOR_H
    #include <stdbool.h>
    #include "mapa.h"
    typedef struct {
        int x, y;
        int vidas;
        int pontuacao;
        bool espada;
        char direcao;
        Texture2D jogador_sul;
        Texture2D jogador_norte;
        Texture2D jogador_leste;
        Texture2D jogador_oeste;

    } Jogador;

    Jogador inicializarJogador(Mapa mapa);
    void atualizarJogador(Jogador *j, Mapa mapa);
    void desenharJogador(Jogador j);
#endif