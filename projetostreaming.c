#include "projetostreaming.h"

int main() {

    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);

    getmaxyx(stdscr, yterminal, xterminal);

    mvprintw(yterminal / 2, xterminal / 2 - 4, "Carregando...\n");
    mvprintw((yterminal / 2) - 2, 2, "[");
    mvprintw((yterminal / 2) - 2, xterminal - 2, "]");
    refresh();

    for(int a = 4; a <= xterminal - 4; a++) {  //tela de carregamento

        mvprintw((yterminal / 2) - 2, a, ">");
        
        refresh();
        usleep(20000);

        mvprintw((yterminal / 2) - 2, a, "|");

        refresh();

        usleep(5000);

    }

    for(int a = 4; a <= xterminal - 4; a++) {  //preenche risco com hashtag

        mvprintw((yterminal / 2) - 2, a, "#");
        
        refresh();

        usleep(6000);

    }

    clear();

    mvprintw((yterminal / 2) - 2, xterminal / 2, "#");

    for(int a = yterminal / 2; a <= yterminal - 4; a++) {  //move um asterisco centralizado pra baixo

        mvprintw(a, xterminal / 2, "#");
        
        refresh();

        usleep(10000);

        clear();

    }

    for(int a = xterminal / 2; a <= xterminal - 4; a++) {  //move o asterisco pra direita

        mvprintw(yterminal - 4, a, "#");
        
        refresh();

        usleep(10000);

        clear();

    }

    for(int a = yterminal - 4; a >= 4; a--) {  //sobe e preenche coluna direita

        mvprintw(a, xterminal - 4, "#");
        
        refresh();

        usleep(10000);

    }

    for(int a = xterminal - 4; a >= 4; a--) {  //vai pra esquerda e preenche linha de cima

        mvprintw(4, a, "-");
        refresh();

        usleep(10000);

    }

    for(int a = 5; a <= yterminal - 4; a++) {  //preenche coluna esquerda

        mvprintw(a, 4, "#");
        
        refresh();

        usleep(10000);

    }

    for(int a = 4; a <= xterminal - 4; a++) {  //preenche linha inferior

        mvprintw(yterminal - 4, a, "-");
        refresh();

        usleep(10000);

    }

    WINDOW *borda = newwin(yterminal - 7, xterminal - 7, 4, 4);

    int xborda, yborda;  //variáveis utilizadas para armazenar as dimensões da borda da janela

    char *stringlogopt1 = "  __                                                             \n";
    char *stringlogopt2 = " (_ _|_ ._ _   _. ._ _  o ._   _    |\\/|  _. ._   _.  _   _  ._ \n";
    char *stringlogopt3 = " __) |_ | (/_ (_| | | | | | | (_|   |  | (_| | | (_| (_| (/_ |   \n";
    char *stringlogopt4 = "                               _|                     _|         \n";


    getmaxyx(borda, yborda, xborda);

    mvwprintw(borda, yborda / 2 - 7, xborda / 2 - 30, "%s", stringlogopt1);
    mvwprintw(borda, yborda / 2 - 6, xborda / 2 - 30, "%s", stringlogopt2);
    mvwprintw(borda, yborda / 2 - 5, xborda / 2 - 30, "%s", stringlogopt3);
    mvwprintw(borda, yborda / 2 - 4, xborda / 2 - 30, "%s", stringlogopt4);

    wrefresh(borda);

    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');

    wrefresh(borda);

    WINDOW *menuopcoes = newwin(10, 15, yterminal / 2 + 1, xterminal / 2 - 5);
    refresh();

    char *menuescolhas[] = {"Iniciar", "Sair"};
    int opcoes = 2;
    int opcao;
    int highlight = 0;

    keypad(menuopcoes, TRUE);
    werase(menuopcoes);

    while(1) {

        for(int a = 0; a < opcoes; a++) {

            if(a == highlight) {

                wattron(menuopcoes, A_REVERSE);

            }

            int x = (15 - strlen(menuescolhas[a])) / 2;
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
            if(highlight >= opcoes) {

                highlight = opcoes - 1;

            }
            break;

            case '\n': 
            
            if (highlight == 0) {
                
                clear();
                refresh();

                arquivobin = fopen("arquivobin.dat", "rb");

                if(arquivobin == NULL) {

                    wclear(stdscr);
                    wclear(borda);
                    MensagemBoasVindas(yterminal, xterminal, borda, yborda, xborda);

                }

                endwin();
                return 0;

            }
            if(highlight == 1) {

                return 0;

            }
            break;
        }

    }

    curs_set(FALSE);

    endwin();

    return 0;

}

