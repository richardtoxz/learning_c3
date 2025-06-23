# Projeto de Jogo de Cartas em C: Pedra, Papel e Tesoura - UCB DUEL

## Sumario

1.  [Visão Geral do Projeto](#1-visão-geral-do-projeto)
2.  [O Jogo e Suas Regras](#2-o-jogo-e-suas-regras)
3.  [Funcionalidades Implementadas](#3-funcionalidades-implementadas)
4.  [Instruções de Compilação e Execução](#4-instruções-de-compilação-e-execução)
5.  [Arquitetura e Organização do Código](#5-arquitetura-e-organização-do-código)
6.  [Detalhes Técnicos](#6-detalhes-técnicos)
7.  [Alunos](#7-alunos)

-----

### 1\. Visão Geral do Projeto

Este projeto foi desenvolvido como parte dos requisitos avaliativos da disciplina de Estrutura de Dados, com o objetivo de aplicar conceitos fundamentais e avançados da linguagem C na criação de um jogo de cartas funcional e robusto. O jogo implementado é uma versão estratégica do clássico "Pedra, Papel e Tesoura", onde sorte, gerenciamento de mão e tática se encontram.

### 2\. O Jogo e Suas Regras

  * **Nome do Jogo:** Pedra, Papel e Tesoura - UCB DUEL

#### Breve Descrição das Regras

O jogo é uma disputa por turnos entre o jogador e uma CPU. Ambos recebem uma mão de cartas e devem usá-las para vencer rodadas e acumular pontos.

  * **Objetivo:** Ser o primeiro a atingir o número de pontos definido no modo de jogo (ex: 2 pontos em uma "Melhor de 3").
  * **O Baralho:** Composto por um número configurável de cartas, contendo um terço de cada tipo: Pedra, Papel e Tesoura.
  * **A Mão:** Cada jogador inicia e mantém uma mão fixa de 5 cartas.
  * **A Rodada:**
    1.  O jogador escolhe uma carta de sua mão para jogar.
    2.  A CPU, simultaneamente, escolhe uma carta aleatória de sua própria mão.
    3.  As cartas são comparadas seguindo a regra universal: Pedra quebra Tesoura, Tesoura corta Papel, e Papel cobre Pedra.
    4.  O vencedor da rodada marca 1 ponto. Em caso de empate, ninguém pontua.
    5.  Após a jogada, ambos os jogadores compram uma nova carta do baralho para repor a mão.
  * **Fim de Jogo:** A partida termina quando um dos competidores alcança a pontuação necessária para a vitória.

### 3\. Funcionalidades Implementadas

  * **Menu Principal Interativo:** Permite ao jogador iniciar uma nova partida, acessar as configurações, visualizar o placar geral ou sair do jogo.
  * **Sistema de Configurações:** Oferece flexibilidade ao jogador, que pode alterar:
      * **Modo de Jogo:** Melhor de 1, 3, 5 ou 7.
      * **Tamanho do Baralho:** Para partidas mais longas ou curtas.
  * **Placar Persistente:** As vitórias e derrotas do jogador são salvas no arquivo `placar.txt`, mantendo um histórico entre as sessões de jogo.
  * **Lógica de CPU:** A CPU possui uma lógica simples e aleatória, oferecendo um desafio dinâmico a cada partida.

### 4\. Instruções de Compilação e Execução

#### Requisitos

  * Um compilador C (como GCC, Clang).
  * Um terminal (CMD ou PowerShell no Windows, Bash no Linux/macOS).

#### Compilação

Navegue até o diretório raiz do projeto pelo terminal e execute o seguinte comando:

```bash
gcc -o jogo *.c
```

Este comando compilará todos os arquivos `.c` do projeto e gerará um executável chamado `jogo` (ou `jogo.exe` no Windows).

#### Execução

  * **No Linux :**
    ```bash
    ./jogo
    ```
  * **No Windows (CMD / PowerShell):**
    ```bash
    .\jogo.exe
    ```

### 5\. Arquitetura e Organização do Código

O projeto foi estruturado de forma altamente modular para promover encapsulamento, reutilização de código e facilidade de manutenção. Cada módulo tem uma responsabilidade bem definida, separada em pares de arquivos `.h` (interface pública) e `.c` (implementação privada).

  * **`main.c`**
      * **Responsabilidade:** Ponto de entrada do programa. Gerencia o loop do menu principal e coordena as chamadas para os outros módulos.
  * **`jogo.c / jogo.h`**
      * **Responsabilidade:** Orquestra toda a lógica e o fluxo de uma partida.
      * **Funções Principais:** `iniciar_partida()`, `comparar_cartas()`.
  * **`cartas.c / cartas.h`**
      * **Responsabilidade:** Gerenciamento de todas as operações relacionadas às cartas e listas encadeadas (baralho, mão, descarte).
      * **Funções Principais:** `criar_baralho()`, `embaralhar()`, `remover_carta_por_posicao()`, `liberar_lista()`.
  * **`placar.c / placar.h`**
      * **Responsabilidade:** Manipulação do arquivo de placar, incluindo leitura e gravação dos dados de vitórias e derrotas.
      * **Funções Principais:** `ler_placar()`, `salvar_placar()`, `exibir_winrate()`.
  * **`configuracoes.c / configuracoes.h`**
      * **Responsabilidade:** Apresenta e gerencia o menu de configurações, permitindo ao usuário alterar as regras do jogo.
      * **Funções Principais:** `menu_configuracoes()`.
  * **`utils.c / utils.h`**
      * **Responsabilidade:** Encapsula funcionalidades dependentes do sistema operacional para garantir a portabilidade do código.
      * **Funções Principais:** `limpar_tela()`, `pausar_tela()`, `ler_inteiro_seguro()`.

### 6\. Detalhes Técnicos

  * **Gerenciamento Seguro de Memória:** Todas as alocações dinâmicas com `malloc` são verificadas para previnir falhas. A memória é sistematicamente liberada com `free` ao final de seu uso, evitando vazamentos de memória.
  * **Entrada de Dados Segura:** Foi implementada uma função `ler_inteiro_seguro()` que utiliza `fgets` para ler a entrada do usuário. Isso previne vulnerabilidades de estouro de buffer (buffer overflow), comuns no uso direto de `scanf`.
  * **Design Modular e Baixo Acoplamento:** A separação em módulos independentes torna o código mais fácil de entender, testar e expandir.
  * **Código Portátil:** Com o módulo `utils`, o jogo compila e roda sem modificações em diferentes sistemas operacionais (Windows e Linux).

### 7\. Alunos

  * **RICHARD RODRIGUES**
  * **PABLO HENRIQUE DOURADO**
  * **RUAN PABLO**
  * **DANIEL SHARIFI**