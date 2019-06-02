#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

using namespace std;

typedef struct s {
    int tipo; //1=elemento 2=sublista

    union{
        int chave;
        struct s* sublista;
    };

    struct s* prox;

} NO;

void inserir(NO **p, char *x)
{

    int i = 0;
    NO *novo;

    while (x[i])
    {

        if (i == 0)
        {
            novo = (NO *)malloc(sizeof(NO));
            novo->letra = x[i];
            novo->prox = NULL;
            *p = novo;
        }
        else
        {
            novo->prox = (NO *)malloc(sizeof(NO));
            novo->prox->letra = x[i];
            novo->prox->prox = NULL;
            novo = novo->prox;
        }

        i++;
    } //while
} //void inserir

void exibir(NO *x)
{
    if (!x)
        return;
    NO *p = x;
    int i = 1;
    while (p)
    {
        printf("%c", p->letra);
        p = p->prox;
        i++;
    }
}

NO *copiar(NO *p)
{
    int i = 0; //variavel para localizar o primeiro elemento
    NO *cpy = NULL;
    NO *novo = (NO *)malloc(sizeof(NO));

    while (p)
    {

        if (i == 0)
        {
            novo->letra = p->letra;
            novo->prox = NULL;
            cpy = novo;
            p = p->prox;
        }
        else
        {
            novo->prox = (NO *)malloc(sizeof(NO));
            novo->prox->letra = p->letra;
            novo->prox->prox = NULL;
            novo = novo->prox;
            p = p->prox;
        }
        i++;
    }
    return cpy;
}

NO *inverterTudo(NO *resp)
{

    NO *x = resp;
    int i = 0; //CONTADOR PARA VERIFICAR O PRIMEIRO ELEMENTO
    NO *aux;
    NO *ant;

    if (x->prox->prox)
    { //VERIFICA SE POSSUI PELO MENOS TRES ELEMENTOS

        while (x)
        {

            if (i == 0)
            { // CONDICIONAL APENAS PARA A PRIMEIRA LETRA

                aux = x->prox->prox;
                ant = x->prox;
                ant->prox = x;
                x->prox = NULL;
                x = aux;
            }
            else
            {

                if (x->prox)
                { //VERIFICA SE AINDA TEM LETRA A SEGUIR

                    aux = x->prox;
                    x->prox = ant;
                    ant = x;
                    x = aux;
                }
                else
                { //CASO N�O TEM LETRA A SEGUIR, INVERTE E QUEBRA O LAcO
                    x->prox = ant;
                    break;
                }
            }
            i++; // CONTADOR

        } //while
    }
    else
    { //CASO NaO TENHA TReS ELEMENTOS SIGNIFICA QUE TEM APENAS 1 OU 2;

        x->prox->prox = x;
        resp = x->prox;
        x->prox = NULL;
        return resp;
    }

    return x;
}

NO *inverterBlocoDeNaoVogais(NO *inicio, NO *fim)
{

    NO *x = inicio; // X EQUIVALE AO NO ATUAL DA LISTA
    int i = 0;
    NO *aux = NULL;
    NO *ant;

    if (x->prox != fim)
    { //SE N�O HOUVER APENAS DUAS NAO VOGAIS PARA TROCAR

        while (x != fim)
        {

            if (i == 0)
            { //CASO SEJA O PRIMEIRO ELEMENTO DA LISTA

                aux = x->prox->prox;
                ant = x->prox;
                ant->prox = x;
                x->prox = NULL;
                x = aux;
                aux = x->prox;

                if (x == fim)
                { // CASO AP�S A TROCA J� TENHA CHEGADO NO FIM DO BLOCO DE NAO VOGAIS, QUEBRA O LA�O
                    x->prox = ant;
                    break;
                }
            }
            else
            {

                if (x->prox == fim)
                { // SE A PROXIMA LETRA FOR A ULTIMA DO BLOCO, INVERTE OS PONTEIROS E QUEBRA O LA�O

                    aux = x->prox;
                    x->prox = ant;
                    ant = x;
                    x = aux;
                    x->prox = ant;
                    break;
                }
                else
                { // INVERTE A NAO VOGAL NORMALMENTE

                    aux = x->prox;
                    x->prox = ant;
                    ant = x;
                    x = aux;
                    aux = x->prox;
                }

                if (x == fim)
                { // CASO AP�S A INVERSAO J� TENHA CHEGADO NA ULTIMA NAO VOGAL DO BLOCO, QUEBRA O LA�O
                    x->prox = ant;
                    break;
                }
            }

            i++;
        } //while
    }
    else
    { // SE O PROXIMO VALOR J� FOR O ULTIMO DO BLOCO, SIGNIFICA QUE TEMOS APENAS DUAS NAO VOGAIS PARA INVERTER

        x->prox = NULL;
        fim->prox = x;
        x = fim;
        return x;
    }

    return x;
}

