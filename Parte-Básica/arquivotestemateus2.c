#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {

    int id;
    char Nome[101];
    char Genero[41];
    int Classificacao;
    char Plataforma[41];
    int QuantidadeTemporadas;
    int QuantidadeEpisodiosTotais;
    int *QuantidadeEpisodiosPorTemporada;
    int DuracaoMediaEpisodios;

} Serie;
    


typedef struct {

    char Nome[101];
    int UltimaTemporadaAssistida;
    int UltimoEpisodio;
    
} Historico;

int salvaHistorico (Serie *serie, int QuantidadeSeries,  Historico *historico, int indiceHistorico)
{ 
    int contadorSerie = 0;
    char serieBusca[41];

    printf("Digite o Nome da serie que deseja  no historico:\n");

    setbuf(stdin, NULL);
    fgets(serieBusca, sizeof(serieBusca), stdin);
    serieBusca[strcspn(serieBusca, "\n")] = '\0';
    setbuf(stdin, NULL);

    for (int i = 0; i < QuantidadeSeries; i++)
    {   
       
            

            if (strcasecmp(serieBusca,serie[i].Nome) == 0)
            {
                
                indiceHistorico ++;
                  printf("Aqui estao os dados bases da serie pesquisada\n\n"); 
                contadorSerie++;
                printf("%d-", serie[i].id);
                printf("%-40s " , serie[i].Nome);
                printf("Genero:%-20s ", serie[i].Genero);
                printf("Classificacao:%-5d ", serie[i].Classificacao);
                printf("Plataforma:%-15s ", serie[i].Plataforma);
                printf("Duracao media por ep:%-5d ", serie[i].DuracaoMediaEpisodios);
                printf("Quantidade de temporadas:%-5d ", serie[i].QuantidadeTemporadas);           
                printf("episodios por temporada: ");


                for (int j = 0; j < serie[i].QuantidadeTemporadas; j++) 
                {
                    printf("%d ", serie[i].QuantidadeEpisodiosPorTemporada[j]);
                }
                printf("\n \n \n");
                
                historico=(Historico*)realloc(historico,indiceHistorico * sizeof(Historico));

                strcpy(historico[indiceHistorico].Nome,serie[i].Nome);


                printf("digite a ultima temporada assistida: ");
                scanf("%d",&historico[indiceHistorico].UltimaTemporadaAssistida);

                printf("digite o ultimo Episodio assistido: ");
                scanf("%d",&historico[indiceHistorico].UltimoEpisodio);
            
               
                
                printf("Os dados do historico da serie %s foi atualizado!! ",historico[indiceHistorico].Nome); 
                 break;
            }//if
        
        
    }//for

    if (contadorSerie == 0)
    {
        printf("Não há séries com esse nome !! Tente novamente.\n");
      salvaHistorico(serie,QuantidadeSeries,historico,indiceHistorico);
    }//if






        return indiceHistorico;



}//int salvaHistorico

void lerSeriesBinario (Serie *serie, int QuantidadeSeries, FILE *arquivo) {

    for (int i = 0; i < QuantidadeSeries; i++) 
    {
        serie[i].QuantidadeEpisodiosTotais = 0;

        fread(&serie[i].id, sizeof(int), 1, arquivo);
        fread(serie[i].Nome, sizeof(char), 101, arquivo);
        fread(serie[i].Genero, sizeof(char), 41, arquivo);
        fread(&serie[i].Classificacao, sizeof(int), 1, arquivo);
        fread(serie[i].Plataforma, sizeof(char), 41, arquivo);
        fread(&serie[i].DuracaoMediaEpisodios, sizeof(int), 1, arquivo);
        fread(&serie[i].QuantidadeTemporadas, sizeof(int), 1, arquivo);

        int realoca = serie[i].QuantidadeTemporadas;
        serie[i].QuantidadeEpisodiosPorTemporada = (int*) malloc(realoca * sizeof(int));
        
        for (int j = 0; j < serie[i].QuantidadeTemporadas; j++) {

            fread(&serie[i].QuantidadeEpisodiosPorTemporada[j], sizeof(int), 1, arquivo);
      
            serie[i].QuantidadeEpisodiosTotais=serie[i].QuantidadeEpisodiosTotais+serie[i].QuantidadeEpisodiosPorTemporada[j];
        }//for
    }//for
}//void lerseriesBinario

