#include "score.h"

void salvarScore(const char *nome, int score) {
    FILE *arquivo = fopen(ARQUIVO_SCORE, "ab");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo de scores.\n");
        return;
    }
    Scores novo;
    strcpy(novo.nome, nome);
    novo.pontuacao = score; 

    fwrite(&novo,sizeof(Scores),1,arquivo);
    fclose(arquivo);
}

int comparar(const void *a, const void *b) {
    return ((Scores *)b)->pontuacao - ((Scores *)a)->pontuacao;
}

void mostrarTop5() {
    FILE *arquivo = fopen(ARQUIVO_SCORE, "rb");
    if (!arquivo){ 
        printf("Erro ao abrir o arquivo de scores.\n");
        return;
    }

    Scores scores[MAX_SCORES];
    int count = 0;

    while (count < MAX_SCORES && fread(&scores[count], sizeof(Scores), 1, arquivo) == 1) 
        count++;

    fclose(arquivo);

    // Ordena do maior para o menor
    qsort(scores, count, sizeof(Scores), comparar);

    // Exibe os 5 primeiros
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("TOP 5 SCORES", 420, 100, 40, WHITE);

        for (int i = 0; (i < count) && (i < 5); i++) {
            char buffer[100];
            sprintf(buffer, "%d. %s = %d", i + 1, scores[i].nome, scores[i].pontuacao);
            DrawText(buffer, 400, 160 + i * 40, 30, WHITE);
        }

        DrawText("Pressione ESPACO para voltar", 400, 600, 20, RAYWHITE);
        EndDrawing();

        if(IsKeyPressed(KEY_SPACE))
                break;
    }
}