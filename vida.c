#include "raylib.h"
#include "vida.h"

// Função para inicializar as vidas no mapa
int inicializarVida(Mapa mapa, Vida vidas[]) {
    int contador = 0;

    // Carrega a textura da vida a partir do arquivo de sprite
    Texture2D vida_textura = LoadTexture("sprites/vida.png");

    // Percorre todas as células do mapa
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {

            // Verifica se há uma vida nesta célula do mapa (marcada com 'V')
            if (mapa.celulas[i][j] == 'V') {

                // Armazena a posição da vida
                vidas[contador].x = j;
                vidas[contador].y = i;

                // Marca a vida como ativa para ser desenhada e utilizada no jogo
                vidas[contador].ativa = true;

                // Atribui a textura carregada à vida
                vidas[contador].vida_textura = vida_textura;

                // Avança o contador de vidas
                contador++;
            }
        }
    }

    // Retorna o total de vidas inicializadas
    return contador;
}

// Função para desenhar as vidas na tela
void desenharVida(Vida vidas[], int qtd) {
    for (int i = 0; i < qtd; i++) {

        // Apenas desenha se a vida estiver ativa
        if (vidas[i].ativa) {
            Texture2D sprite = vidas[i].vida_textura;

            // Define a área da textura que será usada (nesse caso, a imagem toda)
            Rectangle source = { 0.0f, 0.0f, (float)sprite.width, (float)sprite.height };

            // Define onde a vida será desenhada na tela, convertendo da posição no mapa para pixels
            Rectangle dest = {
                vidas[i].x * TAM_CELULA,
                vidas[i].y * TAM_CELULA + TAM_MENUJOGO, // Ajusta por causa da barra de menu
                TAM_CELULA,
                TAM_CELULA
            };

            // Origem da rotação (não usada aqui)
            Vector2 origin = { 0.0f, 0.0f };

            // Desenha a textura da vida na tela com as transformações definidas
            DrawTexturePro(sprite, source, dest, origin, 0.0f, WHITE);
        }
    }
}