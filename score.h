#ifndef SCORE_H
   #define SCORE_H
   #define MAX_NOME 50
   #define MAX_SCORES 5
   #define ARQUIVO_SCORE "highscores_ab.bin"
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   #include "raylib.h" 
   #include "jogador.h"
   typedef struct Scores {
        char nome[MAX_NOME];
        int pontuacao;
   } Scores;

   void salvarScore(const char *nome, int score);
   void mostrarTop5();
   bool NovoRecorde(int score);
#endif