void MensagemBoasVindas(int yterminal, int xterminal, WINDOW *borda, int yborda, int xborda) {

    refresh();
    wclear(borda);
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');  //printa de novo a borda da janela
    wrefresh(borda);  //atualiza a borda 

    char *mensagem1 = "Seja bem vindo ao Streaming Manager!";
    char *mensagem2 = "O Streaming Manager eh um projeto desenvolvido pelos alunos Arthur Massaro, Pedro Lorin e Matheus Conrado";
    char *mensagem3 = "Por meio deste programa, eh possivel gerenciar suas series favoritas!";
    char *mensagem4 = "Eh possivel cadastrar, alterar, remover e listar mais de 250 series dentre as plataformas mais populares como Netflix, Amazon Prime Video e HBO Max!";
    char *mensagem5 = "Parece que nao existe um arquivo contendo os dados das series... Gostaria de criar um agora?";

    char *opcoesNome[] = {"Sim", "Nao"};

    curs_set(TRUE);

    int x;

    x = (xborda - strlen(mensagem1)) / 2; //variável utilizada no cálculo da centralização da mensagem

    for(int a = 0; a <= strlen(mensagem1) - 1; a++) {  //printa na tela a mensagem 1

        mvwaddch(borda, yborda / 2 - 5, a + x, mensagem1[a]);
        wmove(borda, yborda / 2 - 5, a + x + 1);
        wrefresh(borda);
        usleep(30000);

    }

    x = (xborda - strlen(mensagem2)) / 2;

    for(int a = 0; a <= strlen(mensagem2) - 1; a++) {  //printa na tela a mensagem 2

        mvwaddch(borda, yborda / 2 - 3, a + x, mensagem2[a]);
        wmove(borda, yborda / 2 - 3, a + x + 1);
        wrefresh(borda);
        usleep(30000);

    }

    x = (xborda - strlen(mensagem3)) / 2;

    for(int a = 0; a <= strlen(mensagem3) - 1; a++) {  //printa na tela a mensagem 3

        mvwaddch(borda, yborda / 2 - 2, a + x, mensagem3[a]);
        wmove(borda, yborda / 2 - 2, a + x + 1);
        wrefresh(borda);
        usleep(30000);

    }

    x = (xborda - strlen(mensagem4)) / 2;

    for(int a = 0; a <= strlen(mensagem4) - 1; a++) {  //printa na tela a mensagem 4

        mvwaddch(borda, yborda / 2 - 1, a + x, mensagem4[a]);
        wmove(borda, yborda / 2 - 1, a + x + 1);
        wrefresh(borda);
        usleep(30000);

    }

    x = (xborda - strlen(mensagem5)) / 2;

    for(int a = 0; a <= strlen(mensagem5) - 1; a++) {  //printa na tela a mensagem 5

        mvwaddch(borda, yborda / 2 + 1, a + x, mensagem5[a]);
        wmove(borda, yborda / 2 + 1, a + x + 1);
        wrefresh(borda);
        usleep(30000);

    }

    curs_set(FALSE);

    WINDOW *AlternativaSimNao = newwin(1, 153, (yborda / 2) + 7, 8); 

    int opcoes = 2;
    int opcao;
    int highlight = 0;
    keypad(AlternativaSimNao, TRUE);  //habilita as setas como entrada do teclado
    werase(AlternativaSimNao);

    while(1) {

        for(int a = 0; a < opcoes; a++) {  //imprime sim e nao

            if(a == highlight) {

                wattron(AlternativaSimNao, A_REVERSE);

            }

            if(a == 0) {
                
                mvwprintw(AlternativaSimNao, 0, 42, "%s", opcoesNome[a]);
                wattroff(AlternativaSimNao, A_REVERSE);
            
            }
            else {

                mvwprintw(AlternativaSimNao, 0, 108, "%s", opcoesNome[a]);
                wattroff(AlternativaSimNao, A_REVERSE);

            }
        }

        opcao = wgetch(AlternativaSimNao);

        switch(opcao) {

            case KEY_RIGHT:
            highlight++;
            if(highlight > 1) {

                highlight = 1;

            }
            break;

            case KEY_LEFT:
            highlight--;
            if(highlight < 0) {

                highlight = 0;

            }
            break;

            case '\n': 
            
            if (highlight == 0) {
                
                wclear(AlternativaSimNao);
                wprintw(AlternativaSimNao, "sucesso");
                wrefresh(AlternativaSimNao);
                getch();
                endwin();
                exit(1);

            }
            if(highlight == 1) {

                exit(1);

            }
            break;
        }

    }

    getch();

    return;

}
