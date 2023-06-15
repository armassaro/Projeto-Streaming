#ifndef projetostreaming
#define projetostreaming

#include <stdio.h>  //bibliotecas que serão usadas no código
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdint.h>
#include <time.h>

typedef struct {

    int id;

    char Nome[60];
    char Genero[31];
    int Classificacao;
    char Plataforma[13];
    int QuantidadeTemporadas;
    int QuantidadeEpisodiosTotais;
    int *QuantidadeEpisodiosPorTemporada;
    int DuracaoMediaEpisodios;

} Serie;

Serie *serie; 

int QuantidadeSeries = 259;

typedef struct {

    char Nome[31];
    int EpisodiosPendentes;
    int UltimoEpisodio;
    int UltimaTemporada;

} Historico;

Historico *historico;

FILE *arquivotexto;

FILE *arquivobinSeries;  //ponteiro que vai apontar para o arquivo binário criado após a primeira execução do código

FILE *arquivobinHistorico;

char *recebeChar;
int recebeInt;

char *StringAux;
int IntAux;
int IndiceSerieEscolhida;

WINDOW *borda;

WINDOW *MenuOpcoes;

int yterminal, xterminal;  //variáveis que guardam as dimensões máximas do terminal

int yborda, xborda;  //variáveis que guardam as dimensões da janela onde é desenhada a borda

unsigned int OpcoesMin, OpcoesMax;

// a logo foi separada por strings e sem struct por conta de problemas na programação
char *stringlogopt1 = "  __                                                             \n";
char *stringlogopt2 = " (_ _|_ ._ _   _. ._ _  o ._   _    |\\/|  _. ._   _.  _   _  ._ \n";
char *stringlogopt3 = " __) |_ | (/_ (_| | | | | | | (_|   |  | (_| | | (_| (_| (/_ |   \n";
char *stringlogopt4 = "                               _|                     _|         \n";

void MensagemBoasVindas();  //função utilizada em projetostreaming.c, com animações d emensagem de

//funções de menusecundario.c
// void MenuSecundario();
// void CadastrarSerie();
// void AlterarSerie();
// void RemoverSerie();
// void ListaSerie();
// void ListarPorGenero();
// void PesquisaSerie();

#endif 

/* COISAS NECESSÁRIAS PARA O PROGRAMA: 
- Menu com todas as opções disponíveis, sendo essas:

     + Busca por Gênero
     + Cadastro, Listagem, pesquisa, alteração e exclusão de itens tanto na struct de séries quanto an de histórico

- Mensagem de boas-vindas, quando não houver arquivo que armazene os dados das séries e histórico
- Carregar o arquivo com os dados das séries na primeira execução do programa, evitando o carregamento do mesmo quando for aberto uma outra vez
- Salva os dados lidos do arquivo de texto em um novo arquivo binário para que ele possa ser lido nas próximas vezes
*/

/* EXPLICAÇÃO DA BIBLIOTECA DE INTERFACE GRÁFICA -> A biblioteca destinada à interface gráfica ncurses.h produz uma interface gráfica a partir do terminal onde o código está sendo executado. A biblioteca, assim como
em uma interface gráfica normal, funciona a partir de janelas, mas no caso do ncurses as janelas são imaginárias e existentes dentro do terminal, onde se pode dimensionar
as janelas a partir da resolução disponível no terminal, obtida pela função getmaxyx().
As seguintes funções são as principais e mais usadas no código:

    + mvprintw() = printa uma string dada a localização da janela do terminal
    + initscr() = inicia o modo ncurses, é essencial para o início do funcionamento da interface
    + endwin() = fecha a janela principal e fecha o modo ncurses
    + clear() = limpa a janela principal
    + refresh() = atualiza a janela principal, é responsável por fazer com que o texto das funções de print e outras funções relacionadas efetivamente apareçam na tela
    + variantes de funções = as variantes de funções desempenham as mesmas tarefas que as funções apresentadas, mas para outras janelas criadas que não sejam a janela principal
*/
