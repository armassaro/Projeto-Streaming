#include "projetostreaming.h"

void MenuSecundario(WINDOW *EntradaInfo);

int main() {

    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);

    serie = (Serie*) malloc(sizeof(Serie) * QuantidadeSeries);  //aloca memória pro vetor struct de séries

    getmaxyx(stdscr, yterminal, xterminal);  //consegue os valores máximos de resolução do terminal
    
    arquivotexto = fopen("streaming_db.csv", "r");
    arquivobinSeries = fopen("arquivobinSeries.dat", "rb");
    // arquivobinHistorico = fopen("arquivobinHistorico.dat", "rb");
    
    borda = newwin(yterminal - 7, xterminal - 7, 4, 4);
    
    getmaxyx(borda, yborda, xborda);  //consegue as dimensões da janela de borda

    WINDOW *EntradaInfo = newwin(3, xborda - 30, yterminal / 2, (xterminal - (xborda - 30)) / 2);   //ponteiro utilizado para entrada de informações do usuário

    for (int i = 0; i < QuantidadeSeries; i++)  //print de coleta de informações do arquivo binário para a struct de séries
    {
        
        serie[i].QuantidadeEpisodiosTotais = 0;

        IntAux = 0;

        fscanf(arquivotexto, "%d,", &serie[i].id);
        fscanf(arquivotexto, "%[^,\n],", serie[i].Nome);
        fscanf(arquivotexto, "%[^,\n],", serie[i].Genero);
        fscanf(arquivotexto, "%d,", &serie[i].Classificacao);
        fscanf(arquivotexto, "%[^,\n],", serie[i].Plataforma);
        fscanf(arquivotexto, "%d,", &serie[i].DuracaoMediaEpisodios);
        fscanf(arquivotexto, "%d,", &serie[i].QuantidadeTemporadas);

        int realoca = serie[i].QuantidadeTemporadas;
        serie[i].QuantidadeEpisodiosPorTemporada = (int*) malloc(realoca * sizeof(int));
        
        for (int j = 0; j < serie[i].QuantidadeTemporadas; j++) {

            fscanf(arquivotexto, "%d,", &serie[i].QuantidadeEpisodiosPorTemporada[j]);
            IntAux = IntAux + serie[i].QuantidadeEpisodiosPorTemporada[j];
        
        }//for

         serie[i].QuantidadeEpisodiosTotais = IntAux;

    }//for

    MenuOpcoes = newwin(12, 30, yterminal / 2 + 1, (xterminal - 30) / 2);  //ponteiro da janela de opções

    keypad(MenuOpcoes, TRUE);  //habilita entrada de setas
    werase(MenuOpcoes);

    MenuSecundario(EntradaInfo);  

    endwin();
    return 0;

}

