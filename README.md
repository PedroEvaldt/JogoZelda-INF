# Zelda-INF

> Um jogo 2D estilo Zelda feito com a biblioteca [raylib](https://www.raylib.com/), como projeto final da disciplina de Algoritmos e Programação.

---

## 🎮 Sobre o Jogo

Zelda-INF é um jogo de aventura 2D no estilo top-down, onde o jogador explora mapas, coleta vidas, derrota monstros e avança por fases cada vez mais desafiadoras. O objetivo é sobreviver, vencer todas as fases e conquistar a maior pontuação possível.

---

## 🗂️ Estrutura do Projeto

- `main.c` — Lógica principal do jogo e controle de telas (menu, jogo, score, etc).
- `jogador.c/.h` — Inicialização, movimentação e desenho do jogador.
- `espada.c/.h` — Ataques e desenho da espada.
- `monstro.c/.h` — Inicialização, movimentação (com A*) e desenho dos monstros.
- `vida.c/.h` — Geração, desenho e coleta das vidas extras.
- `mapa.c/.h` — Leitura dos mapas `.txt` e renderização gráfica.
- `score.c/.h` — Sistema de ranking (Top 5) salvo em arquivo binário.
- `menuprincipal.c/.h` — Interface do menu inicial.
- `menujogo.c/.h` — Menu de pausa exibido durante o jogo.
- `barrastatus.c/.h` — HUD com informações como vidas, nível e score.
- `caminho.c/.h` — Algoritmo de caminho (A*) usado por monstros.
- `sprites/` — Imagens dos personagens, monstros, vida e itens.
- `Fontes/` — Fontes customizadas para textos do jogo.
- `mapas/` — Mapas do jogo em formato `.txt`.

---

## 🛠️ Como Compilar

### Requisitos:
- Compilador C (gcc, clang, MinGW etc)
- Biblioteca **raylib** instalada corretamente

### Exemplo de compilação (Linux):
```bash
gcc main.c mapa.c jogador.c monstro.c vida.c espada.c barrastatus.c score.c menujogo.c menuprincipal.c caminho.c -o zelda -lraylib -lm -ldl -lpthread
```

### Exemplo no Windows (com MinGW):
```bash
gcc main.c mapa.c jogador.c monstro.c vida.c espada.c barrastatus.c score.c menujogo.c menuprincipal.c caminho.c -o zelda.exe -lraylib -lopengl32 -lgdi32 -lwinmm
```

---

## 🎮 Controles

```text
W / A / S / D ou Setas  - Movimenta o jogador
J                      - Ataca com a espada
TAB                    - Abre o menu de pausa
C                      - Continuar jogo (no menu)
V                      - Voltar ao menu principal
S                      - Sair do jogo
SPACE                  - Confirmar / Avançar menus
BACKSPACE              - Apagar letra no nome
```

---

## 🗺️ Formato dos Mapas

Os mapas estão na pasta `mapas/` e usam caracteres ASCII para representar elementos:

| Símbolo | Significado       |
|---------|-------------------|
| `P`     | Parede            |
| Espaço  | Chão              |
| `M`     | Monstro comum     |
| `V`     | Vida extra        |
| `E`     | Espada            |
| `J`     | Jogador (início)  |

---

## 🏆 Pontuação e Ranking

- Cada monstro possui uma pontuação aleatória de 0 a 100.
- O ranking salva os 5 maiores scores no arquivo `highscores_ab.bin`.
- Ao alcançar um novo recorde, o jogador digita seu nome.

---

## 🧠 Lógica dos Monstros

- Os monstros perseguem o jogador se estiverem próximos (raio ≤ 20).
- O algoritmo A* (A-star) é usado para seguir o jogador evitando paredes.
- Caso o caminho seja bloqueado, o monstro se move aleatoriamente.

---

## 📸 Créditos Visuais

- Sprites e gráficos foram criados ou adaptados para uso educacional.
- Fontes utilizadas:
  - `PressStart2P.ttf` (estilo retrô)
  - `GAMEOVER.TTF` (para tela de fim de jogo)

---

## 👨‍💻 Autor

Este jogo foi desenvolvido como projeto final da disciplina de **Algoritmos e Programação**.

- **Nome do Aluno:** _[SEU NOME AQUI]_
- **Instituição:** _[NOME DA INSTITUIÇÃO]_
- **Disciplina:** Algoritmos e Programação

---

## 📜 Licença
