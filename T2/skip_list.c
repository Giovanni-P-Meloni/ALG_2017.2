#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "skip_list.h"


void cria(t_skiplist* slist){

    srand (time(NULL));
    t_apontador p = (t_apontador) malloc(sizeof(t_no));
    p->dir = NULL;
    p->baixo = NULL;
    p->nivel = 0;
    *slist = p;
    return;
}

void insere_skip(t_skiplist* slist, t_item item){

    if(busca_chave(slist, item.palavra) != NULL) {
            printf("OPERACAO INVALIDA\n");
            return;
    }

    //      -Em qual maior nivel o novo elemento sera inserido
    int found = 0;
    int inserenivel = 0;
    t_apontador pos = *slist;
    //Quantos niveis deve subir
    int h = 1;
    while(h){
        if((rand() % 2) == 1) h = 0;
        else inserenivel++;
    }
    //Eh maior que o nivel atual?
    if (inserenivel > (*slist)->nivel){
        cria_niveis(slist, inserenivel-((*slist)->nivel));
        pos = *slist;
    }
    //Caso contrario, coloco o ponteiro niv, onde ele deve estar
    else{
        for(int i = pos->nivel; i >= 0 && !found; i--){
            if (i == inserenivel) found = 1;
            else pos = pos->baixo;
        }
    }

    //      -Deve inserir o elemento EM ORDEM, de CIMA PARA BAIXO (ate ser atingido o nivel 0).
   t_apontador Last = NULL;
   while (pos != NULL){
        found = 0;
        t_apontador New = (t_apontador) malloc(sizeof(t_no));
        if (New == NULL){
            printf("Erro: memoria insuficiente\n");
            exit(EXIT_FAILURE);
        }
        strcpy(New->item.palavra, item.palavra);
        strcpy(New->item.definicao, item.definicao);
        New->baixo = NULL;
        New->nivel = pos->nivel;
        while (pos->dir != NULL && !found){
            if (strcmp(New->item.palavra, pos->dir->item.palavra) < 0) found = 1;
            else pos = pos->dir;
        }
        if (Last != NULL) Last->baixo = New;
        New->dir = pos->dir;
        pos->dir = New;
        Last = New;
        pos = pos->baixo;
   }
   return;
}

t_apontador busca_chave(t_skiplist* slist, t_chave chave){

   // int found = 0;
    t_apontador pos = (*slist);
    //Descendo pelos niveis
    while (pos != NULL){
        if (pos->dir == NULL) pos = pos->baixo;
        else {
            if(strcmp(chave, pos->dir->item.palavra) > 0) pos = pos->dir;
            else if (strcmp(chave, pos->dir->item.palavra) < 0) pos = pos->baixo;
            else if  (strcmp(chave, pos->dir->item.palavra) == 0) {
                pos = pos->dir;
                return pos;
            }
        }
    }
    return pos;

}

void remove_chave(t_skiplist* slist, t_chave chave){
    if(busca_chave(slist, chave) == NULL) {
            printf("OPERACAO INVALIDA\n");
            return;
    }

    t_apontador pos = *slist;
    while (pos != NULL){
        if (pos->dir == NULL) pos = pos->baixo;
        else{
            if(strcmp(chave, pos->dir->item.palavra) > 0) pos = pos->dir;
            else if(strcmp(chave, pos->dir->item.palavra) < 0) pos = pos->baixo;
            else if(strcmp(chave, pos->dir->item.palavra) == 0){
                t_apontador aux = pos->dir;
                pos->dir = pos->dir->dir;
                free(aux);
                pos = pos->baixo;
            }
        }
    }
    return;
}

void altera_item(t_skiplist* slist, t_item item){
    if(busca_chave(slist, item.palavra) == NULL) {
            printf("OPERACAO INVALIDA\n");
            return;
    }

    t_apontador pos = *slist;
    while (pos != NULL){
        if (pos->dir == NULL) pos = pos->baixo;
        else{
            if(strcmp(item.palavra, pos->dir->item.palavra) > 0) pos = pos->dir;
            else if(strcmp(item.palavra, pos->dir->item.palavra) < 0) pos = pos->baixo;
            else if(strcmp(item.palavra, pos->dir->item.palavra) == 0){
                pos = pos->dir;
                strcpy(pos->item.definicao, item.definicao);
                pos = pos->baixo;
                while(pos != NULL){
                    strcpy(pos->item.definicao, item.definicao);
                    pos = pos->baixo;
                }
            }
        }
    }
    return;
}

void cria_niveis(t_skiplist* slist, int Qtd){

    for (int i=Qtd; i>0; i--){
        t_apontador new_lvl = (t_apontador) malloc(sizeof(t_no));
        if (new_lvl == NULL){
            printf("Erro: memoria insuficiente\n");
            exit(EXIT_FAILURE);
        }
        new_lvl->dir = NULL;
        new_lvl->baixo = *slist;
        new_lvl->nivel = ((*slist)->nivel)+1;
        *slist = new_lvl;
    }
    return;
}