void lerSeries(Serie *serie, int QuantidadeSeries, FILE *arquivo) {

    for (int i = 0; i < QuantidadeSeries; i++) 
    {
        serie[i].QuantidadeEpisodiosTotais = 0;

        fscanf(arquivo, "%d,", &serie[i].id);
        fscanf(arquivo, "%[^,\n],", serie[i].Nome);
        fscanf(arquivo, "%[^,\n],", serie[i].Genero);
        fscanf(arquivo, "%d,", &serie[i].Classificacao);
        fscanf(arquivo, "%[^,\n],", serie[i].Plataforma);
        fscanf(arquivo, "%d,", &serie[i].DuracaoMediaEpisodios);
        fscanf(arquivo, "%d,", &serie[i].QuantidadeTemporadas);

        int realoca = serie[i].QuantidadeTemporadas;
        serie[i].QuantidadeEpisodiosPorTemporada = (int*) malloc(realoca * sizeof(int));
                                                                                        
        for (int j = 0; j < serie[i].QuantidadeTemporadas; j++) {

            fscanf(arquivo, "%d,", &serie[i].QuantidadeEpisodiosPorTemporada[j]);
      
            serie[i].QuantidadeEpisodiosTotais=serie[i].QuantidadeEpisodiosTotais+serie[i].QuantidadeEpisodiosPorTemporada[j];
        }//for
    }//for
}//void lerseries

void imprimirSeries(Serie *serie, int QuantidadeSeries)
{
    printf("Aqui estao todas series cadastradas\n");
    for (int i = 0; i < QuantidadeSeries; i++) 
    {
        printf("%d-", serie[i].id);
        printf("%-40s " , serie[i].Nome);
        printf("Genero:%-20s ", serie[i].Genero);
        printf("Classificacao:%-5d ", serie[i].Classificacao);
        printf("Plataforma:%-15s ", serie[i].Plataforma);
        printf("Duracao media por ep:%-5d ", serie[i].DuracaoMediaEpisodios);
        printf("Quantidade de temporadas:%-5d ", serie[i].QuantidadeTemporadas);
       
        printf("episodios por temporada: ");
        for (int j = 0; j < serie[i].QuantidadeTemporadas; j++) 
        {
            printf("%d ", serie[i].QuantidadeEpisodiosPorTemporada[j]);
        }   

        printf("    Episodios totais: %-5d ",serie[i].QuantidadeEpisodiosTotais);
        printf("\n \n \n");
    }// for
}//void imprimir series

