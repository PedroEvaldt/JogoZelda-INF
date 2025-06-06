#include "score.h"

void salvarScore(const char *nome, int score) {
    FILE *arquivo = fopen(ARQUIVO_SCORE, "a");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de scores.\n");
        return;
    }
    fprintf(arquivo, "%s %d\n", nome, score);
    fclose(arquivo);
}

int comparar(const void *a, const void *b) {
    return ((Scores *)b)->pontuacao - ((Scores *)a)->pontuacao;
}

int mostrarTop5() {
    FILE *arquivo = fopen(ARQUIVO_SCORE, "r");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo de scores.\n");
        return 0;
    }

    Scores Scores[MAX_SCORES];
    int count = 0;

    while (fscanf(arquivo, "%20s %d", Scores[count].nome, &Scores[count].pontuacao) == 2 && count < MAX_SCORES)
        count++;

    fclose(arquivo);

    qsort(Scores, count, sizeof(Scores), comparar);
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("TOP 5 SCORES", 450, 100, 40, WHITE);
        for (int i = 0; i < count && i < 5; i++) {
            char buffer[100];
            sprintf(buffer, "%d. %s = %d", i + 1, Scores[i].nome, Scores[i].pontuacao);
            DrawText(buffer, 400, 160 + i * 40, 30, WHITE);
        }
        DrawText("Pressione ESPACO para voltar", 400, 400, 20, RAYWHITE);
        EndDrawing();

        if (IsKeyPressed(KEY_SPACE))
            return 1;
    }

    return 0;
}