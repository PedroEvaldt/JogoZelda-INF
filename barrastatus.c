#include "raylib.h"
#include "barrastatus.h"
#include <stdio.h>

void desenharbarra(Barra barra)
{
    //barra.vidas = 
    DrawText(barra.vidasstr,20,pY,TAM,WHITE);
    DrawText(barra.nivelstr,320,pY,TAM,WHITE);
    DrawText(barra.escorestr,620,pY,TAM,WHITE);
    DrawText(barra.espada_str,920,pY,TAM,WHITE);
}

void atualizarbarra(Barra *barra)
{
    sprintf(barra->vidasstr, "VIDAS: %d", barra->vidas);
    sprintf(barra->nivelstr, "NIVEL: %d", barra->nivel);
    sprintf(barra->escorestr, "ESCORE: %d", barra->escore);
    sprintf(barra->espada_str, "ESPADA: %s", barra->espada ? "SIM" : "NAO");
}
