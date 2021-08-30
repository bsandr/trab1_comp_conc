//Trabalho de Implementação - Módulo 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include "timer.h"

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
    int indice_menor, indice_maior;
} taxas;

//função executada pelas threads
void * tarefa(void *arg) {
  long int id = (long int) arg;
  taxas *thread_valores; //guarda info da taxa min e max encontradas
  thread_valores = (taxas *) malloc(sizeof(taxas));
  if(thread_valores == NULL){
        fprintf(stderr, "Erro -- malloc\n"); 
        exit(1);
    }

  thread_valores->menor_taxa = taxa[0];
  thread_valores->maior_taxa = taxa[0];

  for(int i = id; i < SIZE; i+=NTHREADS){
    if(taxa[i] > thread_valores->maior_taxa) {
            thread_valores->maior_taxa = taxa[i];
            thread_valores->indice_maior = i;
        }
        if(taxa[i] < thread_valores->menor_taxa) {
            thread_valores->menor_taxa = taxa[i];
            thread_valores->indice_menor = i;
        }
  }

  pthread_exit((void*) thread_valores);
    
}

//programa principal
int main(int argc, char *argv[]){
    //declarações variaveis
    int i_menor_seq, i_maior_seq;
    int i_menor_conc, i_maior_conc;
    float menor_seq, maior_seq;
    float menor_conc, maior_conc;
    pthread_t *tid; //identificadores das threads no sistema
    double inicio, fim;
    taxas *retorno;

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
        char *taxa_temp;

        if((nome_inst[i] = strtok(temp, ";")) != NULL) {
            nome_inst[i] = strdup(nome_inst[i]);
        }

        if((nome_curso[i] = strtok(NULL, ";")) != NULL) {
            nome_curso[i] = strdup(nome_curso[i]);
        }
        
        if((taxa_temp = strtok(NULL, ";")) != NULL) {
            taxa_temp = strdup(taxa_temp);
            taxa[i] = atof(taxa_temp);
        }
        
        i++;
    }   

    GET_TIME(inicio);
    maior_seq = taxa[0];
    menor_seq = taxa[0];
    //sequencial 
    for(int i = 0; i < SIZE; i++){
        if(taxa[i]>maior_seq) {
            maior_seq = taxa[i];
            i_maior_seq = i;
        }
        if(taxa[i]<menor_seq) {
            menor_seq = taxa[i];
            i_menor_seq = i;
        }
    }
    
    printf("-------------- Saída Sequencial ------------------\n");
    printf("Instituição: %s Curso: %s tem a menor taxa de evasao: %f\n",nome_inst[i_menor_seq], nome_curso[i_menor_seq], menor_seq);
    printf("Instituição: %s Curso: %s tem a maior taxa de evasao: %f\n",nome_inst[i_maior_seq], nome_curso[i_maior_seq], maior_seq);
  
    GET_TIME(fim); 
    
    printf("Tempo sequencial: %lf ms\n",fim-inicio);
    
    //funcao concorrente
    GET_TIME(inicio)
    tid = (pthread_t *) malloc(sizeof(pthread_t) * NTHREADS);
    if(tid==NULL){
        fprintf(stderr, "Erro -- malloc\n"); 
        return 2;
    }
    //cria as threads
    for(long int i = 0; i < NTHREADS;i++){
        if(pthread_create(tid+i, NULL, tarefa, (void*) i)){
            fprintf(stderr, "Erro -- pthread_create\n"); 
            return 3;
        }
    }
    //espera as threads acabarem
    menor_conc = taxa[0];
    maior_conc = taxa[0];
    for(int i = 0; i < NTHREADS;i++){
        if(pthread_join(*(tid+i), (void**) &retorno)){
            fprintf(stderr, "Erro -- pthread_join\n"); 
            return 3;
        }
        if((retorno->menor_taxa) < menor_conc){
          menor_conc = retorno->menor_taxa;
          i_menor_conc = retorno->indice_menor;
        } 
        if((retorno->maior_taxa) > maior_conc){
          maior_conc = retorno->maior_taxa;
          i_maior_conc = retorno->indice_maior; 
        }
        free(retorno); 
    }

    //exibe resultados 
    printf("-------------- Saída Concorrente ------------------\n");
    printf("Instituição: %s Curso: %s tem a menor taxa de evasao: %f\n",nome_inst[i_menor_conc], nome_curso[i_menor_conc],menor_conc);
    printf("Instituição: %s Curso: %s tem a maior taxa de evasao: %f\n",nome_inst[i_maior_conc], nome_curso[i_maior_conc], maior_conc);
    
    GET_TIME(fim); 
    printf("Tempo concorrente: %lf ms\n",fim-inicio);
    //corretude
    printf("-------------- Verificação de Corretude ------------------\n");
    if((menor_seq==menor_conc)&&(maior_seq==maior_conc)) printf("Saida correta\n");
    else printf("Saida incorreta\n");

    //libera memoria
    free(nome_inst);
    free(nome_curso);
    free(taxa);
    free(tid);

    return 0;
}