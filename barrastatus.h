#ifndef barrastatus_H
    #define barrastatus_H
    #include <string.h>
    #define N 20
    #define pY 20
    #define TAM 35

    typedef struct {
        char vidas[N];
        char nivel[N];
        char escore[N];
    } Barra;

    void desenharbarra(Barra barra);

#endif