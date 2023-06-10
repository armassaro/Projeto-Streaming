#include "projetostreaming.h"
#include <time.h>

int main() { 

    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    getmaxyx(stdscr, yterminal, xterminal);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    srand(time(NULL));

    typedef struct {

        int x;
        int y;

    } Coordenadas;

    Coordenadas corpo[100];

    bool vida = TRUE;
    corpo[0].x = xterminal / 2;
    corpo[0].y = yterminal / 2;
    int UltimaTecla;
    int UltimaTecla1 = KEY_RIGHT;
    int TamanhoSnake = 2;
    int velocidade = 80000;
    int ComidaY, ComidaX;

    ComidaY = rand() % (yterminal - 2);
    ComidaX = rand() % (xterminal - 2);

    while(vida == TRUE) {

        if(TamanhoSnake >= 2) {

            clear();
            for(int a = 0; a < TamanhoSnake; a++) {

                mvprintw(corpo[a].y, corpo[a].x, "#");

            }

        }

        mvprintw(ComidaY, ComidaX, "+");
        usleep(velocidade);
        refresh();

        UltimaTecla = getch();

        if(UltimaTecla != ERR) {
            
            UltimaTecla1 = UltimaTecla;

        }

        switch(UltimaTecla1) {

            case KEY_RIGHT:
            corpo[0].x = corpo[0].x + 1;
            break;

            case KEY_LEFT:
            corpo[0].x = corpo[0].x - 1;
            break;

            case KEY_DOWN:
            corpo[0].y = corpo[0].y + 1;
            usleep(2500);
            break;

            case KEY_UP:
            corpo[0].y = corpo[0].y - 1;
            usleep(2500);
            break;
            
        }

        for(int a = TamanhoSnake - 1; a > 0; a--) {

            corpo[a] = corpo[a - 1];

        }

        if(mvinch(corpo[0].y, corpo[0].x) == '+') {

            ComidaY = rand() % (yterminal - 2);
            ComidaX = rand() % (xterminal - 2);

            TamanhoSnake = TamanhoSnake + 1;

            velocidade = velocidade - 2000;

        }

        if(mvinch(corpo[0].y, corpo[0].x) == '#') {

            vida = FALSE;

        }

    }

    setbuf(stdin, NULL);
    nocbreak();
    clear();
    mvprintw(yterminal / 2, (xterminal - strlen("Fim de jogo")) / 2, "Fim de jogo");
    refresh();
    getch();
    
    endwin();
    return 0;

}
