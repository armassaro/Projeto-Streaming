#include "projetostreaming.h"

int main() {

    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    delwin(menuopcoes);

    serie = (Serie*) malloc(sizeof(Serie) * 259);  //aloca memória pro vetor struct de séries

    getmaxyx(stdscr, yterminal, xterminal);  //consegue os valores máximos de resolução do terminal
    
    arquivotexto = fopen("streaming_db.txt", "r");
    arquivobinSeries = fopen("arquivobinSeries.dat", "wb");
    arquivobinHistorico = fopen("arquivobinHistorico.dat", "wb");
    
    borda = newwin(yterminal - 7, xterminal - 7, 4, 4);
    
    getmaxyx(borda, yborda, xborda);  //consegue as dimensões da janela de borda

    WINDOW *EntradaInfo = newwin(3, xborda - 30, yterminal / 2, (xterminal - (xborda - 30)) / 2);

    for (int i = 0; i < QuantidadeSeries; i++) {

        fscanf(arquivotexto, "%d,", &serie[i].id);
        fscanf(arquivotexto, "%[^,\n],", serie[i].Nome);
        fscanf(arquivotexto, "%[^,\n],", serie[i].Genero);
        fscanf(arquivotexto, "%d,", &serie[i].Classificacao);
        fscanf(arquivotexto, "%[^,\n],", serie[i].Plataforma);
        fscanf(arquivotexto, "%d,", &serie[i].DuracaoMediaEpisodios);
        fscanf(arquivotexto, "%d,", &serie[i].QuantidadeTemporadas);

        int realoca = serie[i].QuantidadeTemporadas;
        serie[i].QuantidadeEpisodiosPorTemporada = malloc(realoca * sizeof(int));

        for (int j = 0; j < serie[i].QuantidadeTemporadas; j++) {

            fscanf(arquivotexto, "%d,", &serie[i].QuantidadeEpisodiosPorTemporada[j]);

        }

    }

    menuopcoes = newwin(8, 23, yterminal / 2 + 1, xterminal / 2 - 9);

    keypad(menuopcoes, TRUE);  //habilita entrada de setas
    werase(menuopcoes);

    MenuSecundario(EntradaInfo);

    endwin();
    return 0;

}

