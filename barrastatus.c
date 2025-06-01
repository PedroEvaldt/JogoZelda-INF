#include "raylib.h"
#include "barrastatus.h"

void desenharbarra(Barra barra)
{
    DrawText(barra.vidas,20,pY,TAM,WHITE);
    DrawText(barra.nivel,320,pY,TAM,WHITE);
    DrawText(barra.escore,620,pY,TAM,WHITE);
}
