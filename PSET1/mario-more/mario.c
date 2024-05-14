#include <cs50.h>
#include <stdio.h>

void printBricks(int brickNumber)
{
    int aux=0;

    for(int i=1;i<=brickNumber;i++)
    {
        aux=brickNumber;
        for(int j=1;j<=i;j++)
        {
            while(i<aux)    
            {
                printf(" ");
                aux=aux-1;
            }

            printf("#");
        }
        printf("  ");
        for(int k=1;k<=i;k++)
        {
            printf("#");
        }
        printf("\n");
    }
}

int main(void)
{
    int nBricks;

    do
    {
        nBricks=get_int("Height: ");
    }
    while(nBricks>8 || nBricks<1);

    printBricks(nBricks);
}
