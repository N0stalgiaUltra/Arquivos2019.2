#include <stdio.h>
#include <string.h>
 
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
 
int main(int argc, char**argv)
{
    FILE *f;
    Endereco e;
    int qt;
    int i =0;
    long posicao, primeiro, ultimo, meio;
 
    if(argc != 2)
    {
        fprintf(stderr, "USO: %s [CEP]", argv[0]);
        return 1;
    }
    
    f = fopen("cep.dat","r");
    fseek(f,0,SEEK_END);    //vai até o final do arquivo
    posicao = ftell(f);     //retorna a posicao e coloca na variavel
    rewind(f);              //volta para a posicao inicial
    
    primeiro = 0;
    ultimo = (posicao/sizeof(Endereco))-1;
    
    
    while (primeiro <= ultimo)
    {
        i++;                                       //incrementa
        meio = (primeiro+ultimo)/2;                 // define meio
        fseek(f,meio*sizeof(Endereco),SEEK_SET); //ponteiro no meio
        fread(&e, sizeof(Endereco), 1,f);       
        
        //caso 1: achou
        if(strncmp(argv[1], e.cep,8) == 0) //compara, caso os argumentos sejam iguais
        {
            //printf("Endereco encontrado!");
            printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
            
            break;
        }

        else
            if(strncmp(argv[1], e.cep,8) > 0)   //caso 2: argv > e.cep; inicio = meio+1
            {
                primeiro = meio+1;
            }
            else//caso 3: argv<e.cep; ultimo = meio-1
            {
                ultimo = meio-1;
            }     
    }
   //printf(i);

    fclose(f);
    return 0;
}