#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define N 16

enum {O, X, VAZIO};

int COMPUTADOR = 1;
int HUMANO = 0;

void valoresTabuleiro (int x[])
{
    for (int i = 0; i < N; i++)
        x[i] = VAZIO;
}

void imprimirTabuleiro (int x[])
{
    char simbolos [] = {'O', 'X', '*'};
    printf ("\n                                     TABULEIRO\n\n");
    for (int i = 0; i < N; i++)
    {
        if (i != 0 && i % 4 == 0)
            printf ("         \n            _________________________________________________________\n");
        printf ("            | %c |", simbolos[x[i]]);
    }
    printf ("\n\n");
}

int tabuleiroCheio (const int x[])
{
    for (int i = 0; i < N; i++)
    {
        if (x[i] == VAZIO)
            return 0;
    }
    return 1;
}

void fazerAJogada (int x[], const int move, const int lado)
{
    x[move] = lado;
}

int combinacoes (const int x[], const int lado)
{
    //HORIZONTAL
    if (x[0] == lado && x[1] == lado && x[2] == lado && x[3] == lado)
        return 1;
    if (x[4] == lado && x[5] == lado && x[6] == lado && x[7] == lado)
        return 1;
    if (x[8] == lado && x[9] == lado && x[10] == lado && x[11] == lado)
        return 1;
    if (x[12] == lado && x[13] == lado && x[14] == lado && x[15] == lado)
        return 1;
    //VERTICAL
    if (x[0] == lado && x[4] == lado && x[8] == lado && x[12] == lado)
        return 1;
    if (x[1] == lado && x[5] == lado && x[9] == lado && x[13] == lado)
        return 1;
    if (x[2] == lado && x[6] == lado && x[10] == lado && x[14] == lado)
        return 1;
    if (x[3] == lado && x[7] == lado && x[11] == lado && x[15] == lado)
        return 1;
    //DIAGONAL
    if (x[0] == lado && x[5] == lado && x[10] == lado && x[15] == lado)
        return 1;
    if (x[3] == lado && x[6] == lado && x[9] == lado && x[12] == lado)
        return 1;
    if (x[2] == lado && x[5] == lado && x[8] == lado)
        return 1;
    if (x[7] == lado && x[10] == lado && x[13] == lado)
        return 1;
    if (x[1] == lado && x[6] == lado && x[11] == lado)
        return 1;
    if (x[4] == lado && x[9] == lado && x[14] == lado)
        return 1;
    return 0;
}

int ganhou (const int x[], const int lado)
{
    if (combinacoes (x, lado))
        return 10;
    if (combinacoes (x, !lado))
        return -10;
    return 0; //caso de velha
}

int max (int *listaPontuacao, int contagem, int *listaDeMovimentos, int *melhorMovimento)
{
    if (!contagem)
        return 0;

    int max = +20;
    for (int i = 0; i < contagem; i++)
    {
        if (listaPontuacao[i] < max)
        {
            max = listaPontuacao[i];
            *melhorMovimento = listaDeMovimentos[i];
        }
    }
    return max;
}

int min (int* listaPontuacao, int contagem, int* listaDeMovimentos, int *melhorMovimento)
{
    if (!contagem)
        return 0;

    int min = -20;
    for (int i = 0; i < contagem; i++)
    {
        if (listaPontuacao[i] > min)
        {
            min = listaPontuacao[i];
            *melhorMovimento = listaDeMovimentos[i];
        }
    }
    return min;
}

int minMax (int x[], int lado,int *profundidade, int dificuldade)
{
    int listaDeMovimentos[N];
    int contagem = 0;
    int melhorMovimento;
    int listaPontuacao[N];
    int melhorPontuacao;

    melhorPontuacao = ganhou (x, COMPUTADOR);
    if (melhorPontuacao)
        return melhorPontuacao - *profundidade;

    for (int i = 0; i < dificuldade; i++)
    {
        if (x[i] == VAZIO)
            listaDeMovimentos [contagem++] = i;
    }
    --dificuldade;

    int move;

    for (int i = 0; i < contagem; i++)
    {
        move = listaDeMovimentos[i];
        fazerAJogada (x, move, lado);

        (*profundidade)++;
        listaPontuacao[i] = minMax (x, !lado, profundidade, dificuldade);
        (*profundidade)--;

        fazerAJogada (x, move, VAZIO);
    }

    if (lado == COMPUTADOR)
        melhorPontuacao = min (listaPontuacao, contagem, listaDeMovimentos, &melhorMovimento);

    if (lado == HUMANO)
        melhorPontuacao = max (listaPontuacao, contagem, listaDeMovimentos, &melhorMovimento);


    if (*profundidade != 0)
        return melhorPontuacao;
    else
        return melhorMovimento;
}

