JogoZelda-INF
Este projeto é uma recriação simplificada do clássico jogo The Legend of Zelda, desenvolvido em linguagem C utilizando a biblioteca gráfica raylib. O objetivo é oferecer uma experiência de aprendizado em desenvolvimento de jogos 2D, abordando conceitos como movimentação de personagens, combate, gerenciamento de vida e carregamento de mapas.

🧑‍💻 Desenvolvedores
Pedro Evaldt

Alexandre

🎮 Funcionalidades
Movimentação do personagem principal em quatro direções.

Sistema de combate com espada.

Inimigos com comportamento simples.

Gerenciamento de pontos de vida.

Carregamento de mapas a partir de arquivos .txt.

Renderização de sprites para personagens e elementos do cenário.
GitHub Docs

🗂️ Estrutura do Projeto
O projeto está organizado da seguinte forma:

bash
Copiar
Editar

JogoZelda-INF/
├── .vscode/             # Configurações do Visual Studio Code
├── sprites/             # Imagens e sprites utilizados no jogo
├── espada.c/.h          # Lógica e definições da espada
├── jogador.c/.h         # Lógica e definições do jogador
├── monstro.c/.h         # Lógica e definições dos inimigos
├── vida.c/.h            # Gerenciamento dos pontos de vida
├── mapa.c/.h            # Carregamento e renderização do mapa
├── mapa01.txt           # Arquivo de texto representando o mapa do jogo
├── main.c               # Função principal que inicia o jogo
├── zelda.exe            # Executável do jogo (para Windows)
└── .gitignore           # Arquivo para ignorar arquivos e pastas no Git
🚀 Como Executar
Pré-requisitos:

Instale a biblioteca raylib em seu sistema.

Tenha um compilador C instalado (como gcc).

Compilação:

No terminal, navegue até o diretório do projeto e execute:

css
Copiar
Editar
gcc main.c jogador.c espada.c monstro.c vida.c mapa.c -o zelda -lraylib -lm -lpthread -ldl -lrt -lX11
Execução:

Após a compilação bem-sucedida, execute o jogo com:

bash
Copiar
Editar
./zelda
Nota: Se estiver utilizando o Windows, você pode executar diretamente o arquivo zelda.exe.

📝 Controles
Setas direcionais: Movimentação do personagem

Espaço: Ataque com a espada

Esc: Sair do jogo

📄 Licença
Este projeto é de código aberto e está licenciado sob os termos da MIT License.
