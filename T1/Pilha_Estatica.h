#ifndef PILHA_ESTATICA_H_INCLUDED
#define PILHA_ESTATICA_H_INCLUDED

#define MAXTAM 1000

typedef int t_apontador;
typedef float t_num;
typedef char t_sin;

typedef struct {
  t_num num[MAXTAM];
  t_apontador ultimo_num;
  t_sin sin[MAXTAM];
  t_apontador ultimo_sin;
} t_pilha;


/*Funcao que inicializa a pilha de numeros e sinais
    Parametros:
        -Endereco da pilha
*/
void cria(t_pilha *pilha);

/*Funcao que poem um numero da ultima posicao da pilha de numeros
    Parametros:
        -Endereco da pilha
        -Numero
*/
void push_num(t_pilha *pilha, t_num num);

/*Funcao que poem um sinal da ultima posicao da pilha de sinais
    Parametros:
        -Endereco da pilha
        -Sinal
*/
void push_sin(t_pilha *pilha, t_sin sin);

t_num pop_num(t_pilha *pilha);

t_sin pop_sin(t_pilha *pilha);

/*Funcao que verifica se uma das pilhas esta cheia
    Parametros:
        -Endereco da pilha;
    Retorno:
        -Valor inteiro booleano (1=sim, 0=nao)
*/
int cheia(t_pilha *pilha);

int vazia(t_pilha *pilha);

#endif // PILHA_ESTATICA_H_INCLUDED
