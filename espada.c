#include "espada.h"
#include "raylib.h"

Espada inicializarespada(Mapa mapa) {
    Espada espada = {0};  // zera a struct
    espada.espada = false;
    espada.espada_textura = LoadTexture("sprites/espada.png");

    for (int i = 0; i < 16; i++) {
        for (int k = 0; k < 24; k++) {
            if (mapa.celulas[i][k] == 'E') {
                espada.x = k;
                espada.y = i;
                espada.espada = true; // marca que a espada foi encontrada
                return espada;
            }
        }
    }

    return espada;
}

void desenharespada(Espada espada) {
    if (!espada.espada) return; // Se a espada não estiver ativa, não desenha
    Texture2D sprite;
    sprite = espada.espada_textura;
    Rectangle source = { 0.0f, 0.0f, (float)sprite.width, (float)sprite.height };
    Rectangle dest = { espada.x * 50.0f, espada.y * 50.0f + 60.0f, 50.0f, 50.0f };
    Vector2 origin = { 0.0f, 0.0f };
    DrawTexturePro(sprite, source, dest, origin, 0.0f, WHITE);
}