int cadastrar(int QuantidadeSeries , Serie *serie)
{
    QuantidadeSeries++;
  
    serie = (Serie*) realloc(serie, QuantidadeSeries * sizeof(Serie));
    serie[QuantidadeSeries - 1].id= QuantidadeSeries;
    setbuf(stdin,NULL);
 
    printf("Digite o nome da serie\n:");
    fgets(serie[QuantidadeSeries - 1].Nome, 101, stdin);
    serie[QuantidadeSeries - 1].Nome[strcspn(serie[QuantidadeSeries-1].Nome, "\n")] = '\0';
    setbuf(stdin, NULL);

    for (int i = 0; i < QuantidadeSeries - 1; i++)
    {
      
        if (strcasecmp(serie[i].Nome, serie[QuantidadeSeries - 1].Nome) == 0)
        {

            printf("Essa serie ja esta cadastrada. Por favor, insira outro nome.\n");
            QuantidadeSeries--;  // Diminuir o tamanho para cancelar o cadastro da série repetida
          
        }//if
    }//for
    
    
    
    serie[QuantidadeSeries - 1].QuantidadeEpisodiosTotais= 0;
    printf("Digite o genero:\n");
    fgets(serie[QuantidadeSeries - 1].Genero, 41, stdin);
    serie[QuantidadeSeries - 1].Genero[strcspn(serie[QuantidadeSeries-1].Genero, "\n")] = '\0';
    setbuf(stdin, NULL);

    printf("Digite a classificacao\n");
    scanf("%d", &serie[QuantidadeSeries - 1].Classificacao);
    
    setbuf(stdin, NULL);
    printf("Digite plataforma\n");
    fgets(serie[QuantidadeSeries-1].Plataforma, 41, stdin);
    serie[QuantidadeSeries-1].Plataforma[strcspn(serie[QuantidadeSeries-1].Plataforma, "\n")] = '\0';
    setbuf(stdin, NULL);

    printf("Digite a duracao media:\n");
    scanf("%d", &serie[QuantidadeSeries - 1].DuracaoMediaEpisodios);
    
    printf("Digite a quantia de temporadas\n:");
    scanf("%d", &serie[QuantidadeSeries - 1].QuantidadeTemporadas);

    int realoca = serie[QuantidadeSeries - 1].QuantidadeTemporadas;
    serie[QuantidadeSeries-1].QuantidadeEpisodiosPorTemporada = (int*) malloc(realoca * sizeof(int));
    
    for (int i = 0; i < serie[QuantidadeSeries-1].QuantidadeTemporadas; i++)
    { 

        printf("Digite a quantia de episodios da %d temporada:",i+1);
        scanf("%d", &serie[QuantidadeSeries - 1].QuantidadeEpisodiosPorTemporada[i]);
         serie[QuantidadeSeries - 1].QuantidadeEpisodiosTotais=serie[QuantidadeSeries - 1].QuantidadeEpisodiosTotais+serie[QuantidadeSeries-1].QuantidadeEpisodiosPorTemporada[i];

    }//for  

    return QuantidadeSeries;

}//int cadastrar series




