#ifndef SCORE_H
   #define SCORE_H
   #define MAX_NOME 20
   #define MAX_SCORES 100
   #define ARQUIVO_SCORE "scores.txt"
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include "raylib.h"
   #include "jogador.h"
   typedef struct Scores {
        char nome[20];
        int pontuacao;
   } Scores;

   void salvarScore(const char *nome, int score);
   int mostrarTop5();
#endif