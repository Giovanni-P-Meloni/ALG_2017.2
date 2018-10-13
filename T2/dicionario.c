#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "skip_list.h"
#include "dicionario.h"

void impressao(t_skiplist *slist, char c){
    int found = 0;
    t_apontador pos = (*slist);

    while (pos->nivel != 0){
        if(pos->dir == NULL) pos = pos->baixo;
        else{
            if(c > (pos->dir->item.palavra[0])) pos = pos->dir;
            else pos = pos->baixo;
        }
    }
    while(pos!=NULL && !found){
        if(c != (pos->dir->item.palavra[0])) pos = pos->dir;
        else found = 1;
    }
    if (found){
        while (pos->dir->item.palavra[0] == c) {
            printf("%s %s\n", pos->dir->item.palavra, pos->dir->item.definicao);
            pos = pos->dir;
        }
    }
}

