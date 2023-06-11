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

void lerSeries(Serie *serie, int QuantidadeSeries, FILE *arquivo) {

    for (int i = 0; i < QuantidadeSeries; i++) 
    {
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
        }
    }
}

void imprimirSeries(Serie *serie, int QuantidadeSeries)
{
    printf("Aqui estao todas series cadastradas\n");
    for (int i = 0; i < QuantidadeSeries; i++) 
    {
        printf("%d-", serie[i].id);
        printf("%-40s " , serie[i].Nome);
        printf("Genero:%-20s ", serie[i].Genero);
        printf("Clasificacao:%-5d ", serie[i].Classificacao);
        printf("Plataforma:%-15s ", serie[i].Plataforma);
        printf("Duracao media por ep:%-5d ", serie[i].DuracaoMediaEpisodios);
        printf("Quatidade de temporadas:%-5d ", serie[i].QuantidadeTemporadas);
       
        printf("episodios por temporada: ");
        for (int j = 0; j < serie[i].QuantidadeTemporadas; j++) 
        {
            printf("%d ", serie[i].QuantidadeEpisodiosPorTemporada[j]);
        }   
        printf("\n");
       // printf");
        printf("\n");
       
        printf("\n");
    }
}


int cadastrar(int QuantidadeSeries , Serie *serie)
{
    QuantidadeSeries++;
  
    serie = (Serie*) realloc(serie, QuantidadeSeries * sizeof(Serie));
    serie[QuantidadeSeries - 1].id= QuantidadeSeries;
    setbuf(stdin,NULL);
 
    printf("digite o nome da serie\n:");
    fgets(serie[QuantidadeSeries - 1].Nome, 30, stdin);
    serie[QuantidadeSeries - 1].Nome[strcspn(serie[QuantidadeSeries-1].Nome, "\n")] = '\0';
    setbuf(stdin, NULL);

    for (int i = 0; i < QuantidadeSeries - 1; i++)
    {
        if (strcasecmp(serie[i].Nome, serie[QuantidadeSeries - 1].Nome) == 0)
        {

            printf("Essa série já está cadastrada. Por favor, insira outro nome.\n");
            QuantidadeSeries--;  // Diminuir o tamanho para cancelar o cadastro da série repetida
            return QuantidadeSeries;  

        }
    }

    printf("digite o genero\n:");
    fgets(serie[QuantidadeSeries - 1].Genero, 12, stdin);
    serie[QuantidadeSeries - 1].Genero[strcspn(serie[QuantidadeSeries-1].Genero, "\n")] = '\0';
    setbuf(stdin, NULL);

    printf("digite a classificacao\n");
    scanf("%d", &serie[QuantidadeSeries - 1].Classificacao);
    
    setbuf(stdin, NULL);
    printf("digite plataforma\n");
    fgets(serie[QuantidadeSeries-1].Plataforma, 12, stdin);
    serie[QuantidadeSeries-1].Plataforma[strcspn(serie[QuantidadeSeries-1].Plataforma, "\n")] = '\0';
    setbuf(stdin, NULL);

    printf("diga a dura;'ao media\n:");
    scanf("%d", &serie[QuantidadeSeries - 1].DuracaoMediaEpisodios);
    
    printf("digite a quantia de temporadas\n:");
    scanf("%d", &serie[QuantidadeSeries - 1].QuantidadeTemporadas);


    int realoca = serie[QuantidadeSeries - 1].QuantidadeTemporadas;
    serie[QuantidadeSeries-1].QuantidadeEpisodiosPorTemporada = malloc(realoca * sizeof(int));
    
    for (int i = 0; i < serie[QuantidadeSeries-1].QuantidadeTemporadas; i++)
    { 

        printf("digite a quantia de episodios da %d temporada:",i+1);
        scanf("%d", &serie[QuantidadeSeries-1].QuantidadeEpisodiosPorTemporada[i]);

    }  

    return QuantidadeSeries;

}



void apagar(int QuantidadeSeries, Serie *serie)
{
    char deletar[101];
    int encontrar=0;
    int contador=-1;
    
    setbuf(stdin, NULL);
    printf("Digite o nome da série que deseja apagar: ");
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


            int realoca = serie[contador].QuantidadeTemporadas;
           serie[contador].QuantidadeEpisodiosPorTemporada = realloc(serie[contador].QuantidadeEpisodiosPorTemporada ,realoca * sizeof(int));
            
            for(int i = 0; i <realoca; i++)
            {
                serie[contador].QuantidadeEpisodiosPorTemporada[i]=serie[QuantidadeSeries-1].QuantidadeEpisodiosPorTemporada[i];
            }
            
            

            QuantidadeSeries--;
            
            serie = (Serie *)realloc(serie, QuantidadeSeries * sizeof(Serie));
            imprimirSeries(serie, QuantidadeSeries);

          
        }

   


}// void apagar 

int main() {
    
    int QuantidadeSeries = 258;
    Serie *serie = (Serie*) malloc(QuantidadeSeries * sizeof(Serie));

    FILE *arquivo = fopen("streaming_db.txt", "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo.\n");
        return 1;
    }

    lerSeries(serie, QuantidadeSeries, arquivo);
    imprimirSeries(serie, QuantidadeSeries);
    QuantidadeSeries = cadastrar(QuantidadeSeries, serie);
    apagar(QuantidadeSeries, serie);

    fclose(arquivo);

    return 0;
}
