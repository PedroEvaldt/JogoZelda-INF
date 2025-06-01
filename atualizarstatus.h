#ifndef ATUALIZARSTATUS_H
    #define ATUALIZARSTATUS_H
    #include "jogador.h"
    #include "vida.h"
    #include "barrastatus.h"
    #include "monstro.h"
    #include "espada.h"

    void atualizarvida(Jogador *j, Vida vidas[], Barra *barra, int qntdVidas);
    void atualizarscore();
    void atualizarnivel();
    void atualizarespada(Espada *espada, Jogador *jogador, Barra *barra);
#endif

/*
for (int k = 0; k < qntdMonstros; k++){
                if (monstros[k].ativo && monstros[k].x == jogador->x && monstros[k].y == jogador->y) {
                        jogador->vidas--; // Decrementa a vida do jogador
                        barra->vidas--; // Atualiza a barra de status
                        sprintf(barra->vidasstr, "VIDAS: %d", barra->vidas);
                        if (jogador->vidas <= 0) {
                            // Lógica para quando o jogador perde todas as vidas
                            //DrawText("GAME OVER", LARGURA_TELA / 2 - 100, ALTURA_TELA / 2, 20, RED);
                            //EndDrawing();
                            return; // Sai da função após perder todas as vidas
                    }
                }
            }
*/