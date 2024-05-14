// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

string replace(string leetspeak)
{
    for(int i=0;i<strlen(leetspeak);i++)
    {
        switch(leetspeak[i])
        {
            case 'a':
            leetspeak[i]='6';
            break;

            case 'e':
            leetspeak[i]='3';
            break;

            case 'i':
            leetspeak[i]='1';
            break;

            case 'o':
            leetspeak[i]='0';
            break;
        }
    }
    return leetspeak;
}

int main(int argc, string argv[])
{
    string originalString;

    if(argc<=1)
    {
        printf("Usage: ./no-vowel word\n");
        return 1;
    }

    printf("%s\n", replace(argv[1]));
}