NO *inverterNaoVogais(NO *lista)
{

    NO *x = lista;         // VARIAVEL EQUIVALE AO NO ATUAL DA LISTA
    NO *Vogal = NULL;      //VARIAVEL PARA SALVAR A VOGAL ANTES DO BLOCO DE NAO VOGAL A SER INVERTIDO
    bool primeira = false; //VERIFICADOR SE EXISTE A PRIMEIRA NAO VOGAL DO BLOCO A SER INVERTIDA
    NO *NaoVogal = NULL;   //VARIAVEL PARA ARMAZENAR A PRIMEIRA NAO VOGAL DO BLOCO A SER INVERTIDO

    while (x)
    {

        if (toupper(x->letra) == 'A' || toupper(x->letra) == 'E' || toupper(x->letra) == 'I' || toupper(x->letra) == 'O' || toupper(x->letra) == 'U')
        { // VERIFICA SE A LETRA � VOGAL

            Vogal = x; //
            x = x->prox;

            if (!x)
            {
                x = NULL;
                break;
            }

            if (x->prox == NULL)
            { //SE ESSA LETRA FOR A ULTIMA, QUEBRA O LA�O
                x = NULL;
                break;
            }
        }
        else if (toupper(x->prox->letra) != 'A' && toupper(x->prox->letra) != 'E' && toupper(x->prox->letra) != 'I' && toupper(x->prox->letra) != 'O' && toupper(x->prox->letra) != 'U')
        {
            //CASO A PROXIMA LETRA SEJA NAO VOGAL TAMB�M, SIGNIFICA QUE TEMOS PELO MENOS DUAS NAO VOGAIS

            if (primeira == false)
            { //SALVA A PRIMEIRA NAO VOGAL DO BLOCO, PARA SER USADA NA INVERSAO DEPOIS
                NaoVogal = x;
                primeira = true;
            }

            x = x->prox; //PASSA PARA AS PROXIMAS NAO VOGAIS

            if (x->prox == NULL && primeira == true)
            { //INVERSAO DE NAO VOGAIS NO FIM DA LISTA

                x = inverterBlocoDeNaoVogais(NaoVogal, x);

                if (Vogal)
                { //CASO TENHA TIDO UMA VOGAL ANTES
                    Vogal->prox = x;
                }
                else
                { // CASO A LISTA NAO TENHA TIDO VOGAIS
                    lista = x;
                }
                break;
            }
        }
        else
        { //CASO A PROXIMA LETRA SEJA VOGAL

            if (primeira == true)
            { //CASO EXISTE A PRIMEIRA NaoVogal DO BLOCO, COME�A A INVERSAO

                /// ---------------   INVERSAO  ------------------------ AQUI ACONTECE A MAGICA

                if (Vogal)
                {

                    ///INVERTE O BLOCO DE NAO VOGAIS
                    NO *temp;
                    temp = x->prox;                            // SALVA A VOGAL QUE EST� DEPOIS DO BLOCO
                    x = inverterBlocoDeNaoVogais(NaoVogal, x); //INVERTE O BLOCO DE NAO VOGAIS DE NaoVogal(INICIO) AT� X(FIM)
                    Vogal->prox = x;                           //A VOGAL ANTERIOR AO BLOCO INVERTIDO APONTA PARA PARA O X QUE AGORA � O COME�O DO BLOCO INVERTIDO
                    NaoVogal->prox = temp;                     //A NaoVogal QUE PASSOU A SER O ULTIMO ELEMENTO DO BLOCO INVERTIDO APONTA PARA A VOGAL SEGUINTE DO BLOCO
                    x = temp;                                  // X ATUALIZA O VALOR PARA A PROXIMA VOGAL
                    Vogal = x;                                 // A VOGAL JA TOMA SEU VALOR DE PRIMEIRA VOGAL PR�-BLOCO, CASO HAJA OUTRO BLOCO DE NAO VOGAIS EM SEGUIDA
                    primeira = false;                          //VIRA FALSO E PASSA PARA A PROXIMO BLOCO DE NAO VOGAIS A SER INVERTIDO
                }
                else
                {   //CASO NAO TENHA VALOR NA VARIAVEL VOGAL SIGNIFICA QUE A LISTA SO TEVE NAO VOGAIS POR ENQUANTO
                    /// FAZ A INVERSAO DO BLOCO DE NAO VOGAIS CASO A LISTA TENHA COMECADO APENAS COM NAO VOGAIS

                    NO *temp;
                    temp = x->prox;
                    x = inverterBlocoDeNaoVogais(NaoVogal, x);
                    lista = x;
                    NaoVogal->prox = temp;
                    x = temp;
                    primeira = false;
                }

                if (x->prox == NULL)
                { // SE O PROXIMO VALOR AP�S INVERSOES FOR NULL, QUEBRA O LA�O POIS CHEGOU NO FIM DA LISTA
                    x = NULL;
                    break;
                }
            }
            else
            {   //CASO A VARIAVEL PRIMEIRA==FALSE, SIGNIFICA QUE EXISTE UMA VOGAL ANTES E OUTRA DEPOIS
                //POR CAUSA DISSO N�O � NECESS�RIO INVERTER E APENAS CONTINUA-SE O C�DIGO NORMALMENTE
                x = x->prox;
            }
        }

        if (x->prox == NULL && primeira == true)
        { // CASO O FINAL DA LISTA SEJA COM NAO VOGAIS

            x = inverterBlocoDeNaoVogais(NaoVogal, x); //NAO � NECESS�RIO MAIS TROCAS, APENAS INVERTER O ULTIMO BLOCO

            if (Vogal)
            { //CASO TENHA TIDO VOGAIS ANTES
                Vogal->prox = x;
            }
            break;
        }

    } //WHILE

    return lista;

} //LISTA

// o EP consiste em implementar esta funcao

NO *codificar(NO *frase)
{
    NO *resp = frase;

    if (frase && frase->prox)
    {                         //VERIFICA SE EXISTE MAIS DE UM ELEMENTO
        resp = copiar(frase); //FAZ UMA COPIA PARA MANTER A LISTA DE NO ORIGINAL INTACTA
        resp = inverterNaoVogais(resp);
        resp = inverterTudo(resp);
    }

    return resp;
} //NO* codificar

//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------

int main()
{
    NO *p = NULL;

    // aqui vc pode incluir codigo para inserir elementos
    // de teste na sua lista apontada por p

    //USEI ESSES PARA ME AUXLIAR
    //char frase[500];
    // strcpy(frase, "ESTRUTURAS DE DADOS E MUITO LEGAL.");
    //inserir(&p,frase);

    // o EP sera testado com chamadas deste tipo
    NO *teste = NULL;
    teste = codificar(p);

    // e aqui precisaria percorrer a lista teste para ver se ficou correta etc.

    // exibir(teste);
}

// por favor nao inclua nenhum c�digo abaixo da fun��o main()
