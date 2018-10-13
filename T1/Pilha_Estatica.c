#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pilha_Estatica.h"

void cria(t_pilha *pilha){
    pilha->ultimo_num = -1;
    pilha->ultimo_sin = -1;
}

void push_num(t_pilha *pilha, t_num num){
    if(cheia(pilha)){
        printf("Tamanho excedido\n");
        exit(EXIT_FAILURE);
    }
    pilha->num[++pilha->ultimo_num] = num;
}

void push_sin(t_pilha *pilha, t_sin sin){
    if(cheia(pilha)){
        printf("Tamanho excedido\n");
        exit(EXIT_FAILURE);
    }
    pilha->sin[++pilha->ultimo_sin] = sin;
}

t_num pop_num(t_pilha *pilha){
    if(vazia(pilha) == 1){
        printf("ERRO3\n");
        exit(EXIT_FAILURE);
    }
    return pilha->num[pilha->ultimo_num--];
}

t_sin pop_sin(t_pilha *pilha){
    if(vazia(pilha) == 2){
        printf("ERRO4\n");
        exit(EXIT_FAILURE);
    }
    return pilha->sin[pilha->ultimo_sin--];
}

int cheia(t_pilha *pilha){
    return (pilha->ultimo_num == MAXTAM - 1) || (pilha->ultimo_sin ==  MAXTAM - 1);
}

int vazia(t_pilha *pilha){
    if (pilha->ultimo_num == -1) return 1;
    else if (pilha->ultimo_sin == -1) return 2;
    return 0;
}


