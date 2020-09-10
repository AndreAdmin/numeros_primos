#include <stdio.h>
int main ()
{
    int valor, j =1, c = 0;
    printf ("Até onde desejas calcular? ");
    scanf ("%i", &valor);
    for (int i = 2; i <= valor; ++i){
        while (j <= i && c <= 2){
            if (i % j == 0){
                ++c;
            }
            ++j;
        }
        if (c == 2){
            printf ("%i \n", i);
        }
        c = 0;
        j = 1;
    }
    return 0;
}
