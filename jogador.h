#ifndef JOGADOR_H
    #define JOGADOR_H
    #include <stdbool.h>
    #include <stdio.h>
    #include "mapa.h"
    #include "vida.h"
    #include "monstro.h"
    #include "barrastatus.h"
    #include "raylib.h"
    #include "arma.h"

    typedef struct Jogador{
        int x, y;
        int vidas;
        int pontuacao;
        bool espada;
        char direcao;
        char nome[20];
        double tempo_ultimo_dano;
        //arma arma;
        Texture2D jogador_sul;
        Texture2D jogador_norte;
        Texture2D jogador_leste;
        Texture2D jogador_oeste;
        

    } Jogador;

    Jogador inicializarJogador(Mapa mapa);
    void atualizarJogador(Jogador *jogador, Mapa mapa, Monstro monstros[], int qnt_monstros, Barra *barra);
    void desenharJogador(Jogador j);
    
#endif
