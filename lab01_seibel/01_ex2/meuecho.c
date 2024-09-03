/* Pedro de Almeida Barizon 2211350 */

/* DEPENDENCIAS EXTERNAS */
#include <stdio.h>

int main(int argc, char** argv)
{
    for (int i = 1; i < argc - 1; i++)
        printf("%s ", argv[i]);
    /* 
        Nao coloca espaco depois do elemento final, que so existira se argc > 1,
        ja que o nome do programa (argv[0]) nao deve ser exibido.
    */ 
    if (argc > 1)
        printf("%s", argv[argc - 1]);
    
    printf("\n");

    return 0;
}
