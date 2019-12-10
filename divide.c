#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma pack(1)

typedef struct _Endereco Endereco;
 
struct _Endereco
{
    char logradouro[72];
    char bairro[72];
    char cidade[72];
    char uf[72];
    char sigla[2];
    char cep[8];
    char lixo[2];
};
 
int compara(const void *e1, const void *e2)
{
    return strncmp(((Endereco*)e1)->cep,((Endereco*)e2)->cep,8);
}
 
int main(int argc, char**argv)
{
    //dividir em 8 partes
    //unir as partes
    //ordenadas


    
    //Definir a divisão do arquivo em 8 partes
    FILE *f, *saida;
    Endereco *e;
    long posicao, qtd, oitavo, resto, n_linhas;
    //qtd = 8;


    f = fopen("cep.dat","r");    //abre o arquivo
    fseek(f,0,SEEK_END);         //ponteiro apontando para o final do arq
    posicao = ftell(f);          //pega a posicao do ponteiro
    rewind(f);                   //volta f para o inicio

    qtd = posicao/sizeof(Endereco); //define quantidade TOTAL de linhas
    
    char linhas [300];
    oitavo = 8;                  // define por qt sera dividido 

    n_linhas = qtd/oitavo;      //numero de linhas de um arquivo
    resto = qtd % oitavo;       //define o resto de linhas, ou seja, as linhas que sobrarem da divisao
    e = (Endereco*) malloc(n_linhas*sizeof(Endereco));    //separa um oitavo das linhas do arq
    
    printf("\nO arquivo sera separado...\n");
    
    for(int i = 1; i<= oitavo; i++)
    {
        char nome[20];
        sprintf(nome, "teste/cep%d.dat", i);
        FILE *saida = fopen(nome, "w");

        fread(e,sizeof(Endereco),n_linhas,f);
        fwrite(e,sizeof(Endereco),n_linhas,saida);
        fclose(saida);

        printf("\n%d - %s\n", i, nome);
        
        if((i + 1) > oitavo)    //
            {
                printf("\nA partir daqui, serao criados os arquivos de resto\n");
                while(resto > 0)
                {                
                    sprintf(nome, "teste/cep%d.dat", ++i);
                    FILE *limpa = fopen(nome, "w");
                    fclose(limpa);

                    
                    for(int x = 0; x < n_linhas; x++)
                    {
                        if(resto <= 0)
                        {
                            break;
                        }
                        FILE *saida = fopen(nome, "a");
                        fread(linhas,300,1,f);
                        fprintf(saida,"%.300s",linhas);
                        fclose(saida);
                        resto--;
                    }
                    printf("\n%d - %s\n", i, nome);
                }
                printf("\n%d arquivos foram criados\n", i);
                break;
            }
    }
    free(e);
    fclose(f);
    return 0;
    //finalizado
}