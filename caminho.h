#ifndef CAMINHO_H
#define CAMINHO_H
#include "mapa.h"
#include <stdbool.h>

bool encontrarCaminho(Mapa mapa, int posX_InicialMonstro, int sposY_InicialMonstroy, int eposX_FinalJogador, int eyeposY_FinalJogador, int* proximoX, int* proximoY);

#endif