int jogadaMaquina (int *x, int lado)
{
    int dificuldade = 16;
    int profundidade = 0;
    int melhorMovimento = minMax (x, lado, &profundidade, dificuldade);
    system ("clear");
    printf ("A IA achou que o espaço nº %i é a melhor jogada!\n", melhorMovimento + 1);
    return melhorMovimento;
}

int jogadaHumano (int *x, int lado)
{
    int move;
    char inteiros[N];
    printf ("Agora é a sua vez terráquio!(SOMENTE NÚMEROS!!)\n");
    printf ("Onde desejas jogar? ");
    while (1)
    {
        scanf ("%i", &move);
        for (int i = 0; i <= N; i++)
        {
            if (inteiros[i] == move)
                break;
        }
        if (x[move - 1] == VAZIO && move <= N && move >= 0)
            break;
        else
        {
            printf ("Que pena esse espaço já está em uso!\n>> ");
            // while (1) {
            // }
            // printf ("Quer uma dica? (S/N) ");
            // char simOuNao = getchar ();
            // if (toupper(simOuNao) == 'S')
            // {
            //     system("clear");
            //     printf ("Calculando a jogada...\n");
            //     int dificuldade = 16;
            //     int profundidade = 0;
            //     int melhorMovimento = minMax (x, lado, &profundidade, dificuldade);
            //     system ("clear");
            //     printf ("A IA está recomendando o espaço nº%i", melhorMovimento + 1);
            //     break;
            // }
        }
    }
    return move - 1 ;
}

void inciarJogo ()
{
    printf ("Escolha o seu lado da força |X--O|\n>> ");
    while (1)
    {
        char escolha = getchar ();
        if (toupper (escolha) == 'X')
        {
            HUMANO = X;
            COMPUTADOR = O;
            break;
        }
        if (toupper (escolha) == 'O')
        {
            HUMANO = O;
            COMPUTADOR = X;
            break;
        }
        else
        {
            system("clear");
            printf ("Escolha o seu lado da força |X--O|\n>> ");
            printf ("Ocorreu um erro...");
            printf ("\nTente novamente\n>> ");
        }
    }

    int tabuleiro[N];
    int lado = 0;
    int fimDeJogo = 0;
    int move;
    valoresTabuleiro (tabuleiro);
    imprimirTabuleiro (tabuleiro);

    while (!fimDeJogo)
    {
        if (lado == HUMANO)
        {
            move = jogadaHumano (tabuleiro, lado);
            fazerAJogada (tabuleiro, move, lado);
            imprimirTabuleiro (tabuleiro);
        }
        else
        {
            printf ("Calculando a jogada...\n\n");
            move = jogadaMaquina (tabuleiro, lado);
            fazerAJogada (tabuleiro, move, lado);
            imprimirTabuleiro (tabuleiro);
        }
        if (ganhou (tabuleiro, lado))
        {
            printf ("Fim de Jogo\n");
            fimDeJogo =  1;
            if (lado == HUMANO)
                printf ("Você ganhou!\n");
            else
                printf ("A IA ganhou de você!\n");
        }
        if (tabuleiroCheio(tabuleiro))
        {
            printf ("Fim de Jogo\n");
            fimDeJogo = 1;
            printf ("Deu velha!\n");
        }
        lado = !lado;
    }

}

int main ()
{
    printf ("Regras: \n\n\n");
    printf ("- Para ganhar deve-se completar com o mesmo simbolo uma diagonal com\n mais ou igual a 3 espaços\n\n");
    printf ("- As colunas e linhas devem possuir 4 simbolos iguais para vencer\nBOA SORTE :)\n\n");
    printf ("\n\nPressione qualquer tecla para começar... ");
    getchar();
    system ("clear");
    char confirmacao = 'S';
    while (confirmacao == 'S')
    {
        inciarJogo ();
        printf ("Quer jogar de novo? (S/N) ");
        scanf ("%s", &confirmacao);
        confirmacao = toupper(confirmacao);
    }
    system("clear");
    printf ("MUITO OBRIGADO POR TESTAR O JOGO DA VELHA COM IA(MINMAX) :)\n");
    printf ("feito por André da Silva Freitas\n\n\n");
    printf ("GitHub @AndreAdmin\n\n======================================================\n");
    return 0;
}
