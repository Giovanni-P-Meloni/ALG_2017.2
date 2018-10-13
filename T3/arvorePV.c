#include <stdio.h>
#include <stdlib.h>
#include "arvorePV.h"

void insere_ARN(t_arvoreRN* A, t_chave chave){

    t_apontador* track;
    t_apontador pai;
    track = A;
    pai = NULL;

    //enquanto nao chegar em uma folha externa
    while (*track != NULL){
        //Desce pela esquerda
        if (chave < (*track)->num){
            pai = *track;
            track = &(*track)->filho_e;
        }
        //Desce pela direita
        else if (chave > (*track)->num){
            pai = *track;
            track = &(*track)->filho_d;
        }
    }
    cria(track, &pai, chave);
    balanceia(A, track);
}

void cria(t_apontador* x, t_apontador* pai, int num){
    t_apontador p = (t_apontador) malloc(sizeof(t_no));
    p->cor = 'v';
    p->pai = *pai;
    p->filho_d = NULL;
    p->filho_e = NULL;
    p->num = num; // Numero de inicializacao
    *x = p;
    return;
}

void balanceia(t_arvoreRN* A, t_apontador* M){
    t_apontador tio, avo, aux;
    t_apontador x = *M;
    t_apontador pai = x->pai;
    int repete;
    char cor_aux;

    do {
        repete = 0;
        if (pai != NULL){
            avo = pai->pai;
            if (avo == NULL) tio = NULL;
            else if (avo->filho_e == pai) tio = avo->filho_d;
            else tio = avo->filho_e;

        //Se a cor do pai nao for preta duas coisas podem acontecer:
            if(pai->cor != 'p'){
            //1- A cor do tio pode ser vermelha, nesse caso recolore e refaz os passos com o avo.
                if(tio != NULL && tio->cor == 'v'){
                    pai->cor = 'p';
                    tio->cor = 'p';
                    avo->cor = 'v';
                    x = avo;
                    pai = x->pai;
                    repete = 1;
                }
            //2- A cor do tio pode ser preta (OU NULL), nesse caso ha 4 possiveis situacoes.
                else{
                    //2.1- Caso Esquerda-Esquerda: O pai for filho esquerdo do avo, e x for filho esquerdo do pai
                    //Rotacao simples do avo para direita
                    if(x == pai->filho_e && pai == avo->filho_e){
                        //O avo pode ser raiz.
                        if (avo->pai != NULL){
                            if (avo == avo->pai->filho_d) avo->pai->filho_d = pai;
                            else if (avo == avo->pai->filho_e) avo->pai->filho_e = pai;
                        }
                        //Se o avo era a raiz, ela devera mudar
                        else (*A) = pai;
                        aux = avo->pai;
                        avo->pai = pai;
                        avo->filho_e = pai->filho_d;
                        pai->pai = aux;
                        pai->filho_d = avo;
                        cor_aux = avo->cor;
                        avo->cor = pai->cor;
                        pai->cor = cor_aux;
                    }
                    //2.2- Caso Esquerda-Direita: O pai for filho esquerdo do avo, e x for filho direito do pai
                    //Rotacao Dupla, primeiro rotaciona o pai para esquerda, depois o avo para a direita
                    else if (x == pai->filho_d && pai == avo->filho_e){
                        //Rotacao para esquerda.
                        avo->filho_e = x;
                        x->pai = avo;
                        aux = x->filho_e;
                        x->filho_e = pai;
                        pai->filho_d = aux;
                        pai->pai = x;
                        //Rotacao para direita
                        //O avo pode ser raiz.
                        if(avo->pai != NULL){
                            if(avo == avo->pai->filho_d) avo->pai->filho_d = x;
                            else if (avo == avo->pai->filho_e) avo->pai->filho_e = x;
                        }
                        //Se o avo era a raiz, ela devera mudar
                        else (*A) = x;
                        aux = avo->pai;
                        avo->pai = x;
                        avo->filho_e = x->filho_d;
                        x->pai = aux;
                        x->filho_d = avo;
                        cor_aux = avo->cor;
                        avo->cor = x->cor;
                        x->cor = cor_aux;
                    }
                    //2.3- Caso Direita-Direita: O pai for filho direito do avo, e x for filho direito do pai
                    //Rotacao simples do avo para esquerda
                    else if (x == pai->filho_d && pai == avo->filho_d){
                        if(avo->pai != NULL){
                            if(avo == avo->pai->filho_d) avo->pai->filho_d = pai;
                            else if (avo == avo->pai->filho_e) avo->pai->filho_e = pai;
                        }
                        //Se o avo era a raiz, ela devera mudar.
                        else (*A)= pai;
                        aux = avo->pai;
                        avo->pai = pai;
                        avo->filho_d = pai->filho_e;
                        pai->pai = aux;
                        pai->filho_e = avo;
                        cor_aux = avo->cor;
                        avo->cor = pai->cor;
                        pai->cor = cor_aux;
                    }
                    //2.4- Caso Direita-Esquerda: O pai for filho direito do avo, e x for filho esquerdo do pai
                    //Rotacao dupla, primeiro o pai para a direita, de pois o avo para a esquerda
                    else if (x == pai->filho_e && pai == avo->filho_d){

                        //Rotacao para direita
                        avo->filho_d = x;
                        x->pai = avo;
                        aux = x->filho_d;
                        x->filho_d = pai;
                        pai->filho_e = aux;
                        pai->pai = x;
                        //Rotacao para esquerda
                        //O avo pode ser raiz
                        if(avo->pai != NULL){
                            if(avo == avo->pai->filho_d) avo->pai->filho_d = x;
                            else if (avo == avo->pai->filho_e) avo->pai->filho_e = x;
                        }
                        //Se o avo era a raiz, ela devera mudar
                        else (*A) = x;
                        aux = avo->pai;
                        avo->pai = x;
                        avo->filho_d = x->filho_e;
                        x->pai = aux;
                        x->filho_e = avo;
                        cor_aux = avo->cor;
                        avo->cor = x->cor;
                        x->cor = cor_aux;
                    }
                }
            }
        }
    } while (repete);

    //Raiz, a cor eh sempre preta.
    if (pai == NULL){
        x->cor = 'p';
        (*A) = x;
    }
}

