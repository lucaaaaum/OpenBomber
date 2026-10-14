# OpenBomber

OpenBomber é um jogo 2D no estilo Bomberman, feito em C++ com OpenGL para a disciplina de Fundamentos de Processamento Gráfico.

🎬 **Demo:** https://www.youtube.com/watch?v=JTqJu6r27r0

## Como funciona

Você controla um personagem num mapa de 19×19 quadrados, visto de cima.

- **O mapa** tem uma borda de paredes que não quebram, pilares fixos espalhados em grade e paredes quebráveis colocadas aleatoriamente. O canto onde o jogador começa fica sempre livre.
- **Bombas:** aperte Espaço para soltar uma bomba (uma de cada vez). Depois de 3 segundos ela explode em forma de cruz, alcançando um quadrado para cada lado. O fogo dura 1 segundo, destrói paredes quebráveis e é barrado pelas paredes fixas.
- **Inimigos:** cinco inimigos aparecem em lugares vazios do mapa. Eles andam em linha reta e dão meia-volta quando batem numa parede ou numa bomba.
- **Morte:** o fogo mata tanto os inimigos quanto o jogador, e encostar num inimigo também mata o jogador. Quando o jogador morre, a partida recomeça com um mapa novo.

### Controles

| Tecla | Ação |
| --- | --- |
| W A S D ou setas | Andar |
| Espaço | Soltar bomba |
| Esc | Sair |

## Baixar e jogar

Há um binário pronto para baixar na página de [releases do GitHub](https://github.com/lucaaaaum/OpenBomber/releases).

As imagens do jogo ficam na pasta `assets/`, que precisa estar ao lado do executável.

## Compilando

O projeto foi pensado para ser compilado com [Nix](https://nixos.org/), que baixa e prepara todas as dependências sozinho. Mas também dá para compilar só com GCC e CMake.

### Com Nix (recomendado)

Na raiz do repositório:

```sh
nix run                # compila e roda o jogo
nix build              # só compila; o executável fica em ./result/bin/openbomber
nix develop            # abre um terminal com todas as ferramentas de desenvolvimento
```

O pacote gerado pelo Nix já leva as imagens junto, então o `nix run` funciona de qualquer pasta.

Também é possível gerar uma versão para Windows a partir do Linux:

```sh
nix build .#windows -o result-windows
```

A pasta `result-windows/bin/` fica com o `openbomber.exe`, as DLLs de que ele precisa e a pasta `assets/`. Para levar tudo para um computador com Windows, copie com `cp -rL` (o `-L` copia os arquivos de verdade em vez de atalhos).

### Com GCC e CMake

Você vai precisar de:

- GCC (com suporte a C++17) e CMake 3.24 ou mais novo;
- as bibliotecas **GLFW** e **GLM**, instaladas pelo gerenciador de pacotes do seu sistema. Se elas não estiverem instaladas, o CMake tenta baixá-las sozinho, mas aí o GLFW precisa dos pacotes de desenvolvimento do X11 e do Wayland do seu sistema para compilar;
- o arquivo [`stb_image.h`](https://github.com/nothings/stb/blob/master/stb_image.h), que serve para carregar as imagens. Baixe-o e diga ao compilador onde ele está (por exemplo com a variável `CPATH`).

Depois, na raiz do repositório:

```sh
CPATH=/pasta/onde/esta/o/stb cmake -B build
CPATH=/pasta/onde/esta/o/stb cmake --build build
./build/openbomber
```

Rode o jogo sempre a partir da raiz do repositório, para que ele encontre a pasta `assets/`.

## Licença

MIT. Veja o arquivo [LICENSE](LICENSE).
