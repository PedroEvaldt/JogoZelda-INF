#include "raylib.h"
#include "mapa.h"

// Função que carrega o mapa de uma fase específica
Mapa carregarMapa(int fase) {
    Mapa mapa;
    char nomeArquivo[20];

    // Monta o nome do arquivo de texto com base na fase (ex: mapa01.txt)
    sprintf(nomeArquivo, "mapas/mapa%02d.txt", fase);

    // Tenta abrir o arquivo para leitura
    FILE *fp = fopen(nomeArquivo, "r");

    // Se o arquivo não for encontrado, preenche o mapa com espaços vazios
    if (!fp) {
        for (int i = 0; i < LINHAS; i++)
            for (int j = 0; j < COLUNAS; j++)
                mapa.celulas[i][j] = ' ';
        return mapa;
    }

    // Lê o conteúdo do arquivo e preenche as células do mapa
    for (int i = 0; i < LINHAS; i++)
        for (int j = 0; j < COLUNAS; j++) {
            int ch;

            // Ignora quebras de linha e caracteres extras
            do {
                ch = fgetc(fp);
            } while (ch == '\n' || ch == '\r');

            // Armazena o caractere como conteúdo da célula
            mapa.celulas[i][j] = (char)ch;
        }

    // Fecha o arquivo após leitura
    fclose(fp);

    // Carrega as texturas do mapa (parede, espada, vida, chão)
    mapa.parede = LoadTexture("sprites/parede.png");
    mapa.espada = LoadTexture("sprites/espada.png");
    mapa.vida = LoadTexture("sprites/vida.png");
    mapa.chao = LoadTexture("sprites/background-generico.png");

    return mapa;
}

// Função que desenha todas as células do mapa na tela
void desenharMapa(Mapa mapa) {
    Texture2D sprite;

    // Percorre todas as células
    for (int i = 0; i < LINHAS; i++) {
        for (int j = 0; j < COLUNAS; j++) {

            // Escolhe qual textura desenhar com base no caractere da célula
            switch (mapa.celulas[i][j]) {
                case 'P': sprite = mapa.parede; break; // Parede
                case ' ': sprite = mapa.chao; break;   // Espaço vazio (chão)
                default:  sprite = mapa.chao; break;   // Qualquer outro, trata como chão
            }

            // Define a parte da textura a ser usada (imagem completa)
            Rectangle source = {0.0f, 0.0f, (float)sprite.width, (float)sprite.height};

            // Calcula a posição onde a textura será desenhada
            Rectangle dest = {
                j * TAM_CELULA,
                i * TAM_CELULA + TAM_MENUJOGO, // Adiciona espaço da barra superior
                TAM_CELULA,
                TAM_CELULA
            };

            // Origem da textura (canto superior esquerdo)
            Vector2 origin = { 0.0f, 0.0f };

            // Desenha a célula usando a textura apropriada
            DrawTexturePro(sprite, source, dest, origin, 0.0f, WHITE);
        }
    }
}

// Função que libera da memória todas as texturas do mapa
void descarregarTexturasMapa(Mapa *mapa) {
    UnloadTexture(mapa->parede);
    UnloadTexture(mapa->espada);
    UnloadTexture(mapa->vida);
    UnloadTexture(mapa->chao);
}