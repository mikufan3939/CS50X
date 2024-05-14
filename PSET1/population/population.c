#include <cs50.h>
#include <stdio.h>

int calculatePopulation(int sP, int eP)
{
    int currentPopulation, numberYears=0;

    if(sP==eP)
    {
        return 0;
    }

    currentPopulation=sP;

    do
    {
        numberYears=numberYears+1;
        currentPopulation=currentPopulation+(currentPopulation/3)-(currentPopulation/4);
    }
    while(currentPopulation<eP);

    return numberYears;
}

int main(void)
{
    int startingPopulation, endingPopulation;

    do
    {
        startingPopulation=get_int("Type the starting population: ");
    }
    while(startingPopulation<9);

    do
    {
    endingPopulation=get_int("Type the ending population: ");
    }
    while(endingPopulation<startingPopulation);

    printf("Years: %d.", calculatePopulation(startingPopulation, endingPopulation));
}
