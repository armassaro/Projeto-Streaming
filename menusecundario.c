#include "projetostreaming.h"

void main() {

    //printa novamente a arte ASCII do menu inicial
    mvwprintw(borda, yborda / 2 - 7, xborda / 2 - 30, "%s", stringlogopt1);
    mvwprintw(borda, yborda / 2 - 6, xborda / 2 - 30, "%s", stringlogopt2);
    mvwprintw(borda, yborda / 2 - 5, xborda / 2 - 30, "%s", stringlogopt3);
    mvwprintw(borda, yborda / 2 - 4, xborda / 2 - 30, "%s", stringlogopt4);

    wrefresh(borda);

    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');  //desenha noavmente a borda da janela

    wrefresh(borda);

    keypad(menuopcoes, TRUE);  //habilita entrada de setas
    werase(menuopcoes);

    char *menuescolhas[] = {"Busca", "Sair"};
    int opcoes = 2;
    int opcao;
    int highlight = 0;

    opcao = wgetch(menuopcoes);


}
