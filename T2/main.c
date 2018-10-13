#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "skip_list.h"
#include "dicionario.h"

int main() {

    char linha[100000];
    char func[300];
    int pos, num;
    t_skiplist S;
    t_item item;
    t_apontador procuro;
    char c;
    cria(&S);

    while (fgets(linha, 100000, stdin) != NULL){
        pos = 0;
        sscanf(&linha[pos], "%s%n", func, &num);
        pos += num;

        switch (func[1]){
        //iNsercao
            case 'n':
                sscanf(&linha[pos], " %s%n", item.palavra, &num);
                pos += num;
                sscanf(&linha[pos], " %[^\n]s%n", item.definicao, &num);
                pos += num;
                insere_skip(&S, item);
            break;
       //aLteracao
            case 'l':
                sscanf(&linha[pos], " %s%n", item.palavra, &num);
                pos += num;
                sscanf(&linha[pos], " %[^\n]s%n", item.definicao, &num);
                pos += num;
                altera_item(&S, item);
            break;
        //bUsca
            case 'u':
                sscanf(&linha[pos], " %s%n", item.palavra, &num);
                pos += num;
                procuro = busca_chave(&S, item.palavra);
                if(procuro == NULL) printf("OPERACAO INVALIDA\n");
                else printf("%s %s\n", procuro->item.palavra, procuro->item.definicao);
            break;
        //iMpressao
            case 'm':
                //printf("flag\n");
                sscanf(&linha[pos], " %c%n", &c, &num);
                //printf("%c\n", c);
                pos += num;
                impressao(&S, c);
            break;
        //rEmove
            case 'e':
                sscanf(&linha[pos], " %s%n", item.palavra, &num);
                pos += num;
                remove_chave(&S, item.palavra);
            break;
            default:
                printf("OPERACAO INVALIDA\n");
        }
    }
    return 0;
}
