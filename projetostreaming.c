#include "projetostreaming.h"

/* Este arquivo contém as animações de introdução e mensagem de boas-vindas caso o programa não detecte os 
arquivos necessários para rodar o mesmo. Caso o programa encontre os arquivos, este programa fecha e prossegue para o arquivo
menusecundario.c, que abriga o menu com as opções de leitura, cadastro, procura e etc. */

int main() {

    initscr();  //inicia o modo ncurses
    cbreak();  //faz com que a entrada que o usuário enviar para o programa seja imediatamente lida, sem necessidade de dar enter
    noecho();  //desabilita a visualização da entrada do teclado do usuário no terminal
    curs_set(FALSE);  //desabilita a visualização do cursor dentro do temrinal

    getmaxyx(stdscr, yterminal, xterminal);  //coleta as dimensões máximas da janela do terminal

    // mvprintw(yterminal / 2, xterminal / 2 - 4, "Carregando...\n");  //animação de carregamento inicial
    // mvprintw((yterminal / 2) - 2, 2, "[");
    // mvprintw((yterminal / 2) - 2, xterminal - 2, "]");
    // refresh();

    // for(int a = 4; a <= xterminal - 4; a++) {  //tela de carregamento

    //     mvprintw((yterminal / 2) - 2, a, ">");
        
    //     refresh();
    //     usleep(20000);

    //     mvprintw((yterminal / 2) - 2, a, "|");

    //     refresh();

    //     usleep(5000);

    // }

    // for(int a = 4; a <= xterminal - 4; a++) {  //preenche os riscos printados com hashtag

    //     mvprintw((yterminal / 2) - 2, a, "#");
        
    //     refresh();

    //     usleep(6000);

    // }

    // clear();  //limpa o terminal 

    // mvprintw((yterminal / 2) - 2, xterminal / 2, "#");  //printa o primeiro hashtag centralizado na tela

    // for(int a = yterminal / 2; a <= yterminal - 4; a++) {  //move um hashtag centralizado pra baixo

    //     mvprintw(a, xterminal / 2, "#");
        
    //     refresh();

    //     usleep(10000);

    //     clear();

    // }

    // for(int a = xterminal / 2; a <= xterminal - 4; a++) {  //move o hashtag pra direita

    //     mvprintw(yterminal - 4, a, "#");
        
    //     refresh();

    //     usleep(10000);

    //     clear();

    // }

    // for(int a = yterminal - 4; a >= 4; a--) {  //sobe e preenche coluna direita com hashtag

    //     mvprintw(a, xterminal - 4, "#");
        
    //     refresh();

    //     usleep(10000);

    // }

    // for(int a = xterminal - 4; a >= 4; a--) {  //vai pra esquerda e preenche linha de cima com traço

    //     mvprintw(4, a, "-");
    //     refresh();

    //     usleep(10000);

    // }

    // for(int a = 5; a <= yterminal - 4; a++) {  //desce e preenche coluna esquerda com hashtag

    //     mvprintw(a, 4, "#");
        
    //     refresh();

    //     usleep(10000);

    // }

    // for(int a = 4; a <= xterminal - 4; a++) {  //vai pra direita e preenche linha inferior com traço

    //     mvprintw(yterminal - 4, a, "-");
    //     refresh();

    //     usleep(10000);

    // }

    borda = newwin(yterminal - 7, xterminal - 7, 4, 4);  //cria janela para representar a borda desenhada após as animações executadas

    getmaxyx(borda, yborda, xborda);  //coleta as dimensões máximas da janela de borda

    mvwprintw(borda, yborda / 2 - 7, xborda / 2 - 30, "%s", stringlogopt1);  //printa arte ASCII com nome "Streaming Manager"
    mvwprintw(borda, yborda / 2 - 6, xborda / 2 - 30, "%s", stringlogopt2);
    mvwprintw(borda, yborda / 2 - 5, xborda / 2 - 30, "%s", stringlogopt3);
    mvwprintw(borda, yborda / 2 - 4, xborda / 2 - 30, "%s", stringlogopt4);

    wrefresh(borda);

    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');  //desenha a borda da janela

    wrefresh(borda);

    menuopcoes = newwin(10, 15, yterminal / 2 + 1, xterminal / 2 - 5);  //cria uma janela para abrigar as opções do menu inicial
    refresh();

    char *menuescolhas[] = {"Iniciar", "Sair"};
    int opcoes = 2;
    int opcao;  //variável que representa a opção escolhida
    int highlight = 0;

    keypad(menuopcoes, TRUE);  //habilita coleta de setas do teclado
    werase(menuopcoes);

    while(1) {  //loop de seleção das opções dentro do menu

        for(int a = 0; a < opcoes; a++) {  //loop de print das opções do menu e atualização do efeito de seleção dentro do menu

            if(a == highlight) {

                wattron(menuopcoes, A_REVERSE);

            }

            int x = (15 - strlen(menuescolhas[a])) / 2;
            mvwprintw(menuopcoes, a + 1, x, "%s", menuescolhas[a]);
            wattroff(menuopcoes, A_REVERSE);

        }

        wborder(menuopcoes, '#', '#', '-', '-', '-', '-', '-', '-');
        wrefresh(menuopcoes);

        opcao = wgetch(menuopcoes);  //coleta a entrada do usuário dentro da janela menuopcoes

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
                
                clear();
                refresh();

                arquivobinSeries = fopen("arquivobinSeries.dat", "rb");  //tenta abrir o arquivo binário de séries

                if(arquivobinSeries == NULL) {  //caso falhar, limpa a tela e direciona para a mensagem de boas-vidas

                    wclear(stdscr);
                    wclear(borda);
                    MensagemBoasVindas();

                }

                endwin();
                return 0;

            }
            if(highlight == 1) {  //se o usuário optar pela opção "não", sai do programa

                endwin();
                return 0;

            }
            break;
        }

    }

    endwin();  //fecha o modo ncurses

    return 0;

}