void MenuSecundario(WINDOW *EntradaInfo) {

    char *menuescolhas[] = {"Cadastrar", "Alterar", "Remover", "Listar", "Listar por Genero",  "Sair"};
    int opcoes = 6;
    int opcao;
    int highlight = 0;

    while(1) { 
    
    cbreak();
    noecho();
    curs_set(FALSE); //desabilita o cursor, limpa a janela e printa logo e menu com opções
    wclear(borda);
    wrefresh(borda);
        
    mvwprintw(borda, yborda / 2 - 7, xborda / 2 - 30, "%s", stringlogopt1);
    mvwprintw(borda, yborda / 2 - 6, xborda / 2 - 30, "%s", stringlogopt2);
    mvwprintw(borda, yborda / 2 - 5, xborda / 2 - 30, "%s", stringlogopt3);
    mvwprintw(borda, yborda / 2 - 4, xborda / 2 - 30, "%s", stringlogopt4);
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');  //desenha noavmente a borda da janela
    wrefresh(borda);

    for(int a = 0; a < opcoes; a++) {  //loop de print das opções do menu e atualização do efeito de seleção dentro do menu

        if(a == highlight) {

            wattron(menuopcoes, A_REVERSE);

        }

        int x = (23 - strlen(menuescolhas[a])) / 2;  //variável utilizada para centralização de opções dentro do menu, 22 representa o comprimento da janela menuopcoes
        mvwprintw(menuopcoes, a + 1, x, "%s", menuescolhas[a]);
        wattroff(menuopcoes, A_REVERSE);

    }

    wborder(menuopcoes, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(menuopcoes);

    opcao = wgetch(menuopcoes);

    switch(opcao) {

        case KEY_UP:
        highlight--;
           if(highlight < 0) {

                highlight = 0;

            }
            break;

            case KEY_DOWN:
            highlight++;
            if(highlight > opcoes) {  // if que garante que o usuário não selecione opções fora do menu

                highlight = opcoes - 1;

            }
            break;

            case '\n':  //case que representa o que cada opção faz
            switch(highlight) {

                case 0:
                CadastrarSerie(EntradaInfo);
                break;

                case 1:
                //AlterarSerie(EntradaInfo);
                break;

                case 2:
                //RemoverSerie(EntradaInfo);
                break;

                case 3:
                //ListaSerie(EntradaInfo);
                break;

                case 4:
                // ListarPorGenero(EntradaInfo);
                break;

                case 5:
                endwin();
                exit(0);
                break;

                default:
                break;

            }
            break;

            default:
            break;
            
        }

    }

}


void CadastrarSerie(WINDOW *EntradaInfo) {

    setbuf(stdin, NULL);
    curs_set(TRUE);
    cbreak();
    echo();
    QuantidadeSeries++;
    char StringAux[4]; //string auxiliar para coleta de inteiro
    serie = (Serie*) realloc(serie, QuantidadeSeries * sizeof(Serie));  //realoca para novo tamanho
    serie[QuantidadeSeries - 1].id = QuantidadeSeries;  //atribuição de id para a nova série a ser colocada

    ColetaNome:
    clear();
    refresh();
    wclear(borda);
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);
    wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(EntradaInfo);
    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite o nome da serie a ser cadastrada")) / 2, "Digite o nome da serie a ser cadastrada");
    wrefresh(borda);
    move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
    refresh();
    getnstr(serie[QuantidadeSeries - 1].Nome, 30);  //função de coleta de string pra biblioteca ncurses q nn deixa caractere \n como final
    setbuf(stdin, NULL);

    for (int i = 0; i < QuantidadeSeries - 1; i++) { 

        if (strcasecmp(serie[i].Nome, serie[QuantidadeSeries - 1].Nome) == 0)
        {

            wclear(borda);
            wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
            mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Essa serie ja esta cadastrada, digite outro nome")) / 2, "Essa serie ja esta cadastrada, digite outro nome");
            wrefresh(borda);
            getch();
            goto ColetaNome;

        }

    }

    clear();
    refresh();
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);
    wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(EntradaInfo);
    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite o genero da serie a ser cadastrada")) / 2, "Digite o genero da serie a ser cadastrada");
    wrefresh(borda);
    move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
    getnstr(serie[QuantidadeSeries - 1].Genero, 12);
    refresh();
    setbuf(stdin, NULL);

    clear();
    refresh();
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);
    wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(EntradaInfo);
    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite a idade da classificacao da serie a ser cadastrada")) / 2, "Digite a idade da classificacao da serie a ser cadastrada");
    wrefresh(borda);
    move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
    refresh();
    getnstr(StringAux, 2);
    serie[QuantidadeSeries - 1].Classificacao = atoi(StringAux); //função de conversão de string para inteiro

    clear();
    refresh();
    wclear(borda);
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);
    wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(EntradaInfo);
    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite a plataforma da serie a ser cadastrada")) / 2, "Digite a plataforma da serie a ser cadastrada");
    wrefresh(borda);
    move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
    refresh();
    getnstr(serie[QuantidadeSeries-1].Plataforma, 12);
    setbuf(stdin, NULL);

    clear();
    refresh();
    wclear(borda);
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);
    wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(EntradaInfo);
    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite a quantidade de temporadas da serie a ser cadastrada")) / 2, "Digite a quantidade de temporadas da serie a ser cadastrada");
    wrefresh(borda);
    move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
    refresh();
    getnstr(StringAux, 2);
    serie[QuantidadeSeries - 1].QuantidadeTemporadas = atoi(StringAux);
    setbuf(stdin, NULL);

    clear();
    refresh();
    wclear(borda);
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);
    wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(EntradaInfo);
    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite a quantidade total de episodios da serie a ser cadastrada")) / 2, "Digite a quantidade total de episodios da serie a ser cadastrada");
    wrefresh(borda);
    move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
    refresh();
    getnstr(StringAux, 4);
    serie[QuantidadeSeries - 1].QuantidadeEpisodiosTotais = atoi(StringAux);
    setbuf(stdin, NULL);

    int realoca = serie[QuantidadeSeries - 1].QuantidadeTemporadas;
    serie[QuantidadeSeries-1].QuantidadeEpisodiosPorTemporada = (int*) malloc(realoca * sizeof(int));

    for(int a = 0; a < serie[QuantidadeSeries-1].QuantidadeTemporadas; a++) { 

    clear();
    refresh();
    wclear(borda);
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);
    wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(EntradaInfo);
    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite a quantidade de episodios por temporada da serie a ser cadastrada. Temporada  :")) / 2, "Digite a quantidade de episodios por temporada da serie a ser cadastrada. Temporada %i: ", a + 1);
    wrefresh(borda);
    move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
    refresh();
    getnstr(StringAux, 3);
    serie[QuantidadeSeries-1].QuantidadeEpisodiosPorTemporada[a] = atoi(StringAux);
    setbuf(stdin, NULL);

    }

    clear();
    refresh();
    wclear(borda);
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);
    wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(EntradaInfo);
    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite a duracao media dos episodios da serie a ser cadastrada")) / 2, "Digite a duracao media dos episodios da serie a ser cadastrada");
    wrefresh(borda);
    move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
    refresh();
    getnstr(StringAux, 3);
    serie[QuantidadeSeries - 1].DuracaoMediaEpisodios = atoi(StringAux);

    return;

}

