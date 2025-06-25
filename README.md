# Zelda-INF

> Um jogo 2D estilo Zelda feito com a biblioteca [raylib](https://www.raylib.com/), como projeto final da disciplina de Algoritmos e Programação na UFRGS.

---

## 🎮 Sobre o Jogo

Zelda-INF é um jogo de aventura 2D com visão top-down, ambientado em um cenário de apocalipse zumbi. O jogador deve explorar diferentes mapas, coletar vidas para sobreviver, e encontrar uma espada para derrotar todos os monstros e avançar pelas fases. O objetivo principal é completar as 10 fases, que aumentam em dificuldade progressivamente, e alcançar a maior pontuação possível. Para progredir para a próxima fase, é mandatório que o jogador colete a espada e elimine todos os monstros presentes no mapa atual.

---

## 🗂️ Estrutura do Projeto

O projeto é modularizado para facilitar o desenvolvimento e a manutenção, com arquivos `.c` e `.h` dedicados a funcionalidades específicas:

- `main.c` — Contém a lógica principal do jogo, gerenciando o fluxo entre as diferentes telas (menu, jogo, score, game over).
- `jogador.c/.h` — Responsável pela inicialização, movimentação e renderização do personagem principal.
- `espada.c/.h` — Implementa a mecânica de ataque com a espada e seu desenho na tela.
- `monstro.c/.h` — Inicialização, movimentação (com A*) e desenho dos monstros.
- `vida.c/.h` — Geração, desenho e coleta das vidas extras.
- `mapa.c/.h` — Lida com a leitura dos arquivos `.txt` que definem os mapas e sua renderização gráfica.
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

Para compilar e executar o Zelda-INF, você precisará de um compilador C e da biblioteca `raylib` instalada.

### Requisitos:
- Compilador C (GCC, Clang, MinGW, etc.)
- Biblioteca **raylib** (instalação e configuração prévia são necessárias)

### Exemplo de Compilação (Linux):
```bash
gcc main.c mapa.c jogador.c monstro.c vida.c espada.c barrastatus.c score.c menujogo.c menuprincipal.c caminho.c -o zelda -lraylib -lm -ldl -lpthread

---

## 🎮 Controles

| Tecla                 | Ação                                      |
|-----------------------|-------------------------------------------|
| `W / A / S / D`, setas| Movimenta o jogador.                   |
| `J`                   | Ataca com a espada.                       |
| `TAB`                 | Abre/Fecha o menu de pausa durante o jogo.|
| `C`                   | Continua o jogo (no menu de pausa).       |
| `V`                   | Volta ao menu principal (menu de pausa).  |
| `S`                   | Sai do jogo.                              |
| `SPACE`               | Confirma / Avança telas de menu.          |
| `BACKSPACE`           | Apaga o último caractere (tela de nome).  |

---

## 🗺️ Formato dos Mapas

Os mapas do jogo estão localizados na pasta `mapas/` e são arquivos de texto (`.txt`) que utilizam caracteres ASCII para representar os elementos do cenário e dos objetos:

| Símbolo | Significado        |
|---------|--------------------|
| `P`     | Parede             |
| ` `     | Chão (espaço vazio) |
| `M`     | Monstro comum      |
| `V`     | Vida extra         |
| `E`     | Espada             |
| `J`     | Posição inicial do jogador |

Exemplos de mapas:
* `mapa01.txt`
* `mapa02.txt`
* `mapa03.txt`
* `mapa04.txt`
* `mapa05.txt`
* `mapa06.txt`
* `mapa07.txt`
* `mapa08.txt`
* `mapa09.txt`
* `mapa10.txt`

---

## 🏆 Pontuação e Ranking

- Cada monstro derrotado contribui com uma pontuação aleatória entre 0 e 100 pontos para o jogador.
- O jogo mantém um ranking dos 5 maiores scores, salvos persistentemente no arquivo `highscores_ab.bin`.
- Se um jogador alcançar um novo recorde, ele será solicitado a digitar seu nome para registro no ranking.

---

## 🧠 Lógica dos Monstros

- Os monstros possuem uma lógica de perseguição: eles perseguem o jogador ativamente se estiverem dentro de um raio de 20 unidades.
- Para encontrar o melhor caminho até o jogador e evitar obstáculos como paredes, os monstros utilizam o algoritmo de busca de caminho A\* (A-star).
- Caso o caminho para o jogador esteja bloqueado ou fora do raio de perseguição, o monstro se move aleatoriamente.
- Ao colidir com o jogador, os monstros causam dano e o empurram um bloco na direção oposta ao contato (efeito de "knockback").

---

## 📸 Créditos Visuais

- Todos os sprites e elementos gráficos foram criados ou adaptados especificamente para uso educacional neste projeto.
- Fontes tipográficas utilizadas:
    - `PressStart2P.ttf`: Usada para o estilo retrô dos textos do jogo.
    - `GAMEOVER.TTF`: Aplicada na tela de fim de jogo.

---

## 👨‍💻 Autores

Este jogo foi desenvolvido como projeto final para a disciplina de **Algoritmos e Programação** na **UFRGS**.

- **Pedro Evaldt**
- **Alexandre Raczinoski**

---