#ifndef projetostreaming.h
#define projetostreaming.h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct {

    int contador;

    char Nome[31];
    char Genero[13];
    int Classificao;
    char Plataforma[13];
    int QuantidadeTemporadas;
    int QuantidadeEpisodiosTotais;
    int *QuantidadeEpisodiosPorTemporada;
    int DuracaoMediaEpisodios;

} Serie;

Serie *serie;

typedef struct {

    char Nome[31];
    int EpisodiosPendentes;
    int UltimoEpisodio;
    int UltimaTemporada;

} Historico;
Historico *historico;

#endif 

/* COISAS NECESSÁRIAS PARA O PROGRAMA: 
- Menu com todas as opções disponíveis, sendo essas:

     + Busca por Gênero
     + Cadastro, Listagem, pesquisa, alteração e exclusão de itens tanto na struct de séries quanto an de histórico

- Mensagem de boas-vindas, quando não houver arquivo que armazene os dados das séries e histórico
- Carregar o arquivo com os dados das séries na primeira execução do programa, evitando o carregamento do mesmo quando for aberto uma outra vez
- Salva os dados lidos do arquivo de texto em um novo arquivo binário para que ele possa ser lido nas próximas vezes
*/

/* EXPLICAÇÃO DA BIBLIOTECA DE INTERFACE GRÁFICA -> A biblioteca destinada à interface gráfica ncurses.h produz uma interface gáfica a partir do terminal onde o código está sendo executado. A biblioteca, assim como
em uma interface gráfica normal, funciona a partir de janelas, mas no caso do ncurses as janelas são imaginárias e existentes dentro do terminal, onde se pode dimensionar
as janelas a partir da resolução disponível no terminal, obtida pela função getmaxyx(). */
