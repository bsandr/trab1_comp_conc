//Trabalho de Implementação - Módulo 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

#define FILE_SIZE 1024
#define SIZE 1000000

//var globais 
char **nome_inst; //vetor de nome da Instituição
char **nome_curso; //vetor de nome do curso de graduação
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
    int indice_menor, indice_maior;
    float menor_seq = 10000;
    float maior_seq = 0;
    //pthread_t *tid; //identificadores das threads no sistema

    //recebe os parametros de entrada e os trata
    if(argc<2){
        fprintf(stderr,"Digite %s <numero de threads>\n",argv[0]);
        return 1;
    }

    NTHREADS = atoi(argv[1]);


    //aloca memoria 
    nome_inst = (char **) malloc(sizeof(char*)*SIZE);
    if(nome_inst == NULL){
        fprintf(stderr, "Erro -- malloc\n"); 
        return 2;
    }
    nome_curso = (char **) malloc(sizeof(char*)*SIZE);
    if(nome_curso == NULL){
        fprintf(stderr, "Erro -- malloc\n"); 
        return 2;
    }
    taxa = (float *) malloc(sizeof(float)*SIZE);
    if(taxa == NULL){
        fprintf(stderr, "Erro -- malloc\n"); 
        return 2;
    }

    
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
        /**
        if((taxa[i] = strtok(NULL, ";")) != NULL) {
            taxa[i] = strdup(taxa[i]);
        }*/
        
        i++;
    }   

    //sequencial 
    for(int i = 0; i < SIZE; i++){
        if(taxa[i]>maior_seq) {
            maior_seq = taxa[i];
            indice_maior = i;
        }
        if(taxa[i]<menor_seq) {
            menor_seq = taxa[i];
            indice_menor = i;
        }
    }
    printf("Instituição: %s Curso: %s tem a menor taxa de evasao: %f\n",nome_inst[indice_menor], nome_curso[indice_menor], menor_seq);
    printf("Instituição: %s Curso: %s tem a maior taxa de evasao: %f\n",nome_inst[indice_maior], nome_curso[indice_maior], maior_seq); 

    //funcao concorrente
    /**
    tid = (pthread_t *) malloc(sizeof(pthread_t) * NTHREADS);
    if(tid==NULL){
        fprintf(stderr, "Erro -- malloc\n"); 
        return 2;
    }

    //cria as threads
    for(int i = 0; i < NTHREADS;i++){
        if(pthread_create(tid+i, NULL, nome_funcao, (void*) i)){
            fprintf(stderr, "Erro -- pthread_create\n"); 
            return 3;
        }
    }

    //espera as threads acabarem

    //exibe resultados 

    //corretude
    
    if((menor_seq==menor_conc)&&(maior_seq==maior_conc)) printf("Saida correta");
    else printf("Saida incorreta");*/

    //libera memoria
    free(nome_inst);
    free(nome_curso);
    free(taxa);
    //free(tid);

    return 0;
}
    