void Alterar(int QuantidadeSeries, Serie *serie)
{

    char alterar[101];
    int encontrar = 0;
    int contador = -1;
    char placeHolder[45];
    int realoca = 0;
    
    setbuf(stdin, NULL);
    printf("Digite o nome da serie que deseja realizar modificacoes nos dados: ");
    fgets(alterar, sizeof(alterar), stdin);
    alterar[strcspn( alterar, "\n")] = '\0';
    setbuf(stdin, NULL);

    for (int i = 0; i < QuantidadeSeries ; i++)
    {
        contador++;
        if (strcasecmp( alterar, serie[i].Nome) != 0)
        { 
            encontrar =1;
        }else
        {
            encontrar =0;
            break;


        }//else

    }//for
        if(encontrar == 1)
        {
            printf("serie nao encontrada, tente outro nome\n");
            
            Alterar(QuantidadeSeries,serie);

        }else
        {
            int caso=0;

            printf("Digite 1 para mudar o nome da serie\n");
            printf("Digite 2 para mudar o genero da serie\n");
            printf("Digite 3 para mudar a clasificacao da serie\n");
            printf("Digite 4 para mudar plataforma da serie\n");
            printf("Digite 5 para mudar duracao media por episodio  da serie\n");
            printf("Digite 6 para mudar quantia de temporadas da serie\n");
            printf("Digite 7 para mudar a quantia de eps por temporada ");

            scanf("%d",&caso);

                switch (caso) {
                    
                    case 1:

                    printf("Voce escolheu mudar o nome da serie ");

                    setbuf(stdin, NULL);
                    printf("Digite o novo nome da serie que deseja realizar modificacoes nos dados: ");
                    fgets( placeHolder, sizeof(placeHolder), stdin);
                    placeHolder[strcspn( placeHolder, "\n")] = '\0';
                    setbuf(stdin, NULL);

                    strcpy(serie[contador].Nome,placeHolder);
                    
                    break;

            case 2:
                    
                    printf("Voce escolheu mudar o genero da serie \n");
                    setbuf(stdin, NULL);      
                    
                    printf("Digite os novos generos no modelo genero1/genero2: "); 
                    
                    fgets( placeHolder, sizeof(placeHolder), stdin);
                    placeHolder[strcspn( placeHolder, "\n")] = '\0';
                    setbuf(stdin, NULL);
                    
                    strcpy(serie[contador].Genero,placeHolder);
                      
                    
            break;

            case 3:
                    printf("Voce escolheu mudar a classificacao da serie.\n");                   
                    printf("Digite a nova classificacao da serie: ");
                    scanf("%d",&serie[contador].Classificacao);

            break;

            case 4:
                    
                    printf("Voce escolheu mudar a plataforma de streaming da serie.\n");
                    printf("Digite a nova plataforma de streaming: ");
                    strcpy(serie[contador].Plataforma,placeHolder);             
            break;  
            
            case 5:
                    printf("Voce escolheu mudar a duracao media dos episodios da serie.\n");
                
                    printf("Digite a nova duracao media: ");
                    scanf("%d",&serie[contador].DuracaoMediaEpisodios);

            break; 

            case 6:
                printf("Voce escolheu mudar a quantia de temporadas da serie.\n");                   
                printf("Digite a quantia de temporadas: ");
                scanf("%d",&serie[contador].QuantidadeTemporadas);

                printf("Digite a nova distribuicao de episodios por temporada: ");
                realoca = serie[contador].QuantidadeTemporadas;
                serie[contador].QuantidadeEpisodiosPorTemporada = (int*)realloc(serie[contador].QuantidadeEpisodiosPorTemporada, realoca * sizeof(int));
                serie[contador].QuantidadeEpisodiosTotais =  0;
                
                for (int i = 0; i < realoca; i++)
                { 

                    printf("Digite a quantia de episodios da %d temporada:",i+1);
                    scanf("%d", &serie[contador].QuantidadeEpisodiosPorTemporada[i]);
                    serie[contador].QuantidadeEpisodiosTotais=serie[contador].QuantidadeEpisodiosTotais+serie[contador].QuantidadeEpisodiosPorTemporada[i];                   
                } 
            break; 

            case 7:

                printf("Voce escolheu mudar a quantia de episodios das temporadas\n");                          
                printf("Digite a nova distribuicao de episodios por temporada\n");

                for (int i = 0; i < serie[contador].QuantidadeTemporadas; i++)
                { 
                    printf("Digite a quantia de episodios da %d temporada: ",i+1);
                    scanf("%d", &serie[contador].QuantidadeEpisodiosPorTemporada[i]);
                    serie[contador].QuantidadeEpisodiosTotais=serie[contador].QuantidadeEpisodiosTotais+serie[contador].QuantidadeEpisodiosPorTemporada[i];
                } 
                        
            break; 

                default:
                    printf("Numero invalido.\n");
                    
                Alterar(QuantidadeSeries, serie);
            }         
        }//else
}// void alterar



