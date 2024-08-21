#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "EstruturaVetores.h"

typedef struct vetorPrincipal{
    int * aux;
    int tamanho;
    int cont;
}vetorPrincipal;

vetorPrincipal vp[TAM];
// vetorPrincipal vp[TAM] = {{.aux = NULL}, {.aux = NULL}, {.aux = NULL}, {.aux = NULL}, {.aux = NULL}, 
// {.aux = NULL}, {.aux = NULL}, {.aux = NULL}, {.aux = NULL}, {.aux = NULL}};
// int * vetorPrincipal[TAM+1] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

void imprimir_est(int posicao){
    int i;
    for(i = 0; i < vp[posicao].cont; i++)
        printf("%dº Valor: %d\n",i+1, *(vp[posicao].aux + i));
}

int validacao_estrutura(int posicao){
    int retorno = 0;
    if (posicao < 0 || posicao > TAM-1){
        retorno = POSICAO_INVALIDA;
    } else{
        if (vp[posicao].aux == NULL){
            retorno = SEM_ESTRUTURA_AUXILIAR;
        }
    } 
    return retorno;
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    int i;
    int retorno = 0;

    // if(vetorPrincipal[10] == NULL){
    //     vetorPrincipal[posicao] = malloc(10*sizeof(int));
    // }
    posicao = posicao-1;
    
    if(vp[posicao].aux != NULL)
        retorno = JA_TEM_ESTRUTURA_AUXILIAR; // a posicao pode já existir estrutura auxiliar
    else if(posicao < 0 || posicao > TAM-1)
        retorno = POSICAO_INVALIDA; // se posição é um valor válido {entre 1 e 10}
    else if(tamanho < 1){
        retorno = TAMANHO_INVALIDO; // o tamanho nao pode ser menor que 1
    } else{
        vp[posicao].aux = malloc(tamanho * sizeof(int));
        if(vp[posicao].aux != NULL){
            vp[posicao].tamanho = tamanho;
            vp[posicao].cont = 0;
            retorno = SUCESSO; // deu tudo certo, crie
        } else{
            retorno = SEM_ESPACO_DE_MEMORIA; // o tamanho ser muito grande
        }
    }

    return retorno;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    /*int existeEstruturaAuxiliar = 0;
    int temEspaco = 0;
    int posicao_invalida = 0;*/
    int retorno = 0;

    posicao--;
    retorno = validacao_estrutura(posicao);
    if((retorno != POSICAO_INVALIDA) && (retorno != SEM_ESTRUTURA_AUXILIAR)){
        if (vp[posicao].cont < vp[posicao].tamanho){
            //insere
            *(vp[posicao].aux + vp[posicao].cont) = valor;
            vp[posicao].cont++;
            retorno = SUCESSO;
        } else{
            retorno = SEM_ESPACO;
        }
    }

    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    int retorno = 0;
    
    posicao--;
    retorno = validacao_estrutura(posicao);
    if((retorno != POSICAO_INVALIDA) && (retorno != SEM_ESTRUTURA_AUXILIAR)){
        if(vp[posicao].cont > 0){
            vp[posicao].cont--;
            retorno = SUCESSO;
        } else{
            retorno = ESTRUTURA_AUXILIAR_VAZIA;
        }
    }  
    
    return retorno;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    int retorno = 0;
    int i;
    
    posicao--;
    retorno = validacao_estrutura(posicao);
    if((retorno != POSICAO_INVALIDA) && (retorno != SEM_ESTRUTURA_AUXILIAR)){
        if(vp[posicao].cont > 0){
            for(i = 0; i < vp[posicao].cont && *(vp[posicao].aux + i) != valor; i++);
            if(i == vp[posicao].cont){
                retorno = NUMERO_INEXISTENTE;
            }else{
                for(i += 1; i < vp[posicao].cont; i++){
                    *(vp[posicao].aux + i -1) = *(vp[posicao].aux + i);
                }
                retorno = SUCESSO;
                vp[posicao].cont--;
            }
        } else{
            retorno = ESTRUTURA_AUXILIAR_VAZIA;
        }
    }

    return retorno;
}

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}
/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int i, j;
    int retorno = 0;
    posicao--;
    retorno = validacao_estrutura(posicao);
    if((retorno != POSICAO_INVALIDA) && (retorno != SEM_ESTRUTURA_AUXILIAR)){
        for(i = 0; i < vp[posicao].cont; i++){
            vetorAux[i] = *(vp[posicao].aux + i);
            // printf("vetor: %d", vetorAux[i]);
            retorno = SUCESSO;
        }
    }

    return retorno;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    int i, j, k;
    int retorno = 0;
    int Menor;
    
    posicao--;
    retorno = validacao_estrutura(posicao);
    if((retorno != POSICAO_INVALIDA) && (retorno != SEM_ESTRUTURA_AUXILIAR)){
        for(i = 0; i < vp[posicao].cont; i++){
            vetorAux[i] = *(vp[posicao].aux + i);
        }
        for(j = 0; j < i-1; j++){
            for(k = j+1; k < i; k++){
                if(vetorAux[k] < vetorAux[j]){
                    Menor = vetorAux[k];
                    vetorAux[k] = vetorAux[j];
                    vetorAux[j] = Menor;
                }
            }
        }
        retorno = SUCESSO;
    }

    
    return retorno;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = 0;
    int i, j, T = 0;
    int tavazio = 1;
    
    for(i = 0; i < TAM; i++){
        if(vp[i].cont != 0){
            tavazio = 0;
            for(j = 0; j < vp[i].cont; j++, T++){
                vetorAux[T] = *(vp[i].aux + j); 
            }
        }
    }

    if(tavazio == 1){
        retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }else{
        retorno = SUCESSO;
    }
    
    return retorno;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int retorno = 0;
    int i, j, T = 0;
    int tavazio = 1;
    int aux;

    for(i = 0; i < TAM; i++){
        if(vp[i].cont != 0){
            tavazio = 0;
            for(j = 0; j < vp[i].cont; j++, T++){
                vetorAux[T] = *(vp[i].aux + j); 
            }
        }
    }
    for(i = 0; i < T-1; i++){
        for(j = i + 1; j < T; j++){
            if(vetorAux[j] < vetorAux[i]){
                aux = vetorAux[j];
                vetorAux[j] = vetorAux[i];
                vetorAux[i] = aux;
            }
        }
    }
    if(tavazio == 1){
        retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }else{
        retorno = SUCESSO;
    }
    
    /*for(i = 0; i < TAM; i++){
        if(vp[i].cont != 0){
            printf("estouaqui, %d\n", i);
            tavazio = 0;
            for(j = 0; j < vp[i].cont; j++, T++){
                if(T == 0)
                    vetorAux[T] = *(vp[i].aux + j);
                else{
                    for(k = 0; vetorAux[k] < *(vp[i].aux + j); k++);
                    for(l = T; l >= k; l--){
                        vetorAux[l+1] = vetorAux[l];
                    }
                    vetorAux[k] = *(vp[i].aux + j);
                }
            }
        }
    }
    
    if(tavazio == 1){
        retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }else{
        retorno = SUCESSO;
    }
    // printf("retorno %d", retorno);*/
    
    return retorno;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{

    int retorno = 0;
    int * novo_pont = NULL;
    posicao--;
    retorno = validacao_estrutura(posicao);
    if((retorno != POSICAO_INVALIDA) && (retorno != SEM_ESTRUTURA_AUXILIAR)){
        if(vp[posicao].tamanho + novoTamanho >= 1){
            novo_pont = realloc(vp[posicao].aux, (vp[posicao].tamanho + novoTamanho)*sizeof(int));
            if(novo_pont != NULL){
                vp[posicao].aux = novo_pont;
                vp[posicao].tamanho = vp[posicao].tamanho + novoTamanho; 
                if(vp[posicao].cont > vp[posicao].tamanho)
                    vp[posicao].cont = vp[posicao].tamanho;
                
                retorno = SUCESSO;
            } else{
                retorno = SEM_ESPACO_DE_MEMORIA;
            }
        } else{
            retorno = NOVO_TAMANHO_INVALIDO;
        }    
    }
    
    return retorno;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{

    int retorno = 0;
    posicao--;
    retorno = validacao_estrutura(posicao);
    if((retorno != POSICAO_INVALIDA) && (retorno != SEM_ESTRUTURA_AUXILIAR)){
        if(vp[posicao].cont > 0){
            retorno = vp[posicao].cont;
        } else{
            retorno = ESTRUTURA_AUXILIAR_VAZIA;
        }
    }

    return retorno;
}

No * create_node(int key){
    No * node = malloc(sizeof(No));
    node->conteudo = key;
    node->prox = NULL;
    return node;
}
/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{
    int i, j;
    int key;
    No * node;
    No * head = NULL, * prev = NULL;
    
    for(i = 0; i < TAM; i++){
        if(vp[i].cont > 0){
            for(j = 0; j < vp[i].cont; j++){
                key = *(vp[i].aux + j);
                node = create_node(key);
                if(head == NULL)
                    head = node;
                else{
                    prev->prox = node;
                }
                prev = node;
            }
        }
    }
    
    return head;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
    No * i;
    int j;
    for(i = inicio, j = 0; i != NULL; i = i->prox, j++){
        vetorAux[j] = i->conteudo;
    }
    return;
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
    No * i, * j, * aux;

    j = (*inicio)->prox;
    while(j != NULL && j->prox != NULL){
        aux = j;
        j = j->prox;
        free(aux);
    }
    if(j != NULL)
        free(j);
    *inicio = NULL;
    return;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar(){
    int i;
    for(i = 0; i < TAM; i++){
        vp[i].aux = NULL;
        vp[i].cont = 0;
        vp[i].tamanho = 0;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
    int i;
    int * aux;
    
    for(i = 0; i < TAM; i++){
        if(vp[i].aux != NULL){
            aux = vp[i].aux;
            vp[i].aux = NULL;
            free(aux);
            vp[i].cont = 0;
            vp[i].tamanho = 0;
        }
    }
    
}
