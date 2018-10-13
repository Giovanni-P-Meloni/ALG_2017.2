#ifndef SKIP_LIST_H_INCLUDED
#define SKIP_LIST_H_INCLUDED

#define NAO_ENCONTRADO NULL

typedef char t_chave[50];

typedef struct {
	t_chave palavra;
	char definicao[140];
} t_item;

typedef struct no{
    int nivel;
    t_item item;
    struct no* dir;
    struct no* baixo;
} t_no;

typedef t_no* t_apontador;

//t_skiplist sempre apontara para o Header no Maior nivel.
typedef t_apontador t_skiplist;


/*Funcao que cria a skiplist
        Ao criar a skiplist, o ponteiro dela deve apontar para o header de nivel zero, que nao contem nada e
    aponta para o primeiro item (que no comeco sera NULL)
        Parametros:
            -Endereco do ponteiro da skiplist (t_skiplist*)
        Retorno:
*/
void cria(t_skiplist* slist);

/*Funcao que insere na Skip-List
        Para inserir, deve ser seguido alguns passos. Primeiro deve ser verificado se ja existe um item igual, caso positivo
    a OPERACAO EH INVALIDA , caso negativo, eh necessario saber em qual nivel o elemento sera inserido,
    em seguida, deve saber em qual posicao nesse nivel, por fim devem ser ajustados os ponteiros, esses passos devem
    ser repetidos ate ser atingido o "Ground Level".
        Parametros:
            -Endereco do ponteiro da skiplist (t_apontador*)
            -item a ser inserido (t_item)
        Retorno
*/
void insere_skip(t_skiplist* slist, t_item item);

/*Funcao que busca o item pela chave
        Para buscar basta que o ponteiro percorra a skip-list ate achar o primeiro elemento que seja compativel.
   Porem, caso o usuario busque por uma chave inexistente na skiplist, o ponteiro retornado sera NULL
        Parametros:
            -Endereco do ponteiro da skiplist (t_apontador*)
            -Chave a ser procurada (t_chave)
        Retorno:
            -Ponteiro do item (t_apontador)
*/
t_apontador busca_chave(t_skiplist* slist, t_chave chave);

/*Funcao que remove um item pela chave
        Parecido com a busca, porem o item deve ser deletado em todos os niveis, dessa maneira enquanto o ponteiro desce pela skip-list
    ele ira deletar o item e ajustar os ponteiros. Porem, caso o usuario tente remover um item inexistente a OPERACAO EH INVALIDA.
         Parametros:
            -Endereco do ponteiro da skiplist (t_apontador*)
            -Chave a ser deletada (t_chave)
        Retorno:
*/
void remove_chave(t_skiplist* slist, t_chave chave);

/*Funcao que altera o conteudo do item
        Quase identico a funcao "remove_chave". O item alterado deve ser alterado em todos os niveis, ao inves de ser deletado.
    Essa eh a unica diferenca, fora os parametros. Porem, caso o usuario tente alterar um item inexistente a OPERACAO EH INVALIDA.
        Parametros:
            -Endereco do ponteiro da skiplist (t_apontador*)
            -Item a ser alterado (t_item)
        Retorno:
*/
void altera_item(t_skiplist* slist, t_item item);

/*Funcao que cria niveis segundo a necessidade
        Ao inserir, um dos passos eh saber em qual nivel o elemento sera inserido, se ele deve ser inserido em um nivel
    inexistente devo criar a quantidade de niveis necessaria.
    Parametros:
        -Endereco da skiplist (t_apontador*)
        -Quantidade de niveis a serem adicionados (int)
    Retorno:
*/
void cria_niveis(t_skiplist* slist, int Qtd);


#endif // SKIP_LIST_H_INCLUDED