void apagar(int QuantidadeSeries, Serie *serie)
{

    char deletar[101];
    int encontrar=0;
    int contador=-1;
    
    setbuf(stdin, NULL);
    printf("Digite o nome da serie que deseja apagar: ");
    fgets(deletar, sizeof(deletar), stdin);
    deletar[strcspn(deletar, "\n")] = '\0';
    setbuf(stdin, NULL);

    for (int i = 0; i < QuantidadeSeries ; i++)
    {
        contador++;
        if (strcasecmp(deletar, serie[i].Nome) != 0)
        { 
            encontrar =1;
        }else
        {
            encontrar =0;
            break;


        }//else

    }//for
        if(encontrar == 1)
        {
            printf("serie n encontrada, tente outro nome\n");
            
            apagar(QuantidadeSeries,serie);
        }else
        {

            serie[contador].id=contador+1;
            strcpy(serie[contador].Nome,serie[QuantidadeSeries - 1].Nome);
            strcpy(serie[contador].Genero, serie[QuantidadeSeries - 1].Genero);
            serie[contador].Classificacao=serie[QuantidadeSeries-1].Classificacao;
            strcpy(serie[contador].Plataforma, serie[QuantidadeSeries - 1].Plataforma);
            serie[contador].DuracaoMediaEpisodios=serie[QuantidadeSeries -1].DuracaoMediaEpisodios;
            serie[contador].QuantidadeTemporadas=serie[QuantidadeSeries-1].QuantidadeTemporadas;
            serie[contador].QuantidadeEpisodiosTotais=serie[QuantidadeSeries-1].QuantidadeEpisodiosTotais;

            int realoca = serie[contador].QuantidadeTemporadas;
           serie[contador].QuantidadeEpisodiosPorTemporada = realloc(serie[contador].QuantidadeEpisodiosPorTemporada ,realoca * sizeof(int));
            
            for(int i = 0; i <realoca; i++)
            {
                serie[contador].QuantidadeEpisodiosPorTemporada[i]=serie[QuantidadeSeries-1].QuantidadeEpisodiosPorTemporada[i];
            }//for

            QuantidadeSeries--;
            
            serie = (Serie *)realloc(serie, QuantidadeSeries * sizeof(Serie));
            imprimirSeries(serie, QuantidadeSeries);

          
        }//else
}// void apagar 

void Pesquisa (Serie *serie, int QuantidadeSeries)
{ 
    int contadorSerie = 0;
    char serieBusca[41];


    printf("Digite o Nome da serie que deseja buscar:\n");

    setbuf(stdin, NULL);
    fgets(serieBusca, sizeof(serieBusca), stdin);
    serieBusca[strcspn(serieBusca, "\n")] = '\0';
    setbuf(stdin, NULL);

    for (int i = 0; i < QuantidadeSeries; i++)
    {   
       
            

            if (strcasecmp(serieBusca,serie[i].Nome) == 0)
            {
                contadorSerie++;
                printf("%d-", serie[i].id);
                printf("%-40s " , serie[i].Nome);
                printf("Genero:%-20s ", serie[i].Genero);
                printf("Classificacao:%-5d ", serie[i].Classificacao);
                printf("Plataforma:%-15s ", serie[i].Plataforma);
                printf("Duracao media por ep:%-5d ", serie[i].DuracaoMediaEpisodios);
                printf("Quantidade de temporadas:%-5d ", serie[i].QuantidadeTemporadas);
            
                printf("episodios por temporada: ");
                for (int j = 0; j < serie[i].QuantidadeTemporadas; j++) 
                {
                    printf("%d ", serie[i].QuantidadeEpisodiosPorTemporada[j]);
                }
                printf("\n \n \n");
                break;
                
            }//if
        
        
    }//for

    if (contadorSerie == 0)
    {
        printf("Nao ha series com esse nome!! Tente novamente.\n");
        Pesquisa(serie, QuantidadeSeries);
    }//if
}//void pesquisa 
            





