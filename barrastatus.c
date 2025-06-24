#include "raylib.h"
#include "barrastatus.h"

void desenharbarra(Barra barra)
{
    // Barra de vidas
    DrawText(barra.vidasstr,20,pY,TAM,WHITE);
    DrawText(barra.nivelstr,320,pY,TAM,WHITE);
    DrawText(barra.escorestr,620,pY,TAM,WHITE);
    DrawText(barra.espada_str,920,pY,TAM,WHITE);
}

void atualizarbarra(Barra *barra)
{
    // Atualiza barra de vidas durante o jogo
    sprintf(barra->vidasstr, "VIDAS: %d", barra->vidas);
    sprintf(barra->nivelstr, "NIVEL: %d", barra->nivel);
    sprintf(barra->escorestr, "ESCORE: %d", barra->escore);
    sprintf(barra->espada_str, "ESPADA: %s", barra->espada ? "SIM" : "NAO");
}