void sucessor(t_arvoreRN A, t_chave chave){
    t_apontador track;
    track = A;
    //primeiro deve buscar pelo no da chave
    while (track != NULL && track->num != chave){
        if (chave > track->num) track = track->filho_d;
        else track = track->filho_e;
    }
    if (track == NULL){
        printf("erro\n");
        return;
    }
    //Sucessor eh o maior mais proximo de "chave", ou ainda; sucessor eh o MENOR de TODOS OS MAIORES que a chave
    if (track->filho_d == NULL) {
        if (track->num > track->pai->num) printf("erro\n");
        else printf("%d\n", track->pai->num);
        return;
    }
    track = track->filho_d;
    while (track->filho_e != NULL) track = track->filho_e;
    printf("%d\n", track->num);
}

void antecessor(t_arvoreRN A, t_chave chave){
    t_apontador track;
    track = A;
    //primeiro deve buscar pelo no da chave
    while (track != NULL && track->num != chave){
        if (chave > track->num) track = track->filho_d;
        else track = track->filho_e;
    }
    if (track == NULL){
        printf("erro\n");
        return;
    }
    //Antecessor eh o menor mais proximo de "chave", ou ainda; antecessor eh o MAIOR de TODOS OS MENORES que a chave
    if (track->filho_e == NULL) {
        if (track->num < track->pai->num) printf("erro\n");
        else printf("%d\n", track->pai->num);
        return;
    }
    track = track->filho_e;
    while (track->filho_d != NULL) track = track->filho_d;
    printf("%d\n", track->num);
}

void maximo(t_arvoreRN A){
    if (A == NULL) printf("erro\n");
    else {
        t_apontador track;
        track = A;
        while (track->filho_d != NULL) track = track->filho_d;
        printf("%d\n", track->num);
    }
}

void minimo(t_arvoreRN A){
    if (A == NULL) printf("erro\n");
    else {
        t_apontador track;
        track = A;
        while (track->filho_e != NULL) track = track->filho_e;
        printf("%d\n", track->num);
    }
}

void impressao_pre_ordem(t_arvoreRN A){
    if(A != NULL){
        printf("%d ", A->num);
        impressao_pre_ordem(A->filho_e);
        impressao_pre_ordem(A->filho_d);
    }
}

void impressao_em_ordem(t_arvoreRN A){
    if(A != NULL){
        impressao_em_ordem(A->filho_e);
        printf("%d ", A->num);
        impressao_em_ordem(A->filho_d);
    }
}

void impressao_pos_ordem(t_arvoreRN A){
    if(A != NULL){
        impressao_pos_ordem(A->filho_e);
        impressao_pos_ordem(A->filho_d);
        printf("%d ", A->num);
    }
}

void libera_mem(t_arvoreRN A){
    if (A != NULL){
        libera_mem(A->filho_e);
        libera_mem(A->filho_d);
        free(A);
    }
}
