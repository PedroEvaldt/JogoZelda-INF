#include "score.h"

// Define as dimensões da janela utilizadas na exibição do top 5
#define LARGURA_TELA 1200
#define ALTURA_TELA 860

// Função de comparação usada para ordenar os scores (ordem decrescente)
int comparar(const void *a, const void *b) {
    return ((Scores *)b)->pontuacao - ((Scores *)a)->pontuacao;
}

// Salva um novo score no arquivo binário de ranking
void salvarScore(const char *nome, int score) {
    // Lê todos os scores existentes do arquivo
    FILE *arquivo = fopen(ARQUIVO_SCORE, "rb");

    Scores scores[MAX_SCORES + 1]; // +1 para permitir adicionar o novo score
    int count = 0;

    // Lê os scores do arquivo (se o arquivo existir)
    if (arquivo != NULL) {
        while (count < MAX_SCORES + 1 && fread(&scores[count], sizeof(Scores), 1, arquivo) == 1)
            count++;
        fclose(arquivo);
    }

    // Adiciona o novo score no final do array
    if (count < MAX_SCORES + 1) {
        strncpy(scores[count].nome, nome, MAX_NOME - 1); // Copia o nome do jogador
        scores[count].nome[MAX_NOME - 1] = '\0'; // Garante que haverá fim de string
        scores[count].pontuacao = score;
        count++;
    }

    // Ordena os scores do maior para o menor usando qsort e a função comparar
    qsort(scores, count, sizeof(Scores), comparar);

    // Abre o arquivo para escrita (sobrescreve o conteúdo)
    arquivo = fopen(ARQUIVO_SCORE, "wb");
    if (!arquivo) {
        fprintf(stderr, "Erro ao abrir arquivo para escrita!\n");
        return;
    }

    // Escreve apenas os 5 melhores scores de volta no arquivo
    for (int i = 0; i < count && i < MAX_SCORES; i++) {
        fwrite(&scores[i], sizeof(Scores), 1, arquivo);
    }

    fclose(arquivo);
}

// Mostra os 5 melhores scores na tela com Raylib
void mostrarTop5() {
    FILE *arquivo = fopen(ARQUIVO_SCORE, "rb");

    // Se não conseguir abrir o arquivo, exibe uma mensagem de erro
    if (!arquivo){ 
        printf("Erro ao abrir o arquivo de scores.\n");
        return;
    }

    // Carrega a fonte customizada
    Font fonte = LoadFont("Fontes/PressStart2P.ttf");

    Scores scores[MAX_SCORES];
    int count = 0;

    // Lê os scores do arquivo
    while (count < MAX_SCORES && fread(&scores[count], sizeof(Scores), 1, arquivo) == 1) 
        count++;

    fclose(arquivo);

    // Ordena os scores para garantir ordem correta
    qsort(scores, count, sizeof(Scores), comparar);

    // Loop de renderização da tela de ranking
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Título do ranking
        const char *titulo = "TOP 5 SCORES";
        float espacamento = 1.0f;
        float tamanhoFonteTitulo = 40;
        Vector2 tamTextoTitulo = MeasureTextEx(fonte, titulo, tamanhoFonteTitulo, espacamento);
        DrawTextEx(fonte, titulo, (Vector2){(LARGURA_TELA - tamTextoTitulo.x) / 2.0f, 80}, tamanhoFonteTitulo, espacamento, WHITE);

        // Exibe os 5 melhores scores
        for (int i = 0; (i < count) && (i < 5); i++) {
            char buffer[100];
            sprintf(buffer, "%d. %s = %d", i + 1, scores[i].nome, scores[i].pontuacao);

            float tamanhoFonteScore = 25;
            Vector2 tamTextoScore = MeasureTextEx(fonte, buffer, tamanhoFonteScore, espacamento);
            DrawTextEx(fonte, buffer, (Vector2){(LARGURA_TELA - 430) / 2.0f, 180 + i * 50}, tamanhoFonteScore, espacamento, RAYWHITE);
        }

        // Instrução para voltar
        const char *voltar = "Pressione ESPACO para voltar";
        float tamanhoFonteVoltar = 20;
        Vector2 tamTextoVoltar = MeasureTextEx(fonte, voltar, tamanhoFonteVoltar, espacamento);
        DrawTextEx(fonte, voltar, (Vector2){(LARGURA_TELA - tamTextoVoltar.x) / 2.0f, 700}, tamanhoFonteVoltar, espacamento, GRAY);

        EndDrawing();

        // Se pressionar espaço, sai do ranking
        if (IsKeyPressed(KEY_SPACE)) break;
    }

    // Libera a fonte da memória
    UnloadFont(fonte);
}

// Verifica se o score atual é um novo recorde
bool NovoRecorde(int scoreAtual) {
    FILE *arquivo = fopen(ARQUIVO_SCORE, "rb");

    // Se não houver arquivo, é um novo recorde automaticamente
    if (!arquivo) {
        return true;
    }

    Scores scores[MAX_SCORES];
    int count = 0;

    // Lê os scores atuais
    while (count < MAX_SCORES && fread(&scores[count], sizeof(Scores), 1, arquivo) == 1) {
        count++;
    }

    fclose(arquivo);

    // Verifica se o score atual é maior que algum já salvo
    for (int i = 0; i < count; i++){
        if (scoreAtual > scores[i].pontuacao) {
            return true;
        }        
    }

    // Se ainda houver espaço no ranking, também é um novo recorde
    return (count < MAX_SCORES);
}