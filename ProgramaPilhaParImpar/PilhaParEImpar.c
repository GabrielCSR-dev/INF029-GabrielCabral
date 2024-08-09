/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.
      
*******************************************************************************/
#include <stdio.h>

#define TAM 3

void delete(int * toppar, int * topimpar){
    int opcao = -2;
    int repete = 1;
    while(repete){
        repete = 0;
        printf("Escolha uma opção:\n 1 - Pilha par\n 2 - Pilha impar\n");
        scanf("%d", &opcao);
        getchar();
        switch(opcao){
            case 1: 
                if(*toppar <= -1){
                    printf("Stack empty!\n");
                } else *toppar = *toppar -1;
                break;
            case 2:
                if(*topimpar <= -1){
                    printf("Stack empty!\n");
                } else *topimpar = *topimpar -1;
                break;
            default: repete = 1; break;

        }
    }
}

void add(int * par, int * impar, int * toppar, int * topimpar){
    int n;

    printf("Adicione um inteiro:\n");
    scanf("%d", &n);
    getchar();

    if(n % 2 == 0){
        if(*toppar >= TAM-1){
            printf("Stack full!\n");
        } else{
            *toppar = *toppar +1;
            par[*toppar] = n;
        }
    } else{
        if(*topimpar >= TAM-1){
            printf("Stack full!\n");
        } else{
            *topimpar = *topimpar +1;
            impar[*topimpar] = n;
        }
    }

}

void listar(int * par, int * impar, int toppar, int topimpar){
    int i;
    if(toppar > -1){
        printf("Pilha par:\n");
        for(i = 0; i <= toppar; i++){
            printf("%d\n", par[i]);
        } 
    } else printf("Pilha par vazia!\n");

    if(topimpar > -1){
        printf("Pilha impar:\n");
        for(i = 0; i <= topimpar; i++){
            printf("%d\n", impar[i]);
        } 
    } else printf("Pilha impar vazia!\n");
}

int main()
{
    int pPAR[TAM], pIMPAR[TAM];
    int toppar = -1, topimpar = -1;
    int opcao = -2;
    int sair = 0;

    while(1){
        printf("Escolha uma opção:\n1 - Adicionar elementos\n2 - Remover elementos\n3 - Listar elementos\n0 - Sair\n");
        scanf("%d", &opcao);
        // getchar();
        printf("%d\n", opcao);
        switch(opcao){
            case 0: return 0;
            case 1: add(pPAR, pIMPAR, &toppar, &topimpar); break;
            case 2: delete(&toppar, &topimpar); break;
            case 3: listar(pPAR, pIMPAR, toppar, topimpar); break;
            default: break;
        }
    }

    return 0;
}