void MensagemBoasVindas() {

    refresh();
    wclear(borda);
    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');  //printa de novo a borda da janela
    wrefresh(borda);  //atualiza a borda 

    // as mensagens são declaradas como strings para que seja possível printar um caractere por vez gerando a animação na mensagem de boas-vindas
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

    WINDOW *AlternativaSimNao = newwin(1, 153, (yborda / 2) + 7, 8);  //cria janela para abrigar as opções de sim ou não

    int opcoes = 2;
    int opcao;
    int highlight = 0;
    keypad(AlternativaSimNao, TRUE);  //habilita as setas como entrada do teclado
    werase(AlternativaSimNao);

    while(1) {

        for(int a = 0; a < opcoes; a++) {  //loop que imprime sim e nao

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

        opcao = wgetch(AlternativaSimNao);  //entrada de caractere

        switch(opcao) {  //switch que alterna o efeito de highlight da opção entre as opções disponíveis no menu

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
                
                wclear(borda);
                arquivobinSeries = fopen("arquivobinSeries.dat", "wb");
                arquivobinHistorico = fopen("arquivobinHistorico.dat", "wb");
                arquivotexto = fopen("streaming_db.txt", "r");

                if(arquivobinSeries == NULL) {  //printa o retorno do ponteiro de arquivo binário das séries

                    clear();
                    refresh();
                    x = (xborda - strlen("Houve um erro na criação do arquivo binário de séries. Pressione qualquer tecla.")) / 2;
                    mvwprintw(borda, yborda / 2 - 2, x, "Houve um erro na criação do arquivo binário de séries. Pressione qualquer tecla.");
                    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
                    wrefresh(borda);
                
                }
                else {

                    clear();
                    refresh();
                    x = (xborda - strlen("O arquivo binário de séries foi criado com sucesso!")) / 2;
                    mvwprintw(borda, yborda / 2 - 2, x, "O arquivo binário de séries foi criado com sucesso!");
                    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
                    wrefresh(borda);

                }

                if(arquivobinHistorico == NULL) {  //printa o retorno do ponteiro de arquivo binário do histórico

                    clear();
                    refresh();
                    x = (xborda - strlen("Houve um erro na criação do arquivo binário de histórico. Pressione qualquer tecla.")) / 2;
                    mvwprintw(borda, yborda / 2 - 1, x, "Houve um erro na criação do arquivo binário de histórico. Pressione qualquer tecla.");
                    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
                    wrefresh(borda);
                
                }
                else {

                    clear();
                    refresh();
                    x = (xborda - strlen("O arquivo binário de histórico foi criado com sucesso!")) / 2;
                    mvwprintw(borda, yborda / 2 - 1, x, "O arquivo binário de histórico foi criado com sucesso!");
                    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
                    wrefresh(borda);

                }

                if(arquivotexto == NULL) {  //printa o retorno do ponteiro de arquivo fonte dos dados das séries

                    clear();
                    refresh();
                    x = (xborda - strlen("Houve um erro na leitura do arquivo fonte de dados das séries. Pressione qualquer tecla.")) / 2;
                    mvwprintw(borda, yborda / 2, x, "Houve um erro na leitura do arquivo fonte de dados das séries. Pressione qualquer tecla.");
                    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
                    wrefresh(borda);
                
                }
                else {

                    clear();
                    refresh();
                    x = (xborda - strlen("O arquivo fonte de dados das séries foi lido com sucesso!")) / 2;
                    mvwprintw(borda, yborda / 2, x, "O arquivo fonte de dados das séries foi lido com sucesso!");
                    wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
                    wrefresh(borda);

                }

                if(arquivobinHistorico == NULL || arquivobinSeries == NULL || arquivotexto == NULL) {  //se houver qualquer tipo de erro na abertura de qualquer arquivo, sai do programa

                    getch();
                    endwin();
                    exit(1);

                }

                for (int i = 0; i < QuantidadeSeries; i++) {
                    
                    fwrite(&serie[i].id,sizeof(int),1,arquivobinSeries);
           
                    fwrite(serie[i].Nome,sizeof(char),101,arquivobinSeries);
              
                    fwrite(serie[i].Genero,sizeof(char),41,arquivobinSeries);
               
                    fwrite(&serie[i].Classificacao,sizeof(int),1,arquivobinSeries);
           
                    fwrite(serie[i].Plataforma,sizeof(char),41,arquivobinSeries);
       
                    fwrite(&serie[i].DuracaoMediaEpisodios,sizeof(int),1,arquivobinSeries);
             
                    fwrite(&serie[i].QuantidadeTemporadas,sizeof(int),1,arquivobinSeries);
               

                    for (int j = 0; j < serie[i].QuantidadeTemporadas; j++) {
                        
                        fwrite(&serie[i].QuantidadeEpisodiosPorTemporada[j],sizeof(int),1,arquivobinSeries);
                        
                        }//for
                        
                }//for
    
                fclose(arquivobinSeries);

                clear();
                refresh();
                x = (xborda - strlen("Os arquivos foram lidos e criados com sucesso, pressione qualquer tecla para prosseguir")) / 2;
                mvwprintw(borda, yborda / 2 + 1, x, "Os arquivos foram lidos e criados com sucesso, pressione qualquer tecla para prosseguir");
                wborder(borda, '#', '#', '-', '-', '-', '-', '-', '-');
                wrefresh(borda);
                getch();
                wclear(borda);
                return;  //volta pra linha 191

            }

            if(highlight == 1) {  //caso selecionado não, sai do programa

                endwin();
                exit(0);

            }
            break;
        }

    }

}