// void ListarPorGenero(WINDOW *EntradaInfo) {  //PRECISA SER COMPLETADO

//     wclear(menuopcoes);
//     wrefresh(menuopcoes);
//     char StringAux[12];
//     keypad(menuopcoes, TRUE);
//     int opcoesMax;
//     int opcoesMin = 0;
//     int opcao;
//     int highlight = 0;

//     clear();
//     refresh();
//     wclear(borda);
//     wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
//     wrefresh(borda);
//     wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
//     wrefresh(EntradaInfo);
//     mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite o gênero que queira lista as séries")) / 2, "Digite o gênero que queira listar as séries");
//     wrefresh(borda);
//     move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
//     refresh();
//     getnstr(StringAux, 12);
//     setbuf(stdin, NULL);

//     for(int a = 0; a < QuantidadeSeries; a++) {


//     }

//     for(int a = opcoesMin; a < opcoesMax; a++) {  //loop de print das opções do menu e atualização do efeito de seleção dentro do menu

//         if(a == highlight) {

//             wattron(menuopcoes, A_REVERSE);

//         }

//         int x = (23 - strlen(menuescolhas[a])) / 2;  //variável utilizada para centralização de opções dentro do menu, 22 representa o comprimento da janela menuopcoes
//         mvwprintw(menuopcoes, a + 1, x, "%s", menuescolhas[a]);
//         wattroff(menuopcoes, A_REVERSE);

//     }

//     wborder(menuopcoes, '#', '#', '-', '-', '-', '-', '-', '-');
//     wrefresh(menuopcoes);

//     opcao = wgetch(menuopcoes);

//     switch(opcao) {

//         case KEY_UP:
//         highlight--;
//            if(highlight < 0) {

//                 highlight = 0;

//             }
//             break;

//             case KEY_DOWN:
//             highlight++;
//             if(highlight > opcoes) {  // if que garante que o usuário não selecione opções fora do menu

//                 highlight = opcoes - 1;

//             }
//             break;

//             case '\n':  //case que representa o que cada opção faz
//             switch(highlight) {

//                 case 0:
//                 CadastrarSerie(EntradaInfo);
//                 break;

//                 case 1:
//                 //AlterarSerie(EntradaInfo);
//                 break;

//                 case 2:
//                 //RemoverSerie(EntradaInfo);
//                 break;

//                 case 3:
//                 //ListaSerie(EntradaInfo);
//                 break;

//                 case 4:
//                 ListarPorGenero(EntradaInfo);
//                 break;

//                 case 5:
//                 endwin();
//                 exit(0);
//                 break;

//                 default:
//                 break;

//             }
//             break;

//             default:
//             break;
            
//         }

//     }

// }
