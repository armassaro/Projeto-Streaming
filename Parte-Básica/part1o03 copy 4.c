
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

void lerSeries(Serie *serie, int capacidade, FILE *arquivo) {
  

    for (int i = 0; i < capacidade; i++) 
    {
        fscanf(arquivo, "%d,", &serie[i].id);
        fscanf(arquivo, "%[^,\n],", serie[i].Nome);
        fscanf(arquivo, "%[^,\n],", serie[i].Genero);
        fscanf(arquivo, "%d,", &serie[i].Classificacao);
        fscanf(arquivo, "%[^,\n],", serie[i].Plataforma);
        fscanf(arquivo, "%d,", &serie[i].DuracaoMediaEpisodios);
        fscanf(arquivo, "%d,", &serie[i].QuantidadeTemporadas);

        int realoca = serie[i].QuantidadeTemporadas;
        serie[i].QuantidadeEpisodiosPorTemporada = malloc(realoca * sizeof(int));

        for (int j = 0; j < serie[i].QuantidadeTemporadas; j++) {
            fscanf(arquivo, "%d,", &serie[i].QuantidadeEpisodiosPorTemporada[j]);
        }
    }
}

void imprimirSeries(Serie *serie, int capacidade)
{
    printf("Aqui estao todas series cadastradas\n");
    for (int i = 0; i < capacidade; i++) 
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


void cadastrar(int* capacidade , Serie** serie)
{
    (*capacidade)++;
  
    *serie = (Serie*)realloc(*serie, (*capacidade) * sizeof(Serie));
    (*serie)[*capacidade-1].id= *capacidade;
    setbuf(stdin,NULL);
 
    printf("digite o nome da serie\n:");
    fgets((*serie)[*capacidade-1].Nome, sizeof((*serie)[*capacidade-1].Nome), stdin);
    (*serie)[*capacidade-1].Nome[strcspn((*serie)[*capacidade-1].Nome, "\n")] = '\0';
    setbuf(stdin, NULL);

    for (int i = 0; i < *capacidade - 1; i++)
    {
        if (strcasecmp((*serie)[i].Nome, (*serie)[*capacidade-1].Nome) == 0)
        {
            printf("Essa série já está cadastrada. Por favor, insira outro nome.\n");
            (*capacidade)--;  // Diminuir o tamanho para cancelar o cadastro da série repetida
            return cadastrar(capacidade,serie );  
        }
    }

    printf("digite o genero\n:");
    fgets((*serie)[*capacidade - 1].Genero, sizeof((*serie)[*capacidade-1].Genero), stdin);
    (*serie)[*capacidade - 1].Genero[strcspn((*serie)[*capacidade-1].Genero, "\n")] = '\0';
    setbuf(stdin, NULL);

    printf("digite a classificacao\n");
    scanf("%d", &(*serie)[*capacidade - 1].Classificacao);
    
    setbuf(stdin, NULL);
    printf("digite plataforma\n");
    fgets((*serie)[*capacidade-1].Plataforma, sizeof((*serie)[*capacidade-1].Plataforma), stdin);
    (*serie)[*capacidade-1].Plataforma[strcspn((*serie)[*capacidade-1].Plataforma, "\n")] = '\0';
    setbuf(stdin, NULL);

    printf("diga a dura;'ao media\n:");
    scanf("%d", &(*serie)[*capacidade - 1].DuracaoMediaEpisodios);
    
    printf("digite a quantia de temporadas\n:");
    scanf("%d", &(*serie)[*capacidade - 1].QuantidadeTemporadas);


        int realoca = (*serie)[*capacidade - 1].QuantidadeTemporadas;
       (*serie)[*capacidade-1].QuantidadeEpisodiosPorTemporada = malloc(realoca * sizeof(int));
     for (int i = 0; i < (*serie)[*capacidade-1].QuantidadeTemporadas; i++)
    {   
        printf("digite a quantia de episodios da %d temporada:",i+1);
        scanf("%d",&(*serie)[*capacidade-1].QuantidadeEpisodiosPorTemporada[i]);
    }  
   



}



void apagaSeries(int* capacidade , Serie** serie)
{
    char deletar[101];
    int encontrar=0;
    int contador=-1;
    
    setbuf(stdin, NULL);
    printf("Digite o nome da série que deseja apagar: ");
    fgets(deletar, sizeof(deletar), stdin);
    deletar[strcspn(deletar, "\n")] = '\0';
    setbuf(stdin, NULL);

    for (int i = 0; i < *capacidade ; i++)
    {
        contador++;
        if (strcasecmp(deletar, (*serie)[i].Nome) != 0)
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
            
            apagaSeries(capacidade,serie);
        }else
        {

             free((*serie)[contador].QuantidadeEpisodiosPorTemporada);

            

            (*serie)[contador].id=contador+1;
            strcpy((*serie)[contador].Nome,(*serie)[*capacidade - 1].Nome);
            strcpy((*serie)[contador].Genero, (*serie)[*capacidade - 1].Genero);
            (*serie)[contador].Classificacao=(*serie)[*capacidade-1].Classificacao;
            strcpy((*serie)[contador].Plataforma, (*serie)[*capacidade - 1].Plataforma);
            (*serie)[contador].DuracaoMediaEpisodios=(*serie)[*capacidade -1].DuracaoMediaEpisodios;
            (*serie)[contador].QuantidadeTemporadas=(*serie)[*capacidade-1].QuantidadeTemporadas;


            int realoca = (*serie)[contador].QuantidadeTemporadas;
           (*serie)[contador].QuantidadeEpisodiosPorTemporada = realloc((*serie)[contador].QuantidadeEpisodiosPorTemporada ,realoca * sizeof(int));
            
            for(int i = 0; i <realoca; i++)
            {
                (*serie)[contador].QuantidadeEpisodiosPorTemporada[i]=(*serie)[*capacidade-1].QuantidadeEpisodiosPorTemporada[i];
            }
            
            

            (*capacidade)--;
            
            *serie = (Serie *)realloc(*serie, (*capacidade) * sizeof(Serie));
            imprimirSeries(*serie,* capacidade);

          
        }

   


}// void apagar 

void liberarMemoria(Serie *serie, int capacidade) 
{
    for (int i = 0; i < capacidade; i++) {
        free(serie[i].QuantidadeEpisodiosPorTemporada);
    }
    free(serie);
}

int main() {
    int capacidade = 258;
    Serie *serie = (Serie *)malloc(capacidade * sizeof(Serie));

    FILE *arquivo = fopen("streaming_db.txt", "r");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo.\n");
        return 1;
    }

    lerSeries(serie, capacidade, arquivo);
    //imprimirSeries(serie, capacidade);
    //cadastrar(&capacidade,&serie );
    apagaSeries(&capacidade,&serie);

    liberarMemoria(serie, capacidade);

    fclose(arquivo);

    return 0;
}