void BuscaGenero(Serie *serie, int QuantidadeSeries)
{ 
    int ContadorGenero = 0;
    char GeneroBusca[41];
    char GeneroCopia[41];
    printf("Digite o Genero que deseja buscar:\n");

    setbuf(stdin, NULL);
    fgets(GeneroBusca, sizeof(GeneroBusca), stdin);
    GeneroBusca[strcspn(GeneroBusca, "\n")] = '\0';
    setbuf(stdin, NULL);

    for (int i = 0; i < QuantidadeSeries; i++)
    {   
        strcpy(GeneroCopia, serie[i].Genero);
        char *GeneroToken = strtok(GeneroCopia, "/");//esse comando divide a palavra em 2 usando o / como o centro da divisao
                                                    //dessa forma generos que foram cadastrados como "acao/drama" sao localizados pela funcao
        while (GeneroToken != NULL)
        {
            if (strcasecmp(GeneroBusca, GeneroToken) == 0)
            {
                ContadorGenero++;
                printf("%d-", serie[i].id);
                printf("%-40s " , serie[i].Nome);
                printf("Genero:%-20s ", serie[i].Genero);
                printf("Classificacao:%-5d ", serie[i].Classificacao);
                printf("Plataforma:%-15s ", serie[i].Plataforma);
                printf("Duracao media por ep:%-5d ", serie[i].DuracaoMediaEpisodios);
                printf("Quantidade de temporadas:%-5d ", serie[i].QuantidadeTemporadas);
            
                printf("episodios por temporada: ");
                for (int j = 0; j < serie[i].QuantidadeTemporadas; j++) 
                {
                    printf("%d ", serie[i].QuantidadeEpisodiosPorTemporada[j]);
                }//for

                printf("\n");
                printf("\n");
                printf("\n");
            }//if
            GeneroToken = strtok(NULL, "/");
        }//while
    }//for

    if (ContadorGenero == 0)
    {
        printf("Não há séries desse gênero, tente novamente.\n");
        BuscaGenero(serie, QuantidadeSeries);
    }//if
}//void buscaGeneros
            


void salvaDados(Serie *serie, int QuantidadeSeries)
{
   
    FILE *arquivobin = fopen("streaming_db.dat", "wb");

    if (arquivobin == NULL) {

        perror("Erro ao abrir o arquivo.\n");
        
    }else{


    for (int i = 0; i < QuantidadeSeries; i++)
    {
        fwrite(&serie[i].id,sizeof(int),1,arquivobin);
           
      
        fwrite(serie[i].Nome,sizeof(char),101,arquivobin);
              
        fwrite(serie[i].Genero,sizeof(char),41,arquivobin);
               
        fwrite(&serie[i].Classificacao,sizeof(int),1,arquivobin);
           
        fwrite(serie[i].Plataforma,sizeof(char),41,arquivobin);
               
       
        fwrite(&serie[i].DuracaoMediaEpisodios,sizeof(int),1,arquivobin);
             
       
        fwrite(&serie[i].QuantidadeTemporadas,sizeof(int),1,arquivobin);
               

        for (int j = 0; j < serie[i].QuantidadeTemporadas; j++) {

            fwrite(&serie[i].QuantidadeEpisodiosPorTemporada[j],sizeof(int),1,arquivobin);
                
        }//for

    }//else
    printf("\n");
    }//for
    
    fclose(arquivobin);
    
}//void salva dados

        
        
void ArquivoHistorico( Historico *historico, int indiceHistorico)
{

    char pulaLinha= '\n';

    FILE *arquivohistorico = fopen("arquivobinHistorico.dat", "wb");

    if (arquivohistorico == NULL) {
        perror("Erro ao abrir o arquivo.\n");
        
    }else{

    fwrite(&indiceHistorico,sizeof(int),1,arquivohistorico);
    fwrite(&pulaLinha, sizeof(char), 1, arquivohistorico);
    for (int i = 0; i < indiceHistorico; i++)
    {
        fwrite(historico[i].Nome,sizeof(char),101,arquivohistorico);
        fwrite(&historico[i].UltimaTemporadaAssistida,sizeof(int),1,arquivohistorico);
        fwrite(&historico[i].UltimoEpisodio,sizeof(int),1,arquivohistorico);
           
    
           
  
       
        }//for

    }//else
    printf("\n");
    
    fclose(arquivohistorico);

}//void arquivo historico



