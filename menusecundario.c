#include "projetostreaming.h"

int main() {

    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    delwin(MenuOpcoes);

    serie = (Serie*) malloc(sizeof(Serie) * 259);  //aloca memória pro vetor struct de séries

    getmaxyx(stdscr, yterminal, xterminal);  //consegue os valores máximos de resolução do terminal
    
    arquivotexto = fopen("streaming_db.txt", "r");
    arquivobinSeries = fopen("arquivobinSeries.dat", "rb");
    arquivobinHistorico = fopen("arquivobinHistorico.dat", "rb");
    
    borda = newwin(yterminal - 7, xterminal - 7, 4, 4);
    
    getmaxyx(borda, yborda, xborda);  //consegue as dimensões da janela de borda

    WINDOW *EntradaInfo = newwin(3, xborda - 30, yterminal / 2, (xterminal - (xborda - 30)) / 2);

    for (int i = 0; i < QuantidadeSeries; i++)
    {
        serie[i].QuantidadeEpisodiosTotais = 0;

        fread(&serie[i].id, sizeof(int), 1, arquivobinSeries);
        fread(serie[i].Nome, sizeof(char), 101, arquivobinSeries);
        fread(serie[i].Genero, sizeof(char), 41, arquivobinSeries);
        fread(&serie[i].Classificacao, sizeof(int), 1, arquivobinSeries);
        fread(serie[i].Plataforma, sizeof(char), 41, arquivobinSeries);
        fread(&serie[i].DuracaoMediaEpisodios, sizeof(int), 1, arquivobinSeries);
        fread(&serie[i].QuantidadeTemporadas, sizeof(int), 1, arquivobinSeries);

        int realoca = serie[i].QuantidadeTemporadas;
        serie[i].QuantidadeEpisodiosPorTemporada = (int*) malloc(realoca * sizeof(int));
        
        for (int j = 0; j < serie[i].QuantidadeTemporadas; j++) {

            fread(&serie[i].QuantidadeEpisodiosPorTemporada[j], sizeof(int), 1, arquivobinSeries);
      
            serie[i].QuantidadeEpisodiosTotais=serie[i].QuantidadeEpisodiosTotais+serie[i].QuantidadeEpisodiosPorTemporada[j];
        
        }//for

    }//for

    MenuOpcoes = newwin(9, 23, yterminal / 2 + 1, xterminal / 2 - 9);

    keypad(MenuOpcoes, TRUE);  //habilita entrada de setas
    werase(MenuOpcoes);

    MenuSecundario(EntradaInfo);

    endwin();
    return 0;

}

