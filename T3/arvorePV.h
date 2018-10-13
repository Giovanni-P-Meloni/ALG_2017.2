#ifndef ARVOREPV_H_INCLUDED
#define ARVOREPV_H_INCLUDED

typedef int t_chave;

/*
typedef struct{
    t_chave chave;
    char cor;
}t_item;
*/
typedef struct no{
    char cor;
    t_chave num;
    struct no* pai;
    struct no* filho_e;
    struct no* filho_d;
}t_no;

typedef t_no* t_apontador;

typedef t_apontador t_arvoreRN;

void insere_ARN(t_arvoreRN* A, t_chave chave);
void cria(t_apontador* x, t_apontador* pai, int num);

void balanceia(t_arvoreRN* A, t_apontador* M);

void sucessor(t_arvoreRN A, t_chave chave);
void antecessor(t_arvoreRN A, t_chave chave);
void maximo(t_arvoreRN A);
void minimo(t_arvoreRN A);
void impressao_pre_ordem(t_arvoreRN A);
void impressao_em_ordem(t_arvoreRN A);
void impressao_pos_ordem(t_arvoreRN A);
void libera_mem(t_arvoreRN A);

#endif // ARVOREPV_H_INCLUDED
