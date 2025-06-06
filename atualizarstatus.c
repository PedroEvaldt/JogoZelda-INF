#include "raylib.h"
#include "atualizarstatus.h"

void atualizarvida(Jogador *jogador, Vida vidas[], Barra *barra, int qntdVidas) {
    for (int i = 0; i < LINHAS; i++){
        for (int j = 0; j < COLUNAS; j++){
            for (int k = 0; k < qntdVidas; k++) {
                if (vidas[k].ativa && vidas[k].x == jogador->x && vidas[k].y == jogador->y) {
                    vidas[k].ativa = false; // Remove a vida do mapa
                    jogador->vidas++; // Incrementa a vida do jogador
                    barra->vidas++;
                    barra->escore += VALOR_VIDA; // Atualiza a barra de status
                    sprintf(barra->vidasstr, "VIDAS: %d", barra->vidas);
                    sprintf(barra->escorestr, "ESCORE: %d", barra->escore);
                    qntdVidas--; // Decrementa a quantidade de vidas restantes no mapa
                    return; // Sai da função após pegar uma vida
                }
        }
    }
  }
}

void atualizarespada(Espada *espada, Jogador *jogador, Barra *barra) {
    if (espada->espada && espada->x == jogador->x && espada->y == jogador->y) {
        espada->espada = false; // Remove a espada do mapa
        jogador->espada = true; // Marca que o jogador pegou a espada
        barra->espada = true; // Atualiza a barra de status
        barra->escore += VALOR_ESPADA; // Incrementa o escore do jogador
        atualizarbarra(barra); // Atualiza a barra de status
        sprintf(barra->escorestr, "ESCORE: %d", barra->escore);
        UnloadTexture(jogador->jogador_sul);
        UnloadTexture(jogador->jogador_leste);
        UnloadTexture(jogador->jogador_oeste);
        UnloadTexture(jogador->jogador_norte);

        jogador->jogador_sul   = LoadTexture("sprites/jogador-sul-espada.png");
        jogador->jogador_norte = LoadTexture("sprites/jogador-norte.png"); // supondo que o norte é o mesmo
        jogador->jogador_leste = LoadTexture("sprites/jogador-leste-espada.png");
        jogador->jogador_oeste = LoadTexture("sprites/jogador-oeste-espada.png");
    }
}

void atualizarscore(Barra *barra, int qntdMonstrosMortos) {
    
    barra->escore += qntdMonstrosMortos * rand()%101; // Incrementa o escore baseado na quantidade de monstros mortos
    sprintf(barra->escorestr, "ESCORE: %d", barra->escore); // Atualiza a string do escore
}