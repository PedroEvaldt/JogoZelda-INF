// #include "arma.h"
// #include "jogador.h"

// arma inicializarArma(Jogador *jogador){
//     jogador->arma.ativa = false;
//     jogador->jogador_sul = LoadTexture("sprites/(JOGADOR COM ARMA)")
//     jogador->jogador_norte = LoadTexture("sprites/(JOGADOR COM ARMA)")
//     jogador->jogador_leste = LoadTexture("sprites/(JOGADOR COM ARMA)")
//     jogador->jogador_oeste = LoadTexture("sprites/(JOGADOR COM ARMA)")
// }

// void atirarArma(arma *arma, Jogador *jogador, Monstro monstros[], qntmonstros, Mapa *mapa){
//     if (jogador->arma.ativa){
//         int x = jogador->x;
//         int y = jogador->y;
//         char direcao_bala = jogador->direcao;
//         switch (jogador.direcao){
//             case 'N': 
//             jogador->arma.bala_norte = LoadTexture("sprites/bala-norte.png");
//             for (int i = 0; i < qntmonstros; i++) {
//                 while (!((x == monstros[i].x && y == monstros[i].y) || mapa->celular[y][x] == 'P')) {
//                     y--;
//                     Rectangle source = { 0.0f, 0.0f, (float)jogador->arma.bala_norte.width, (float)jogador->arma.bala_norte.height };
//                     Rectangle dest = { x * TAM_CELULA, y * TAM_CELULA + TAM_MENUJOGO, TAM_CELULA, TAM_CELULA };
//                     Vector2 origin = { 0.0f, 0.0f };
//                     DrawTexturePro(jogador->arma.bala_norte, source, dest, origin, 0.0f, WHITE);
//                     }
//                 }
//             }
            
//             break;
//             case 'S':
//             sprite = jogador->arma.bala_sul = LoadTexture("sprites/bala-sul.png");
//             for (int i = 0; i < qntmonstros; i++) {
//                 while (!((x == monstros[i].x && y == monstros[i].y) || mapa->celular[y][x] == 'P')) {
//                     y++;
//                     Rectangle source = { 0.0f, 0.0f, (float)jogador->arma.bala_sul.width, (float)jogador->arma.bala_sul.height };
//                     Rectangle dest = { x * TAM_CELULA, y * TAM_CELULA + TAM_MENUJOGO, TAM_CELULA, TAM_CELULA };
//                     Vector2 origin = { 0.0f, 0.0f };
//                     DrawTexturePro(jogador->arma.bala_sul, source, dest, origin, 0.0f, WHITE);
//                     }
//                 }
//             }
            
//             break;
            
//             case 'L': 
//             jogador->arma.bala_leste = LoadTexture("sprites/bala-leste.png");
//             for (int i = 0; i < qntmonstros; i++) {
//                 while (!((x == monstros[i].x && y == monstros[i].y) || mapa->celular[y][x] == 'P')) {
//                     x++;
//                     Rectangle source = { 0.0f, 0.0f, (float)jogador->arma.bala_leste.width, (float)jogador->arma.bala_leste.height };
//                     Rectangle dest = { x * TAM_CELULA, y * TAM_CELULA + TAM_MENUJOGO, TAM_CELULA, TAM_CELULA };
//                     Vector2 origin = { 0.0f, 0.0f };
//                     DrawTexturePro(jogador->arma.bala_leste, source, dest, origin, 0.0f, WHITE);
//                     }
//                 }
            
//             break;
//             case 'O': 
//             jogador->arma.bala_oeste = LoadTexture("sprites/bala-oeste.png");
//             for (int i = 0; i < qntmonstros; i++) {
//                 while (!((x == monstros[i].x && y == monstros[i].y) || mapa->celular[y][x] == 'P')) {
//                     x--;
//                     Rectangle source = { 0.0f, 0.0f, (float)jogador->arma.bala_oeste.width, (float)jogador->arma.bala_oeste.height };
//                     Rectangle dest = { x * TAM_CELULA, y * TAM_CELULA + TAM_MENUJOGO, TAM_CELULA, TAM_CELULA };
//                     Vector2 origin = { 0.0f, 0.0f };
//                     DrawTexturePro(jogador->arma.bala_oeste, source, dest, origin, 0.0f, WHITE);
//                     }
//                 }
//             break;
            
//             }