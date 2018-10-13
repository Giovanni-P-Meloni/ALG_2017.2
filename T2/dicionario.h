#ifndef DICIONARIO_H_INCLUDED
#define DICIONARIO_H_INCLUDED
#include "skip_list.h"

/*Funcao que imprime todas as palavras inicidadas pelo caracter passado pelo usuario
        Parametros:
             -Endereco do ponteiro da skiplist (t_apontador*)
             -Caracter passado pelo ussuario (char)
        Retorno:
*/
void impressao(t_skiplist *slist, char c);

#endif // DICIONARIO_H_INCLUDED
