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

    refresh();
    clear();
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    mvprintw(yterminal / 2, xterminal / 2, "Transferência de informações entre arquivos, aguarde um momento...");
    refresh();

    // LOOP DE TRANSFERENCIA DE INFORMAÇÃOES ENTRE ARQUIVOS

    menuopcoes = newwin(8, 23, yterminal / 2 + 1, xterminal / 2 - 9);
    
    wclear(borda);
    //printa novamente a arte ASCII do menu inicial


    char *menuescolhas[] = {"Cadastrar", "Alterar", "Remover", "Listar as series", "Listar por genero", "Sair"};
    int opcoes = 6;
    int opcao;
    int highlight = 0;

    keypad(menuopcoes, TRUE);  //habilita entrada de setas
    werase(menuopcoes);

    while(1) {

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
            if(highlight >= opcoes) {  // if que garante que o usuário não selecione opções fora do menu

                highlight = opcoes - 1;

            }
            break;

            case '\n':  //case que representa o que cada opção faz
            if (highlight == 0) {

                CadastrarSerie(EntradaInfo);

            }

            if(highlight == 1) {  //se o usuário optar pela opção "não", sai do programa

                AlterarSerie(EntradaInfo);

            }
            if(highlight == 3) {

                clear();
                wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');  //desenha novamente a borda da janela
                wrefresh(borda);

                
            }
            if(highlight == 5) {

                clear();
                refresh();
                endwin();
                exit(0);

            }
            break;
        }

    }


}

void CadastrarSerie(WINDOW *EntradaInfo) {

    wclear(borda);
    wrefresh(borda);
    curs_set(TRUE);
    nocbreak();
    echo();

    QuantidadeSeries = QuantidadeSeries + 1;

    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);

    wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(EntradaInfo);

    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite o nome da serie a ser cadastrada")) / 2, "Digite o nome da serie a ser cadastrada");
    wrefresh(borda);
    move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
    getch();

    clear();
    refresh();
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);
    wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(EntradaInfo);
    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite o genero da serie a ser cadastrada")) / 2, "Digite o genero da serie a ser cadastrada");
    wrefresh(borda);
    move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
    getch();

    clear();
    refresh();
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);
    wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(EntradaInfo);
    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite a idade da classificacao da serie a ser cadastrada")) / 2, "Digite a idade da classificacao da serie a ser cadastrada");
    wrefresh(borda);
    move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
    getch();

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
    getch();

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
    getch();

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
    getch();

    clear();
    refresh();
    wclear(borda);
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(borda);
    wborder(EntradaInfo, '#', '#', '-', '-', '-', '-', '-', '-');
    wrefresh(EntradaInfo);
    mvwprintw(borda, yborda / 2 - 3, (xborda - strlen("Digite a quantidade de episodios por temporada da serie a ser cadastrada")) / 2, "Digite a quantidade de episodios por temporada da serie a ser cadastrada");
    wrefresh(borda);
    move(yterminal / 2 + 1, (xterminal - (xborda - 30)) / 2 + 2);
    getch();

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
    getch();

    return;

}

void ListarPorGenero() {

    wclear(menuopcoes);
    wborder(menuopcoes, '#', '#', '-', '-', '-', '-', '-', '-');

    char *menuescolhas[] = {"Western Espacial", "Drama", "Fantasia", "Humor Ácido", "Suspense", "Ficção Cientifica", "Drama médico", "Comedia", "Ação", "Comédia", "Ficção ", "Terror/Drama", "Criança", "comédia", "Terror", "Documentário", "Ação ", "Ficção Científica", "Mistério", "Drama Médico", "terror", "drama", "Sitcom", "Fantasia Cientifíca", "Crime Drama", "Comédia/Romance", "Misterio ", "Suspense / Fantasia", "Infantil", "Humor", "Drama / Ação", "Drama / Suspense", "Açao", "Superhero", "Crime Real", "Comédia/Animação", "Comédia/Sitcom", "Suspense/Ação", "Comédia Dramatica", "Crime", "Drama Mistério", "Policial", "Sticom", "Ficção cientifica", "Ação/Super Heroi", "Sci-Fi", "Ficção científica", "Reality Show", "Suspense / Drama", "Comédia/Politica", "Drama/Terror", "Suspence", "Ficção", "Ação/Aventura"};
    int opcoes = sizeof(*menuescolhas);
    int opcao;
    int highlight = 0;

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
            if(highlight >= opcoes) {  // if que garante que o usuário não selecione opções fora do menu

                highlight = opcoes - 1;

            }
            break;
}
}