void MenuSecundario(WINDOW *EntradaInfo) {

    char *menuescolhas[] = {"Cadastrar", "Alterar", "Remover", "Listar Series", "Listar por Genero", "Pesquisar", "Sair"};
    int opcoes = 7;
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

            wattron(MenuOpcoes, A_REVERSE);

        }

        int x = (23 - strlen(menuescolhas[a])) / 2;  //variável utilizada para centralização de opções dentro do menu, 22 representa o comprimento da janela MenuOpcoes
        mvwprintw(MenuOpcoes, a + 1, x, "%s", menuescolhas[a]);
        wattroff(MenuOpcoes, A_REVERSE);

    }

    wborder(MenuOpcoes, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(MenuOpcoes);

    opcao = wgetch(MenuOpcoes);

    switch(opcao) {

        case KEY_UP: 
        highlight--;
           if(highlight < 0) {

                highlight = 0;

            }
            break;

            case KEY_DOWN:
            highlight++;
            if(highlight >= opcoes) {  // if que garante que o usuário não selecione opções fora do menu

                highlight = opcoes - 1;

            }
            break;

            case '\n':  //case que representa o que cada opção faz
            switch(highlight) {

                case 0:
                CadastrarSerie(EntradaInfo);
                break;

                case 1:
                AlterarSerie(EntradaInfo);
                break;

                case 2:
                RemoverSerie(EntradaInfo);
                break;

                case 3:
                ListaSerie();
                break;

                case 4:
                ListarPorGenero(EntradaInfo);
                break;

                case 5:
                PesquisarSerie(EntradaInfo);
                break;

                case 6:
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

        curs_set(TRUE);

    }

}

void CadastrarSerie(WINDOW *EntradaInfo) {

    setbuf(stdin, NULL);
    curs_set(TRUE);
    cbreak();
    echo();
    
    QuantidadeSeries++;
    char *StringAux = (char*) malloc (4 * sizeof(char)); //string auxiliar para coleta de inteiro
    serie = (Serie*) realloc(serie, QuantidadeSeries * sizeof(Serie));  //realoca para novo tamanho
    serie[QuantidadeSeries - 1].id = QuantidadeSeries;  //atribuição de id para a nova série a ser colocada

    ColetaNomeCadastrarSerie:
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
            goto ColetaNomeCadastrarSerie;

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
    getnstr(serie[QuantidadeSeries - 1].Genero, 31);
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

    free(StringAux);

    return;

}

void AlterarSerie(WINDOW *EntradaInfo) {

    echo();
    nocbreak();
    curs_set(TRUE);
    char *StringAux = (char*) malloc(100 * sizeof(char));
    char *StringAux1 = (char*) malloc(100 * sizeof(char));
    bool SerieEncontrada = FALSE;
    typedef enum {Nome = 1, Genero, Classificacao, Plataforma, QuantidadeTemporadas, QuantidadeEpisodiosTotais, QuantidadeEpisodiosPorTemporada, DuracaoMediaEpisodios, Sair} StructInfo;
    int Escolha;

    ColetaNomeAlterarSerie:
    clear();
    refresh();
    wclear(borda);
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);
    wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(EntradaInfo);
    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite o nome da serie que voce quer alterar")) / 2, "Digite o nome da serie que voce quer alterar");
    wrefresh(borda);
    move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
    refresh();
    getnstr(StringAux, 31);
    setbuf(stdin, NULL);

    for(int a = 0; a < QuantidadeSeries; a++) {

        if(strcasecmp(StringAux, serie[a].Nome) == 0) {

            IndiceSerieEscolhida = a;
            SerieEncontrada = TRUE;

        }

        if(SerieEncontrada == TRUE) {

            break;

        }

    }

    if(SerieEncontrada == FALSE) {

        clear();
        refresh();
        wclear(borda);
        mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Serie nao encontrada, pressione qualquer tecla e digite novamente")) / 2, "Serie nao encontrada, pressione qualquer tecla e digite novamente");
        wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(borda);
        getch();
        goto ColetaNomeAlterarSerie;

    }

    ColetaNovaInfoAlterarSerie:
    clear();
    refresh();
    wclear(borda);
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);
    wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(EntradaInfo);
    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite o numero de qual informação voce deseja alterar")) / 2, "Digite o numero de qual informação voce deseja alterar");
    mvwprintw(borda, yborda / 2 + 2, (xborda - strlen("1 - Nome")) / 2, "1 - Nome");
    mvwprintw(borda, yborda / 2 + 3, (xborda - strlen("1 - Genero")) / 2, "2 - Genero");
    mvwprintw(borda, yborda / 2 + 4, (xborda - strlen("1 - Classficacao")) / 2, "3 - Classficacao");
    mvwprintw(borda, yborda / 2 + 5, (xborda - strlen("1 - Plataforma")) / 2, "4 - Plataforma");
    mvwprintw(borda, yborda / 2 + 6, (xborda - strlen("1 - Quantidade de temporadas")) / 2, "5 - Quantidade de temporadas");
    mvwprintw(borda, yborda / 2 + 7, (xborda - strlen("1 - Quantidade total de episodios")) / 2, "6 - Quantidade total de episodios");
    mvwprintw(borda, yborda / 2 + 8, (xborda - strlen("1 - Quantidade de episodios por temporada")) / 2, "7 - Quantidade de episodios por temporada");
    mvwprintw(borda, yborda / 2 + 9, (xborda - strlen("1 - Duracao media dos episodios")) / 2, "8 - Duracao media dos episodios");
    mvwprintw(borda, yborda / 2 + 10, (xborda - strlen("1 - Sair")) / 2, "9 - Sair");
    wrefresh(borda);
    move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
    refresh();
    getnstr(StringAux, 1);
    setbuf(stdin, NULL);
    Escolha = atoi(StringAux);

    switch(Escolha) {

        case Nome:
        clear();
        refresh();
        wclear(borda);
        wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(borda);
        wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(EntradaInfo);
        mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite o novo nome para a serie escolhida")) / 2, "Digite o novo nome para a serie escolhida");
        wrefresh(borda);
        move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
        refresh();
        getnstr(StringAux, 31);
        strcpy(serie[IndiceSerieEscolhida].Nome, StringAux);
        setbuf(stdin, NULL);
        goto ColetaNovaInfoAlterarSerie;
        break;

        case Genero:
        clear();
        refresh();
        wclear(borda);
        wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(borda);
        wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(EntradaInfo);
        mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite o novo genero para a serie escolhida")) / 2, "Digite o novo genero para a serie escolhida");
        wrefresh(borda);
        move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
        refresh();
        getnstr(StringAux, 31);
        strcpy(serie[IndiceSerieEscolhida].Genero, StringAux);
        setbuf(stdin, NULL);
        goto ColetaNovaInfoAlterarSerie;
        break;

        case Classificacao:
        clear();
        refresh();
        wclear(borda);
        wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(borda);
        wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(EntradaInfo);
        mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite o novo genero para a serie escolhida")) / 2, "Digite o novo genero para a serie escolhida");
        wrefresh(borda);
        move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
        refresh();
        getnstr(StringAux, 2);
        serie[IndiceSerieEscolhida].Classificacao = atoi(StringAux);
        setbuf(stdin, NULL);
        goto ColetaNovaInfoAlterarSerie;
        break;

        case Plataforma:
        clear();
        refresh();
        wclear(borda);
        wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(borda);
        wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(EntradaInfo);
        mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite a nova plataforma para a serie escolhida")) / 2, "Digite a nova plataforma para a serie escolhida");
        wrefresh(borda);
        move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
        refresh();
        getnstr(StringAux, 13);
        strcpy(serie[IndiceSerieEscolhida].Plataforma, StringAux);
        setbuf(stdin, NULL);
        goto ColetaNovaInfoAlterarSerie;
        break;

        case QuantidadeTemporadas:
        clear();
        refresh();
        wclear(borda);
        wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(borda);
        wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(EntradaInfo);
        mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite a nova quantidade de temporadas para a serie escolhida")) / 2, "Digite a nova quantidade de temporadas para a serie escolhida");
        wrefresh(borda);
        move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
        refresh();
        getnstr(StringAux, 4);
        serie[IndiceSerieEscolhida].QuantidadeTemporadas = atoi(StringAux);
        serie[IndiceSerieEscolhida].QuantidadeEpisodiosPorTemporada = (int*) realloc(serie[IndiceSerieEscolhida].QuantidadeEpisodiosPorTemporada, serie[IndiceSerieEscolhida].QuantidadeTemporadas * sizeof(int));
        setbuf(stdin, NULL);
        goto ColetaNovaInfoAlterarSerie;
        break;

        case QuantidadeEpisodiosTotais:
        clear();
        refresh();
        wclear(borda);
        wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(borda);
        wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(EntradaInfo);
        mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite a nova quantidade de episodios totais para a serie escolhida")) / 2, "Digite a nova quantidade de episodios totais para a serie escolhida");
        wrefresh(borda);
        move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
        refresh();
        getnstr(StringAux, 6);
        serie[IndiceSerieEscolhida].QuantidadeEpisodiosTotais = atoi(StringAux);
        setbuf(stdin, NULL);
        goto ColetaNovaInfoAlterarSerie;
        break;

        case QuantidadeEpisodiosPorTemporada:
        for(int a = 0; a < serie[IndiceSerieEscolhida].QuantidadeTemporadas; a++) { 
        clear();
        refresh();
        wclear(borda);
        wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(borda);
        wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(EntradaInfo);
        mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite a nova quantidade de episodios para a serie escolhida. Temporada  :")) / 2, "Digite a nova quantidade de episodios totais para a serie escolhida. Temporada %i:", a + 1);
        wrefresh(borda);
        move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
        refresh();
        getnstr(StringAux, 6);
        serie[IndiceSerieEscolhida].QuantidadeEpisodiosPorTemporada[a] = atoi(StringAux);
        setbuf(stdin, NULL);
        }
        goto ColetaNovaInfoAlterarSerie;
        break;

        case DuracaoMediaEpisodios:
        clear();
        refresh();
        wclear(borda);
        wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(borda);
        wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(EntradaInfo);
        mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite a nova duracao media dos episodios para a serie escolhida")) / 2, "Digite a nova duracao media dos episodios para a serie escolhida");
        wrefresh(borda);
        move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
        refresh();
        getnstr(StringAux, 6);
        serie[IndiceSerieEscolhida].DuracaoMediaEpisodios = atoi(StringAux);
        setbuf(stdin, NULL);
        goto ColetaNovaInfoAlterarSerie;
        break;

        case Sair:
        clear();
        refresh();
        wclear(borda);
        wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(borda);
        strcpy(StringAux, "Nome: ");
    strcat(StringAux, serie[IndiceSerieEscolhida].Nome);
    mvwprintw(borda, (yborda - 8) / 2 - 2, (xborda - strlen(StringAux)) / 2, "%s", StringAux);

    sprintf(StringAux, "ID: %i", serie[IndiceSerieEscolhida].id);
    mvwprintw(borda, (yborda - 8) / 2, (xborda - strlen(StringAux)) / 2, "%s", StringAux);

    strcpy(StringAux, "Genero: ");
    strcat(StringAux, serie[IndiceSerieEscolhida].Genero);
    mvwprintw(borda, (yborda - 8) / 2 + 2, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
    sprintf(StringAux, "Classficacao: %i", serie[IndiceSerieEscolhida].Classificacao);
    mvwprintw(borda, (yborda - 8) / 2 + 3, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
    strcpy(StringAux, "Plataforma: ");
    strcat(StringAux, serie[IndiceSerieEscolhida].Plataforma);
    mvwprintw(borda, (yborda - 8) / 2 + 4, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
    sprintf(StringAux, "Quantidade de temporadas: %i", serie[IndiceSerieEscolhida].QuantidadeTemporadas);
    mvwprintw(borda, (yborda - 8) / 2 + 5, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
    sprintf(StringAux, "Quantidade total de episodios: %i", serie[IndiceSerieEscolhida].QuantidadeEpisodiosTotais);
    mvwprintw(borda, (yborda - 8) / 2 + 6, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
    char *StringAux1 = (char*) malloc(sizeof(char) * 100);

    strcpy(StringAux, " ");

    for(int a = 0; a < serie[IndiceSerieEscolhida].QuantidadeTemporadas; a++) {

        sprintf(StringAux1, "%i ", serie[IndiceSerieEscolhida].QuantidadeEpisodiosPorTemporada[a]);
        strcat(StringAux, StringAux1);

    }
    
    strcpy(StringAux1, StringAux);
    strcpy(StringAux, "Quantidade de episodios por temporada:");
    strcat(StringAux, StringAux1);
    mvwprintw(borda, (yborda - 8) / 2 + 7, (xborda - strlen(StringAux)) / 2, "%s", StringAux);

    sprintf(StringAux, "Duracao media dos episodios: %i", serie[IndiceSerieEscolhida].DuracaoMediaEpisodios);
    mvwprintw(borda, (yborda - 8) / 2 + 8, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    mvwprintw(borda, yborda - 2, (xborda - strlen("Pressione qualquer tecla para sair")) / 2, "Pressione qualquer tecla para sair");
    wrefresh(borda);
    curs_set(FALSE);
        getch();
        break;

        default:
        clear();
        refresh();
        wclear(borda);
        wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(borda);
        mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Comando invalido! Pressione qualquer tecla e digite novamente")) / 2, "Comando invalido! Pressione qualquer tecla e digite novamente");
        wrefresh(borda);
        getch();
        goto ColetaNovaInfoAlterarSerie;
        break;

    }

    free(StringAux);
    free(StringAux1);
    return;

}

void RemoverSerie(WINDOW *EntradaInfo) {

    echo();
    nocbreak();
    curs_set(TRUE);

    char *StringAux = (char*) malloc(50 * sizeof(char));
    bool SerieEncontrada = FALSE;

    ColetaNomeRemoverSerie:
    clear();
    refresh();
    wclear(borda);
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);
    wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(EntradaInfo);
    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite o nome da serie que voce quer excluir")) / 2, "Digite o nome da serie que voce quer excluir");
    wrefresh(borda);
    move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
    refresh();
    getnstr(StringAux, 31);
    setbuf(stdin, NULL);

    for(int a = 0; a < QuantidadeSeries; a++) {

        if(strcasecmp(StringAux, serie[a].Nome) == 0) {

            IndiceSerieEscolhida = a;
            SerieEncontrada = TRUE;

        }

        if(SerieEncontrada == TRUE) {

            break;

        }

    }

    if(SerieEncontrada == FALSE) {

        clear();
        refresh();
        wclear(borda);
        mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Serie nao encontrada, pressione qualquer tecla e digite novamente")) / 2, "Serie nao encontrada, pressione qualquer tecla e digite novamente");
        wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(borda);
        getch();
        goto ColetaNomeRemoverSerie;

    }

    serie[IndiceSerieEscolhida].id=IndiceSerieEscolhida+1;
    strcpy(serie[IndiceSerieEscolhida].Nome,serie[QuantidadeSeries - 1].Nome);
    strcpy(serie[IndiceSerieEscolhida].Genero, serie[QuantidadeSeries - 1].Genero);
    serie[IndiceSerieEscolhida].Classificacao=serie[QuantidadeSeries-1].Classificacao;
    strcpy(serie[IndiceSerieEscolhida].Plataforma, serie[QuantidadeSeries - 1].Plataforma);
    serie[IndiceSerieEscolhida].DuracaoMediaEpisodios=serie[QuantidadeSeries -1].DuracaoMediaEpisodios;
    serie[IndiceSerieEscolhida].QuantidadeTemporadas=serie[QuantidadeSeries-1].QuantidadeTemporadas;
    serie[IndiceSerieEscolhida].QuantidadeEpisodiosTotais=serie[QuantidadeSeries-1].QuantidadeEpisodiosTotais;

    int realoca = serie[IndiceSerieEscolhida].QuantidadeTemporadas;
    serie[IndiceSerieEscolhida].QuantidadeEpisodiosPorTemporada = realloc(serie[IndiceSerieEscolhida].QuantidadeEpisodiosPorTemporada ,realoca * sizeof(int));
            
    for(int i = 0; i <realoca; i++) { 

        serie[IndiceSerieEscolhida].QuantidadeEpisodiosPorTemporada[i]=serie[QuantidadeSeries-1].QuantidadeEpisodiosPorTemporada[i];
            
    }//for

    QuantidadeSeries--;
            
    serie = (Serie *)realloc(serie, QuantidadeSeries * sizeof(Serie));

    free(StringAux);

    clear();
    refresh();
    wclear(borda);
    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("A serie inserida foi removida com sucesso! Pressione qualquer tecla")) / 2, "A serie inserida foi removida com sucesso! Pressione qualquer tecla");
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);
    curs_set(FALSE);
    getch();

    return;

}

void ListaSerie() {

    keypad(borda, TRUE);
    cbreak();
    noecho();
    curs_set(FALSE);

    OpcoesMin = 0;
    OpcoesMax = 30;
    int highlight = 0;
    int opcao;
    int yopcao = 0;

    char *StringAux = (char*) malloc(sizeof(char) * 100);

    while (1) {
        
        wclear(borda);
        yopcao = 0;

        for (int a = OpcoesMin; a < OpcoesMax; a++) {
            if (a == highlight) {

                wattron(borda, A_REVERSE);

            }

            int x = (40 - strlen(serie[a].Nome)) / 2;
            mvwprintw(borda, yopcao + 1, x, "%s", serie[a].Nome);
            wattroff(borda, A_REVERSE);
            yopcao++;

        }

    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    
    strcpy(StringAux, "Nome: ");
    strcat(StringAux, serie[highlight].Nome);
    mvwprintw(borda, (yborda - 8) / 2 - 2, (xborda - strlen(StringAux)) / 2, "%s", StringAux);

    sprintf(StringAux, "ID: %i", serie[highlight].id);
    mvwprintw(borda, (yborda - 8) / 2, (xborda - strlen(StringAux)) / 2, "%s", StringAux);

    strcpy(StringAux, "Genero: ");
    strcat(StringAux, serie[highlight].Genero);
    mvwprintw(borda, (yborda - 8) / 2 + 2, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
    sprintf(StringAux, "Classficacao: %i", serie[highlight].Classificacao);
    mvwprintw(borda, (yborda - 8) / 2 + 3, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
    strcpy(StringAux, "Plataforma: ");
    strcat(StringAux, serie[highlight].Plataforma);
    mvwprintw(borda, (yborda - 8) / 2 + 4, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
    sprintf(StringAux, "Quantidade de temporadas: %i", serie[highlight].QuantidadeTemporadas);
    mvwprintw(borda, (yborda - 8) / 2 + 5, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
    sprintf(StringAux, "Quantidade total de episodios: %i", serie[highlight].QuantidadeEpisodiosTotais);
    mvwprintw(borda, (yborda - 8) / 2 + 6, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
    char *StringAux1 = (char*) malloc(sizeof(char) * 100);

    strcpy(StringAux, " ");
    for(int a = 0; a < serie[highlight].QuantidadeTemporadas; a++) {

        sprintf(StringAux1, "%i ", serie[highlight].QuantidadeEpisodiosPorTemporada[a]);
        strcat(StringAux, StringAux1);

    }
    
    strcpy(StringAux1, StringAux);
    strcpy(StringAux, "Quantidade de episodios por temporada:");
    strcat(StringAux, StringAux1);
    mvwprintw(borda, (yborda - 8) / 2 + 7, (xborda - strlen(StringAux)) / 2, "%s", StringAux);

    sprintf(StringAux, "Duracao media dos episodios: %i", serie[highlight].DuracaoMediaEpisodios);
    mvwprintw(borda, (yborda - 8) / 2 + 8, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    mvwprintw(borda, yborda - 2, (xborda - strlen("Pressione S para sair")) / 2, "Pressione S para sair");
    wrefresh(borda);

    free(StringAux1);

        opcao = wgetch(MenuOpcoes);

        switch (opcao) {
            case KEY_DOWN:
                highlight++;
                if (highlight >= OpcoesMax) {

                    OpcoesMax = highlight + 1;
                    OpcoesMin = OpcoesMax - 30;

                }
                break;

            case KEY_UP:
                highlight--;
                if (highlight < 0) {
                    highlight = 0;
                    if (highlight < OpcoesMin) {

                        OpcoesMin = highlight;
                        OpcoesMax = OpcoesMin + 30;

                    }
                }
            break;

            case 's':
            free(StringAux);
            return;
        }
    }
}

void ListarPorGenero(WINDOW *EntradaInfo) {  //PRECISA SER COMPLETADO

    nocbreak();
    echo();
    curs_set(TRUE);

    int yopcao = 0;
    int highlight = 0;
    int opcao;
    int Contador = 0;
    int IntAux;
    OpcoesMin = 0;
    OpcoesMax = 30;

    char *StringAux = (char*) malloc(sizeof(char) * 60);

    int *IndicesSeries = (int*) malloc(sizeof(int));

    clear();
    refresh();
    wclear(borda);
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);
    wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(EntradaInfo);
    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite um genero para listar series")) / 2, "Digite um genero para listar series");
    wrefresh(borda);
    move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
    refresh();
    getnstr(StringAux, 60);
    setbuf(stdin, NULL);

    for(int a = 0; a < QuantidadeSeries; a++) {

        if(strcasecmp(StringAux, serie[a].Genero) == 0) {

            IndicesSeries[Contador] = a;
            Contador++;
            IndicesSeries = (int*) realloc(IndicesSeries, sizeof(int) * (Contador + 1));
            
        }

    }

    IndicesSeries = (int*) realloc(IndicesSeries, sizeof(int) * (Contador - 1));

    clear();
    refresh();
    keypad(borda, TRUE);
    curs_set(FALSE);
    noecho();
    cbreak();

    while (1) {

        wclear(borda);
        yopcao = 0;

        for (int a = OpcoesMin; a < OpcoesMax; a++) {

            if (a == highlight) {
                wattron(borda, A_REVERSE);
            }

            IntAux = IndicesSeries[a];
            int x = (40 - strlen(serie[IntAux].Nome)) / 2;
            mvwprintw(borda, yopcao + 1, x, "%s", serie[IntAux].Nome);
            wattroff(borda, A_REVERSE);
            yopcao++;

        }

        IntAux = IndicesSeries[highlight];
        wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
        mvwprintw(borda, (yborda - 8) / 2, xborda / 2 + 6, "ID: %i", serie[IntAux].id);
        mvwprintw(borda, (yborda - 8) / 2 + 2, xborda / 2 + 6, "Genero: %s", serie[IntAux].Genero);
        mvwprintw(borda, (yborda - 8) / 2 + 3, xborda / 2 + 6, "Classificacao: %i", serie[IntAux].id);
        mvwprintw(borda, (yborda - 8) / 2 + 4, xborda / 2 + 6, "Plataforma: %s", serie[IntAux].Plataforma);
        mvwprintw(borda, (yborda - 8) / 2 + 5, xborda / 2 + 6, "Quantidade de temporadas: %i", serie[IntAux].QuantidadeTemporadas);
        mvwprintw(borda, (yborda - 8) / 2 + 6, xborda / 2 + 6, "Quantidade total de episodios: %i", serie[IntAux].QuantidadeEpisodiosTotais);
        mvwprintw(borda, (yborda - 8) / 2 + 7, xborda / 2 + 6, "Quantidade de episodios por temporada: ");

        for(int a = 0; a < serie[IntAux].QuantidadeTemporadas; a++) {

            wprintw(borda, "%i ", serie[IntAux].QuantidadeEpisodiosPorTemporada[a]);

        }

        mvwprintw(borda, (yborda - 8) / 2 + 8, xborda / 2 + 6, "Duracao media dos episodios: %i", serie[IntAux].DuracaoMediaEpisodios);
        mvwprintw(borda, yborda - 2, (xborda - strlen("Pressione S para sair")) / 2, "Pressione S para sair");
        wrefresh(borda);

        opcao = wgetch(MenuOpcoes);

        switch (opcao) {
            case KEY_DOWN:
                highlight++;
                if (highlight >= OpcoesMax) {

                    highlight = Contador - 1;
                    OpcoesMax = highlight + 1;
                    OpcoesMin = OpcoesMax - 30;

                }
                break;

            case KEY_UP:
                if (highlight > 0) {
                    highlight--;
                    if (highlight < OpcoesMin) {

                        OpcoesMin = highlight;
                        OpcoesMax = OpcoesMin + 30;

                    }
                }
            break;

            case 's':
                return;


        
        }
        
        // mvwprintw(borda, (yborda - 8) / 2, xborda / 2 + 10, "ID: %i", serie[highlight].id);
        // mvwprintw(borda, (yborda - 8) / 2 + 2, xborda / 2 + 10, "Genero: %s", serie[highlight].Genero);
        // mvwprintw(borda, (yborda - 8) / 2 + 3, xborda / 2 + 10, "Classificacao: %i", serie[highlight].id);
        // mvwprintw(borda, (yborda - 8) / 2 + 4, xborda / 2 + 10, "Plataforma: %s", serie[highlight].Plataforma);
        // mvwprintw(borda, (yborda - 8) / 2 + 5, xborda / 2 + 10, "Quantidade de temporadas: %i", serie[highlight].QuantidadeTemporadas);
        // mvwprintw(borda, (yborda - 8) / 2 + 6, xborda / 2 + 10, "Quantidade total de episodios: %i", serie[highlight].QuantidadeEpisodiosTotais);
        // mvwprintw(borda, (yborda - 8) / 2 + 7, xborda / 2 + 10, "Quantidade de episodios por temporada: ");
    }
}

void PesquisarSerie(WINDOW *EntradaInfo) {

    nocbreak();
    echo();
    curs_set(TRUE);

    char *StringAux = (char*) malloc(sizeof(char) * 100);
    bool SerieEncontrada = FALSE;


    ColetaNomePesquisarSerie:
    clear();
    refresh();
    wclear(borda);
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);
    wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(EntradaInfo);
    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite o nome da serie que deseja pesquisar")) / 2, "Digite o nome da serie que deseja pesquisar");
    wrefresh(borda);
    move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
    refresh();
    getnstr(StringAux, 31);
    setbuf(stdin, NULL);

    for(int a = 0; a < QuantidadeSeries; a++) {

        if(strcasecmp(serie[a].Nome, StringAux) == 0) {

            SerieEncontrada = TRUE;
            IndiceSerieEscolhida = a;
            break;

        }

    }

    if(SerieEncontrada == FALSE) {

        clear();
        refresh();
        wclear(borda);
        wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(borda);
        mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Serie nao encontrada. Pressione qualquer tecla e digite novamente")) / 2, "Serie nao encontrada. Pressione qualquer tecla e digite novamente");
        wrefresh(borda);
        getch();
        goto ColetaNomePesquisarSerie;
        
    }

    curs_set(FALSE);
    wclear(EntradaInfo);
    wclear(borda);
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    
    strcpy(StringAux, "Nome: ");
    strcat(StringAux, serie[IndiceSerieEscolhida].Nome);
    mvwprintw(borda, (yborda - 8) / 2 - 2, (xborda - strlen(StringAux)) / 2, "%s", StringAux);

    sprintf(StringAux, "ID: %i", serie[IndiceSerieEscolhida].id);
    mvwprintw(borda, (yborda - 8) / 2, (xborda - strlen(StringAux)) / 2, "%s", StringAux);

    strcpy(StringAux, "Genero: ");
    strcat(StringAux, serie[IndiceSerieEscolhida].Genero);
    mvwprintw(borda, (yborda - 8) / 2 + 2, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
    sprintf(StringAux, "Classficacao: %i", serie[IndiceSerieEscolhida].Classificacao);
    mvwprintw(borda, (yborda - 8) / 2 + 3, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
    strcpy(StringAux, "Plataforma: ");
    strcat(StringAux, serie[IndiceSerieEscolhida].Plataforma);
    mvwprintw(borda, (yborda - 8) / 2 + 4, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
    sprintf(StringAux, "Quantidade de temporadas: %i", serie[IndiceSerieEscolhida].QuantidadeTemporadas);
    mvwprintw(borda, (yborda - 8) / 2 + 5, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
    sprintf(StringAux, "Quantidade total de episodios: %i", serie[IndiceSerieEscolhida].QuantidadeEpisodiosTotais);
    mvwprintw(borda, (yborda - 8) / 2 + 6, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
    char *StringAux1 = (char*) malloc(sizeof(char) * 100);

    strcpy(StringAux, " ");

    for(int a = 0; a < serie[IndiceSerieEscolhida].QuantidadeTemporadas; a++) {

        sprintf(StringAux1, "%i ", serie[IndiceSerieEscolhida].QuantidadeEpisodiosPorTemporada[a]);
        strcat(StringAux, StringAux1);

    }
    
    strcpy(StringAux1, StringAux);
    strcpy(StringAux, "Quantidade de episodios por temporada:");
    strcat(StringAux, StringAux1);
    mvwprintw(borda, (yborda - 8) / 2 + 7, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
    free(StringAux1);

    sprintf(StringAux, "Duracao media dos episodios: %i", serie[IndiceSerieEscolhida].DuracaoMediaEpisodios);
    mvwprintw(borda, (yborda - 8) / 2 + 8, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
    mvwprintw(borda, yborda - 2, (xborda - strlen("Pressione qualquer tecla para sair")) / 2, "Pressione qualquer tecla para sair");
    
    wrefresh(borda);
    
    getch();

    free(StringAux);

    return;

}
