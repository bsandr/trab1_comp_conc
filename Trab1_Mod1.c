//Trabalho de Implementação - Módulo 1
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

//var globais 
float *nome_inst; //vetor de nome da Instituição
float *nome_curso; //vetor de nome do curso de graduação
float *taxa; //vetor de taxa de desistência
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

    //cria as threads

    //espera as threads acabarem

    //exibe resultados 

    //corretude

    //libera memoria

    return 0;
}




    