void MenuSecundario(WINDOW *EntradaInfo) {

    char *menuescolhas[] = {"Cadastrar", "Alterar", "Remover", "Listar series", "Listar por genero", "Pesquisar", "Plataforma mais assistida", "Genero mais assistido", "Salvar historico", "Sair"};  //matriz contendo as opções do menu
    typedef enum {cadastrarSerie = 0, alterarSerie, removerSerie, listarSeries, listarPorGenero, pesquisarSerie, plataformaMaisAssistida, generoMaisAssistido, salvarHistorico, sair} OpcoesSwitch;
    int opcoes = 10;
    int opcao;
    int highlight = 0;  //variável utilizada para representar a opção que está sendo selecionada dentro do menu

    while(1) { 
        
        cbreak();  //habilita a entrada imediata
        noecho();  //desabilita a escrita do usuário dentro do terminal
        curs_set(FALSE); //desabilita o cursor, limpa a janela e printa logo e menu com opções
    
        wclear(borda);
        wrefresh(borda);

        mvwprintw(borda, yborda / 2 - 7, (xborda - strlen(stringlogopt1)) / 2, "%s", stringlogopt1);
        mvwprintw(borda, yborda / 2 - 6, (xborda - strlen(stringlogopt2)) / 2, "%s", stringlogopt2);
        mvwprintw(borda, yborda / 2 - 5, (xborda - strlen(stringlogopt3)) / 2, "%s", stringlogopt3);
        mvwprintw(borda, yborda / 2 - 4, (xborda - strlen(stringlogopt4)) / 2, "%s", stringlogopt4);
    
        wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');  //desenha noavmente a borda da janela
        wrefresh(borda);

        for(int a = 0; a < opcoes; a++) {  //loop de print das opções do menu e atualização do efeito de seleção dentro do menu

            if(a == highlight) {

                wattron(MenuOpcoes, A_REVERSE);

            }

            mvwprintw(MenuOpcoes, a + 1, (30 - strlen(menuescolhas[a])) / 2, "%s", menuescolhas[a]);
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

                    case cadastrarSerie:
                    CadastrarSerie(EntradaInfo);
                    break;

                    case alterarSerie:
                    AlterarSerie(EntradaInfo);
                    break;

                    case removerSerie:
                    RemoverSerie(EntradaInfo);
                    break;

                    case listarSeries:
                    ListarSeries();
                    break;

                    case listarPorGenero:
                    ListarPorGenero(EntradaInfo);
                    break;

                    case pesquisarSerie:
                    PesquisarSerie(EntradaInfo);
                    break;

                    case plataformaMaisAssistida:
                    PlataformaMaisAssistida();
                    break;

                    case generoMaisAssistido:
                    GeneroMaisAssistido();
                    break;

                    case salvarHistorico:
                    SalvarHistorico(EntradaInfo);
                    break;
                    
                    case sair:
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

    setbuf(stdin, NULL); //configurações do ncurses para a função CadastrarSerie
    curs_set(TRUE);
    cbreak();
    echo();
    
    QuantidadeSeries++;  //aumenta em 1 a variável QuantidadeSeries para realocar o tamanho do vetor de struct que contém as séries
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

void ListarSeries() {

    keypad(borda, TRUE);
    cbreak();
    noecho();
    curs_set(FALSE);

    OpcoesMin = 0;
    OpcoesMax = yborda - 2;
    int highlight = 0;
    int opcao;
    int yopcao = 0;

    char *StringAux = (char*) malloc(sizeof(char) * 100);

    while (1) {
        
        wclear(borda);
        yopcao = 0;

        if(OpcoesMax > QuantidadeSeries) {

            OpcoesMax = QuantidadeSeries;

        }
        for (int a = OpcoesMin; a < OpcoesMax; a++) {
            
            if (a == highlight) {

                wattron(borda, A_REVERSE);

            }

            int x = (50 - strlen(serie[a].Nome)) / 2;
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
    
    char *StringAux1 = (char*) malloc(sizeof(char) * 500);

    strcpy(StringAux, " ");
    for(int a = 0; a < serie[highlight].QuantidadeTemporadas; a++) {

        if(a > 20) {

            break;

        }
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
                if(highlight >= QuantidadeSeries - 1) {

                    highlight = QuantidadeSeries - 1;
                        
                }
                if (highlight >= OpcoesMax) {

                    OpcoesMax = highlight + 1;

                    if(OpcoesMax > QuantidadeSeries) {

                        OpcoesMax = highlight - 1;

                    }
                    OpcoesMin = OpcoesMax - (yborda - 2);

                }
                break;

            case KEY_UP:
                highlight--;
                if (highlight < 0) {
                    
                    highlight = 0;

                }

                    if (highlight < OpcoesMin) {

                        OpcoesMin = highlight;
                        OpcoesMax = OpcoesMin + (yborda - 2);

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
    int ContadorGenero = 0;
    int ContadorQuantidadeSeries = 0;
    int IntAux;
    OpcoesMin = 0;
    OpcoesMax = yborda - 2;

    char *StringAux = (char*) malloc(sizeof(char) * 31);

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
    getnstr(StringAux, 31);
    setbuf(stdin, NULL);

    for(int a = 0; a < QuantidadeSeries; a++) {  //for
        
        for(int b = 0; b <= strlen(serie[a].Genero); b++) {  //for

            if(tolower(serie[a].Genero[b]) == tolower(StringAux[ContadorGenero])) { //if de comparação por caractere entre a string inserida pelo usuário e a string de genero da série

                ContadorGenero++;

            }//if #
            else {  //else

                ContadorGenero = 0;

            }  //else #

            if(ContadorGenero == strlen(StringAux)) {  //if

                IndicesSeries[ContadorQuantidadeSeries] = a;
                ContadorQuantidadeSeries++;
                IndicesSeries = (int*) realloc(IndicesSeries, sizeof(int) * (ContadorQuantidadeSeries + 1));
                ContadorGenero = 0;

            }  //if #
       
        }  //for #

    }  //for #

    // IndicesSeries = (int*) realloc(IndicesSeries, sizeof(int) * (ContadorQuantidadeSeries - 1));  //realoca para uma quantidade a menos após o loop pois o loop aloca de forma a obter um espaço a mais no vetor

    keypad(borda, TRUE);
    curs_set(FALSE);
    noecho();
    cbreak();

    int MaxSeriesPorPagina = yborda - 2;

    while (1) {

        wclear(borda);
        yopcao = 0;

        if(ContadorQuantidadeSeries < OpcoesMax) {

            OpcoesMax = ContadorQuantidadeSeries;
            MaxSeriesPorPagina = ContadorQuantidadeSeries;

        }

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

        wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
        IntAux = IndicesSeries[highlight];

        char *StringAux2 = (char*) malloc(sizeof(char) * 100);
        strcpy(StringAux2, "Nome: ");
        strcat(StringAux2, serie[IntAux].Nome);
        mvwprintw(borda, (yborda - 8) / 2 - 2, (xborda - strlen(StringAux2)) / 2, "%s", StringAux2);

        sprintf(StringAux2, "ID: %i", serie[IntAux].id);
        mvwprintw(borda, (yborda - 8) / 2, (xborda - strlen(StringAux2)) / 2, "%s", StringAux2);

        strcpy(StringAux2, "Genero: ");
        strcat(StringAux2, serie[IntAux].Genero);
        mvwprintw(borda, (yborda - 8) / 2 + 2, (xborda - strlen(StringAux2)) / 2, "%s", StringAux2);
    
        sprintf(StringAux2, "Classficacao: %i", serie[IntAux].Classificacao);
        mvwprintw(borda, (yborda - 8) / 2 + 3, (xborda - strlen(StringAux2)) / 2, "%s", StringAux2);
    
        strcpy(StringAux2, "Plataforma: ");
        strcat(StringAux2, serie[IntAux].Plataforma);
        mvwprintw(borda, (yborda - 8) / 2 + 4, (xborda - strlen(StringAux2)) / 2, "%s", StringAux2);
    
        sprintf(StringAux2, "Quantidade de temporadas: %i", serie[IntAux].QuantidadeTemporadas);
        mvwprintw(borda, (yborda - 8) / 2 + 5, (xborda - strlen(StringAux2)) / 2, "%s", StringAux2);
    
        sprintf(StringAux2, "Quantidade total de episodios: %i", serie[IntAux].QuantidadeEpisodiosTotais);
        mvwprintw(borda, (yborda - 8) / 2 + 6, (xborda - strlen(StringAux2)) / 2, "%s", StringAux2);
    
        char *StringAux1 = (char*) malloc(sizeof(char) * 500);

        strcpy(StringAux2, " ");
        for(int a = 0; a < serie[IntAux].QuantidadeTemporadas; a++) {

            if(a > 20) {
    
                break;

            }
            sprintf(StringAux1, "%i ", serie[IntAux].QuantidadeEpisodiosPorTemporada[a]);
            strcat(StringAux2, StringAux1);

        }
    
        strcpy(StringAux1, StringAux2);
        strcpy(StringAux2, "Quantidade de episodios por temporada:");
        strcat(StringAux2, StringAux1);
        mvwprintw(borda, (yborda - 8) / 2 + 7, (xborda - strlen(StringAux2)) / 2, "%s", StringAux2);

        sprintf(StringAux2, "Duracao media dos episodios: %i", serie[IntAux].DuracaoMediaEpisodios);
        mvwprintw(borda, (yborda - 8) / 2 + 8, (xborda - strlen(StringAux2)) / 2, "%s", StringAux2);

        sprintf(StringAux2, "Quantidade total de series encontradas: %i", ContadorQuantidadeSeries);
        mvwprintw(borda, (yborda - 8) / 2 + 10, (xborda - strlen(StringAux2)) / 2, "%s", StringAux2);

        sprintf(StringAux2, "Posicao: %i", highlight + 1);
        mvwprintw(borda, (yborda - 8) / 2 + 11, (xborda - strlen(StringAux2)) / 2, "%s", StringAux2);

        mvwprintw(borda, yborda - 2, (xborda - strlen("Pressione S para sair")) / 2, "Pressione S para sair");
        wrefresh(borda);

        mvwprintw(borda, yborda - 2, (xborda - strlen("Pressione S para sair")) / 2, "Pressione S para sair");
        wrefresh(borda);

        opcao = wgetch(MenuOpcoes);

        switch (opcao) {
            case KEY_DOWN:
                highlight++;
                if(highlight >= ContadorQuantidadeSeries - 1) {

                    highlight = ContadorQuantidadeSeries - 1;

                }
                if (highlight >= OpcoesMax) {

                    OpcoesMax = highlight + 1;
                    if(OpcoesMax > ContadorQuantidadeSeries) {

                        OpcoesMax = highlight + 1;

                    }
                    OpcoesMin = OpcoesMax - MaxSeriesPorPagina;

                }
            break;

            case KEY_UP:
                highlight--;
                if (highlight < 0) {

                    highlight = 0;

                }

                if (highlight < OpcoesMin) {

                    OpcoesMin = highlight;
                    OpcoesMax = OpcoesMin + MaxSeriesPorPagina;

                }

            break;

            case 's':
            free(StringAux1);
            free(StringAux2);
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

}  //ListarPorGenero #

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

void PlataformaMaisAssistida() {

    curs_set(FALSE);

    int *contagemPlataformas = (int*)calloc(QuantidadeSeries, sizeof(int));
    int contadorSeriesPlataforma = 0;
    StringAux = (char*) malloc(sizeof(char) * 100);

    // Percorre todas as séries e incrementa a contagem da plataforma correspondente
    for (int i = 0; i < QuantidadeSeries; i++)
    {
        contagemPlataformas[i] = 0;
        for (int j = 0; j < QuantidadeSeries; j++)
        {
            if (strcasecmp(serie[i].Plataforma, serie[j].Plataforma) == 0)
            {
                contagemPlataformas[i]++;
            }
        }
    }

    // Encontra o índice da plataforma mais assistida
    int indicePlataformaMaisAssistida = 0;
    for (int i = 1; i < QuantidadeSeries; i++)
    {

        if (contagemPlataformas[i] > contagemPlataformas[indicePlataformaMaisAssistida]) { 

            indicePlataformaMaisAssistida = i;

        }

    }

    for(int a = 0; a < QuantidadeSeries; a++) {

        if(strcasecmp(serie[a].Plataforma, serie[indicePlataformaMaisAssistida].Plataforma) == 0) {

            contadorSeriesPlataforma++;

        }

    }

    clear();
    refresh();
    wclear(borda);

    strcpy(StringAux, "A plataforma mais assistida eh: ");
    strcat(StringAux, serie[indicePlataformaMaisAssistida].Plataforma);
    mvwprintw(borda, yborda / 2, (xborda - strlen(StringAux)) / 2, StringAux);
    
    sprintf(StringAux, "A plataforma %s possui %i series cadastradas", serie[indicePlataformaMaisAssistida].Plataforma, contadorSeriesPlataforma);
    mvwprintw(borda, yborda / 2 + 1, (xborda - strlen(StringAux)) / 2, StringAux);

    mvwprintw(borda, yborda - 2, (xborda - strlen("Pressione qualquer tecla para prosseguir")) / 2, "Pressione qualquer tecla para prosseguir");

    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-'); 
    wrefresh(borda);
    getch();

    free(StringAux);
    free(contagemPlataformas);

    return;

}

void GeneroMaisAssistido() {

    curs_set(FALSE);

    int *contagemGeneros = (int*)calloc(QuantidadeSeries, sizeof(int));
    StringAux = (char*) malloc(sizeof(char) * 100);
    int contadorSeriesGenero = 0;

    // Percorre todas as séries e incrementa a contagem do gênero correspondente
    for (int i = 0; i < QuantidadeSeries; i++)
    {
        contagemGeneros[i] = 0;
        for (int j = 0; j < QuantidadeSeries; j++)
        {
                
            if(strcasecmp(serie[i].Genero, serie[j].Genero) == 0) {

                contagemGeneros[i]++;
                
            }

        }

    }

    // Encontra o índice do gênero mais assistido
    int indiceGeneroMaisAssistido = 0;
    for (int i = 1; i < QuantidadeSeries; i++)
    {
        if (contagemGeneros[i] > contagemGeneros[indiceGeneroMaisAssistido])
        {
            indiceGeneroMaisAssistido = i;
        }
    }

    for(int a = 0; a < QuantidadeSeries; a++) {

        if(strcasecmp(serie[a].Genero, serie[indiceGeneroMaisAssistido].Genero) == 0) {

            contadorSeriesGenero++;

        }

    }

    clear();
    refresh();
    wclear(borda);

    strcpy(StringAux, "O genero mais assistido eh: ");
    strcat(StringAux, serie[indiceGeneroMaisAssistido].Genero);
    mvwprintw(borda, yborda / 2, (xborda - strlen(StringAux)) / 2, StringAux);
    
    sprintf(StringAux, "O genero %s possui %i series cadastradas", serie[indiceGeneroMaisAssistido].Genero, contadorSeriesGenero);
    mvwprintw(borda, yborda / 2 + 1, (xborda - strlen(StringAux)) / 2, StringAux);

    mvwprintw(borda, yborda - 2, (xborda - strlen("Pressione qualquer tecla para prosseguir")) / 2, "Pressione qualquer tecla para prosseguir");

    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-'); 
    wrefresh(borda);
    getch();

    free(contagemGeneros);
    free(StringAux);

    return;

}

void SalvarHistorico(WINDOW *EntradaInfo) {

    curs_set(TRUE);
    echo();
    nocbreak();

    bool SerieEncontrada = FALSE;
    char serieBusca[60];
    int indiceHistorico = 0;
    StringAux = (char*) malloc(sizeof(char) * 100);

    ColetaNomeSalvarHistorico:
    clear();
    refresh();
    wclear(borda);
    wrefresh(borda);
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);
    wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(EntradaInfo);
    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite o nome da serie que deseja pesquisar")) / 2, "Digite o nome da serie que deseja pesquisar");
    wrefresh(borda);
    move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
    refresh();
    getnstr(serieBusca, 60);
    setbuf(stdin, NULL);
    curs_set(FALSE);

    for (int i = 0; i < QuantidadeSeries; i++)
    {

            if (strcasecmp(serieBusca,serie[i].Nome) == 0)
            {

                indiceHistorico++;
                SerieEncontrada = TRUE;

                wclear(borda);
                wclear(EntradaInfo);

                strcpy(StringAux, "Nome: ");
                strcat(StringAux, serie[i].Nome);
                mvwprintw(borda, (yborda - 8) / 2 - 2, (xborda - strlen(StringAux)) / 2, "%s", StringAux);

                sprintf(StringAux, "ID: %i", serie[i].id);
                mvwprintw(borda, (yborda - 8) / 2, (xborda - strlen(StringAux)) / 2, "%s", StringAux);

                strcpy(StringAux, "Genero: ");
                strcat(StringAux, serie[i].Genero);
                mvwprintw(borda, (yborda - 8) / 2 + 2, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
                sprintf(StringAux, "Classficacao: %i", serie[i].Classificacao);
                mvwprintw(borda, (yborda - 8) / 2 + 3, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
                strcpy(StringAux, "Plataforma: ");
                strcat(StringAux, serie[i].Plataforma);
                mvwprintw(borda, (yborda - 8) / 2 + 4, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
                sprintf(StringAux, "Quantidade de temporadas: %i", serie[i].QuantidadeTemporadas);
                mvwprintw(borda, (yborda - 8) / 2 + 5, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
    
                sprintf(StringAux, "Quantidade total de episodios: %i", serie[i].QuantidadeEpisodiosTotais);
                mvwprintw(borda, (yborda - 8) / 2 + 6, (xborda - strlen(StringAux)) / 2, "%s", StringAux);


                char *StringAux1 = (char*) malloc(sizeof(char) * 500);

                strcpy(StringAux, " ");
                for(int a = 0; a < serie[i].QuantidadeTemporadas; a++) {

                    if(a > 20) {

                        break;

                    }
                    sprintf(StringAux1, "%i ", serie[i].QuantidadeEpisodiosPorTemporada[a]);
                    strcat(StringAux, StringAux1);

                }
    
                strcpy(StringAux1, StringAux);
                strcpy(StringAux, "Quantidade de episodios por temporada:");
                strcat(StringAux, StringAux1);
                mvwprintw(borda, (yborda - 8) / 2 + 7, (xborda - strlen(StringAux)) / 2, "%s", StringAux);

                sprintf(StringAux, "Duracao media dos episodios: %i", serie[i].DuracaoMediaEpisodios);
                mvwprintw(borda, (yborda - 8) / 2 + 8, (xborda - strlen(StringAux)) / 2, "%s", StringAux);
                mvwprintw(borda, yborda - 2, (xborda - strlen("Pressione qualquer tecla para prosseguir")) / 2, "Pressione qualquer tecla para prosseguir");
                wrefresh(borda);

                free(StringAux1);

                wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
                wrefresh(borda);

                // for (int j = 0; j < serie[i].QuantidadeTemporadas; j++) 
                // {
                //     printf("%d ", serie[i].QuantidadeEpisodiosPorTemporada[j]);
                // }
                // printf("\n \n \n");

                historico=(Historico*)realloc(historico,indiceHistorico * sizeof(Historico));
                getch();
                // strcpy(historico[indiceHistorico].Nome,serie[i].Nome);

                // printf("digite a ultima temporada assistida: ");
                // scanf("%d",&historico[indiceHistorico].UltimaTemporada);

                // printf("digite o ultimo Episodio assistido: ");
                // scanf("%d",&historico[indiceHistorico].UltimoEpisodio);

                // printf("Os dados do historico da serie %s foi atualizado!! ",historico[indiceHistorico].Nome); 
                break;

            }//if


    }//for

    // if (SerieEncontrada == FALSE)
    // {

    //     printf("Não há séries com esse nome !! Tente novamente.\n");
    //     goto ColetaNomeSalvarHistorico;

    // }//if

    return;

}
