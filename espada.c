#include "raylib.h"
#include "espada.h"

// Inicializa a espada a partir do mapa
Espada inicializarespada(Mapa mapa) {
    Espada espada = {0};  // Zera todos os campos da struct

    espada.espada = false; // Marca inicialmente que a espada não foi coletada
    espada.espada_textura = LoadTexture("sprites/espada.png"); // Carrega a textura da espada

    // Percorre o mapa procurando pela célula marcada com 'E'
    for (int i = 0; i < LINHAS; i++) {
        for (int k = 0; k < COLUNAS; k++) {
            if (mapa.celulas[i][k] == 'E') {
                espada.x = k;  // Coluna onde está a espada
                espada.y = i;  // Linha onde está a espada
                espada.espada = true; // Marca que a espada foi encontrada
                return espada; // Retorna imediatamente após achar
            }
        }
    }

    return espada; // Retorna espada (com estado falso se não achou)
}

// Desenha a espada no mapa (se estiver ativa/visível)
void desenharespada(Espada espada) {
    if (!espada.espada) return; // Se não estiver ativa, não desenha

    Texture2D sprite = espada.espada_textura;

    // Define a parte da imagem a ser usada (imagem inteira)
    Rectangle source = { 0.0f, 0.0f, (float)sprite.width, (float)sprite.height };

    // Define onde a espada será desenhada na tela
    Rectangle dest = {
        espada.x * TAM_CELULA,
        espada.y * TAM_CELULA + TAM_MENUJOGO,
        TAM_CELULA,
        TAM_CELULA
    };

    Vector2 origin = { 0.0f, 0.0f };

    // Desenha a espada na tela
    DrawTexturePro(sprite, source, dest, origin, 0.0f, WHITE);
}
// Executa o ataque da espada e verifica colisão com monstros
int ataqueEspada(Espada *espada, Jogador *jogador, Mapa *mapa, int qnt_monstros, Monstro monstros[]) {
    Texture2D sprite = espada->espada_textura;
    int monstros_mortos = 0; // Contador de monstros derrotados

    if (!(jogador->espada)) return 0; // Só ataca se jogador estiver com a espada

    if (IsKeyDown(KEY_J)) { // Tecla J aciona o ataque

        int dx = 0, dy = 0;   // Direções do ataque
        float rotacao = 0;    // Rotação da espada

        // Define a direção e rotação conforme a direção do jogador
        switch (jogador->direcao) {
            case 'N': dy = -1; rotacao = 0.0f; break;
            case 'S': dy =  1; rotacao = 180.0f; break;
            case 'L': dx =  1; rotacao = 90.0f; break;
            case 'O': dx = -1; rotacao = 270.0f; break;
            default: return 0;
        }

        // A espada ataca até 3 células de distância
        for (int i = 1; i < 4; i++) {
            int celulaX = jogador->x + (i * dx); // Posição da célula atacada
            int celulaY = jogador->y + (i * dy);
            float destinoX = celulaX * TAM_CELULA;
            float destinoY = celulaY * TAM_CELULA + TAM_MENUJOGO;

            // Interrompe ataque se sair do mapa
            if (celulaY < 0 || celulaY >= LINHAS || celulaX < 0 || celulaX >= COLUNAS)
                break;

            // Interrompe ataque se houver parede
            if (mapa->celulas[celulaY][celulaX] == 'P')
                break;

            // Define as áreas da textura a desenhar
            Rectangle source = { 0.0f, 0.0f, (float)sprite.width, (float)sprite.height };
            Rectangle dest = {
                destinoX + TAM_CELULA / 2.0f, // Corrige origem para girar ao redor do centro
                destinoY + TAM_CELULA / 2.0f,
                TAM_CELULA,
                TAM_CELULA
            };
            Vector2 origin = { TAM_CELULA / 2.0f, TAM_CELULA / 2.0f };

            // Verifica colisão com todos os monstros
            for (int a = 0; a < qnt_monstros; a++) {
                if (celulaX == monstros[a].x && celulaY == monstros[a].y) {
                    if (monstros[a].ativo) {
                        monstros[a].ativo = false; // Monstro derrotado
                        jogador->pontuacao += monstros[a].pontuacao; // Ganha pontos
                        mapa->celulas[celulaY][celulaX] = ' '; // Remove o monstro do mapa
                        monstros_mortos++; // Contabiliza
                    }
                }
            }

            // Desenha a espada na célula atacada
            DrawTexturePro(sprite, source, dest, origin, rotacao, WHITE);
        }
    }

    return monstros_mortos; // Retorna quantos monstros foram mortos nesse ataque
}