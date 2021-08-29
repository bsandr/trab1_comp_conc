//Trabalho de Implementação - Módulo 1
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<pthread.h>

#define FILE_SIZE 1024
#define SIZE 1000000

//var globais 
char *nome_inst[SIZE]; //vetor de nome da Instituição
char *nome_curso[SIZE]; //vetor de nome do curso de graduação
char *taxa[SIZE]; //vetor de taxa de desistência
int NTHREADS; //número de threads

//struct 
typedef struct {
    float menor_taxa, maior_taxa;
} taxas;

//função executada pelas threads

//programa principal
int main(int argc, char *argv[]){
    //declarações variaveis

    //recebe os parametros de entrada e os trata
    if(argc<2){
        fprintf(stderr,"Digite %s <numero de threads>\n",argv[0]);
        return 1;
    }
    NTHREADS = atoi(argv[1]);

    //aloca memoria 

    //leitura de arquivos e preenchimento dos vetores
    FILE *file;
    char path[] = "./indicadores.CSV";

    file = fopen(path, "r");
    if (!file) {
        printf("Failed to open file\n");
        return 1;
    }

    char content[FILE_SIZE];
    int i = 0;
    while(fgets(content, FILE_SIZE-1, file)) {

        char* temp = strdup(content);

        if((nome_inst[i] = strtok(temp, ";")) != NULL) {
            nome_inst[i] = strdup(nome_inst[i]);
        }

        if((nome_curso[i] = strtok(NULL, ";")) != NULL) {
            nome_curso[i] = strdup(nome_curso[i]);
        }

        if((taxa[i] = strtok(NULL, ";")) != NULL) {
            taxa[i] = strdup(taxa[i]);
        }
        
        i++;
    }   

    //cria as threads

    //espera as threads acabarem

    //exibe resultados 

    //corretude

    //libera memoria

    return 0;
}




    