int lerHistoricoBinario(Historico* historico ,int indiceHistorico)
{

char pulaLinha= '\n';//ta aqui na leitura pra ler o \n na primeira linha feito na escrita



     FILE *arquivohistorico = fopen("Histirico.dat", "wb");

    if (arquivohistorico == NULL) {
        perror("Erro ao abrir o arquivo.\n");
        
    }else{

    fread(&indiceHistorico,sizeof(int),1,arquivohistorico);
    fread(&pulaLinha, sizeof(char), 1, arquivohistorico);
    for (int i = 0; i < indiceHistorico; i++)
    {
        fread(historico[i].Nome,sizeof(char),101,arquivohistorico);
        fread(&historico[i].UltimaTemporadaAssistida,sizeof(int),1,arquivohistorico);
        fread(&historico[i].UltimoEpisodio,sizeof(int),1,arquivohistorico);
           
    
           
  
       
        }//for

    }//else
    printf("\n");
    
    
    fclose(arquivohistorico);

    return indiceHistorico;



}//int lerHistoricoBinario



int main() {
    int indiceHistorico = 0;
    int QuantidadeSeries = 258;
    int menu;

    Serie *serie = (Serie*) malloc(QuantidadeSeries * sizeof(Serie));
    Historico *historico =(Historico*)malloc(indiceHistorico * sizeof(Historico)); 

    FILE *arquivo = fopen("streaming_db.dat", "rb");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo Binario, tentaremos excutar o arquivo csv.\n");

        FILE *arquivo = fopen("streaming_db.csv", "r");

         if (arquivo == NULL) {
             perror("Erro ao abrir o arquivo CSV.\n");
              return 1;
        }
        lerSeries(serie, QuantidadeSeries, arquivo);
        salvaDados(serie,QuantidadeSeries);

    }else{

        lerSeriesBinario(serie, QuantidadeSeries, arquivo);

    }//else
    //esse if acima serve para conferir se tem o arquivo binario.




    FILE *arquivoCarregaHistorico = fopen("Histirico.dat", "rb");

    if (arquivoCarregaHistorico== NULL) {
        perror("Erro ao Abrir historico, por favor assim que possivel adicione seus dados!!!  \n");

   

    }else{
    indiceHistorico = lerHistoricoBinario(historico,indiceHistorico);
    
    fclose(arquivoCarregaHistorico);

    }//else
    //esse if acima serve para conferir se tem o arquivo binario.

    while (menu !=9)
    {
         
        printf("\n\nBusca Streaming\n\n");
        printf("Digite 1 para mostrar todas as series\n");
        printf("Digite 2 para buscar uma serie\n");
        printf("Digite 3 para buscar um genero\n");
        printf("Digite 4 para adicionar uma serie ao historico\n");
        printf("Digite 5 para cadastrar uma serie nova\n");
        printf("Digite 6 para alterar uma serie\n");
        printf("Digite 7 para apagar uma serie\n");
        printf("Digite 8 para salvar os seus dados\n");
        printf("Digite 9 para sair\n");

      scanf("%d",&menu);

       switch (menu){

        case 1:
            imprimirSeries(serie, QuantidadeSeries);
        break;

        case 2: 
            Pesquisa(serie,QuantidadeSeries);
        break;

        case 3:
            BuscaGenero(serie,QuantidadeSeries);
        break;

        case 4:
            indiceHistorico=salvaHistorico(serie,QuantidadeSeries,historico,indiceHistorico);
        break;

        case 5:
             QuantidadeSeries = cadastrar(QuantidadeSeries, serie);
        break;
        
        case 6:
            Alterar(QuantidadeSeries, serie);
        break;

        case 7: 
            apagar(QuantidadeSeries, serie);
        break;

        
        case 8:
            salvaDados(serie,QuantidadeSeries);
            ArquivoHistorico(historico,indiceHistorico);
        break;

        case 9:
        break;

        default:
        printf("Opcao invalida\n");
        break;

       }

     }

    free(serie);
    free(historico);
    fclose(arquivo);

    return 0;
}
