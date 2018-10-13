#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Pilha_Estatica.h"


/*Funcao que checa a validacao da expressao fornecida
    Paremetros:
        -linha (a expressao)
        -tamanho da linha
    Retorno:
        -Valor inteiro booleano (1-valido, 0-nao valido)
*/
int checa_Valid(char* linha, int sz){
    int valid = 1;
    int pos = 0;
    int qtd_num = 0;
    int qtd_sin = 0;
    int qtd_opn = 0;
    int qtd_cls = 0;
    int check, prcorr;
    float num;
    char simb;

    //analisando a linha
    while(pos < sz-1){
        check = sscanf(&linha[pos], "%f%n", &num, &prcorr);
        if(check){
            qtd_num++;
            pos += prcorr;
        }
        else {
            sscanf(&linha[pos], " %c%n", &simb, &prcorr);
            if (simb == '(') qtd_opn++;
            else if (simb == ')') qtd_cls++;
            else qtd_sin++;
            pos += prcorr;
        }
    }

    //Ponto e virgula ou virgula no final
    if (linha[sz-1] != ';' && linha[sz-1] != ',') valid = 0;
    //Quantidade de numeros = Quantidade de operadores + 1
    if (qtd_num != qtd_sin + 1) valid = 0;
    //Quantidade de '(' = Quantidade de ')'
    if (qtd_opn != qtd_cls) valid = 0;

    return valid;
}

/*Funcao que calcula a expressao dentro de um parenteses
    Parametro:
        -linha (a expressao)
        -endereco da variavel responsavel por dizer onde na linha esta(int*)
        -endereco da variavel responsavel por dizer se a expressao e valida(int*)
        -Endereco da pilha da expressao inteira;
*/
void calcula_Parent (char *linha, int* pos, int *valid ,t_pilha* PO){

    //basicamente uma repeticao do codigo na main,
    //porem com uma condicao de parada diferente
    int check, prcorr;
    char sin, car;
    float op1, op2, num;
    t_pilha pilha;
    cria(&pilha);
    int atual = *pos;

    sscanf(&linha[atual], "%c", &car);
    while(car != ')' && *valid){
        sin = '0';
        check = sscanf(&linha[atual], "%f%n", &num, &prcorr);
        if(check){ // portanto encontrei um numero
            push_num(&pilha, num); //coloco o numero na pilha
            atual += prcorr;
        }
        else if(!check){//portanto encontrei um sinal
            check = sscanf(&linha[atual], " %c%n", &sin, &prcorr);
            //Esse sinal pode ser um operador ou um parenteses.
            if (sin == '(') {
                atual += prcorr;
                calcula_Parent(linha, &atual, valid, &pilha);
            }
            else {
                push_sin(&pilha, sin);//coloco o sinal na pilha
                atual += prcorr;
            }
        }
        //Enquanto empilha, se houver operacoes com prioridade maior, faco sua conta para depois apenas sobrar contas de soma e subtracao na pilha,
        //cuja prioridade eh igual.
        if (sin == '*' || sin == '/'){
            check = sscanf(&linha[atual], "%f%n", &num, &prcorr);
            if(check){
                push_num(&pilha, num);
                atual += prcorr;
            }
            else if(!check){
                check = sscanf(&linha[atual], " %c%n", &sin, &prcorr);
                if(sin == '('){
                    atual += prcorr;
                    calcula_Parent(linha, &atual, valid, &pilha);
                    }
            }

            op2 = pop_num(&pilha);
            op1 = pop_num(&pilha);
            sin = pop_sin(&pilha);
            switch (sin){//opero com ele e o anterior, na sequencia correta
                case '*':
                    push_num(&pilha, op1 * op2);
                    break;
                case '/':
                    if (op2 == 0) *valid = 0;
                    push_num(&pilha, op1 / op2);
                    break;
            }
        }
        sscanf(&linha[atual], "%c%n", &car, &prcorr);
    }
    *pos = atual+prcorr;// atualiza posicao para quando voltar na main

    //O segundo laco ficara responsavel por fazer contas de soma e subtracao, cuja prioridade eh a mesma.
    //Para tanto, bastar comecar a desempilhar ate ficar com apenas um numero na pilha, que e a resposta.
    while(pilha.ultimo_num != 0 && *valid){
        op2 = pop_num(&pilha);
        op1 = pop_num(&pilha);
        sin = pop_sin(&pilha);
        switch (sin){
            case '+':
                push_num(&pilha, op1 + op2);
                break;
            case '-':
                push_num(&pilha, op1 - op2);
                break;
        }
    }
    if (valid) push_num(PO, pilha.num[0]);
}

int main(){
    char linha[1000];
    int pos, check, prcorr, sz, valid;
    float op1, op2, num;

    do{
        char sin;
        t_pilha P;
        cria(&P);
        gets(linha);
        pos = 0;
        sz = strlen(linha);
        valid = checa_Valid(linha, sz);
        if(!valid) printf("Expressao incorreta\n");
        else{
            char car;
            sscanf(&linha[pos], "%c", &car);
            //enquanto nao estiver no fim da linha, isto e, em um ',' ou ';', continuo operando
            while (car != ';' && car != ',' && valid){
                sin = '0';
                check = sscanf(&linha[pos], "%f%n", &num, &prcorr);
                if(check){ // portanto encontrei um numero
                    push_num(&P, num); //coloco o numero na pilha
                    pos += prcorr;
                }
                else if(!check){//portanto encontrei um sinal
                    check = sscanf(&linha[pos], " %c%n", &sin, &prcorr);
                    //Esse sinal pode ser um operador ou um parenteses.
                    if (sin == '(') {
                        pos += prcorr;
                        calcula_Parent(linha, &pos, &valid, &P);
                    }
                    else {
                        push_sin(&P, sin);//coloco o sinal na pilha
                        pos += prcorr;
                    }
                }
                //Enquanto empilha, se houver operacoes com prioridade maior, faco sua conta para depois apenas sobrar contas de soma e subtracao na pilha,
                //cuja prioridade eh igual.
                if (sin == '*' || sin == '/'){
                    check = sscanf(&linha[pos], "%f%n", &num, &prcorr);
                    if(check){
                        push_num(&P, num);
                        pos += prcorr;
                    }
                    else if(!check){
                       check = sscanf(&linha[pos], " %c%n", &sin, &prcorr);
                        if(sin == '('){
                            pos += prcorr;
                            calcula_Parent(linha, &pos, &valid, &P);
                           }
                    }

                    op2 = pop_num(&P);
                    op1 = pop_num(&P);
                    sin = pop_sin(&P);
                    switch (sin){//opero com ele e o anterior, na sequencia correta
                        case '*':
                            push_num(&P, op1 * op2);
                            break;
                        case '/':
                            if (op2 == 0) valid = 0;
                            push_num(&P, op1 / op2);
                            break;
                    }
                }
                sscanf(&linha[pos], "%c", &car);
            }
            //O segundo laco ficara responsavel por fazer contas de soma e subtracao, cuja prioridade eh a mesma.
            //Para tanto, bastar comecar a desempilhar ate ficar com apenas um numero na pilha, que e a resposta.
            while(P.ultimo_num != 0 && valid){
                op2 = pop_num(&P);
                op1 = pop_num(&P);
                sin = pop_sin(&P);
                switch (sin){
                    case '+':
                        push_num(&P, op1 + op2);
                        break;
                    case '-':
                        push_num(&P, op1 - op2);
                        break;
                }
            }
            if(!valid) printf("Expressao incorreta\n");
            else printf("%.2f\n", pop_num(&P));
        }
    }while(linha[sz-1] != ',');
}
