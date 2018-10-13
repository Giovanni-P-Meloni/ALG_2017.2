#include <stdio.h>
#include <stdlib.h>
#include "arvorePV.h"

int main(){

    t_arvoreRN Arvore = NULL;
    t_chave chave;
    int qtdade, op;

    scanf("%d", &qtdade);
    for (int i = 0; i < qtdade; i++){
        scanf("%d", &op);
        switch (op){
            case 1:
                scanf("%d", &chave);
                insere_ARN(&Arvore, chave);
                break;
            case 2:
                scanf("%d", &chave);
                sucessor(Arvore, chave);
                break;
            case 3:
                scanf("%d", &chave);
                antecessor(Arvore, chave);
                break;
            case 4:
                maximo(Arvore);
                break;
            case 5:
                minimo(Arvore);
                break;
            case 6:
                if (Arvore == NULL){
                    printf("erro\n");
                }
                else impressao_pre_ordem(Arvore);
                printf("\n");
                break;
            case 7:
                if (Arvore == NULL){
                    printf("erro\n");
                }
                else impressao_em_ordem(Arvore);
                printf("\n");
                break;
            case 8:
                if (Arvore == NULL){
                    printf("erro\n");
                }
                else impressao_pos_ordem(Arvore);
                printf("\n");
                break;
            default:
                printf("Nao era pra entrar aqui\n");
                break;
        }
    }
    libera_mem(Arvore);
    return 0;
}
