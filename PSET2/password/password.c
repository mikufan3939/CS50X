// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool uCase=false, lCase=false, number=false, symbol=false;

    for(int i=0;i<strlen(password);i++)
    {
        if(isupper(password[i]))
        {
            uCase=true;
        }
        if(islower(password[i]))
        {
            lCase=true;
        }
        if(isdigit(password[i]))
        {
            number=true;
        }
        if(ispunct(password[i]))
        {
            symbol=true;
        }
    }

    if(uCase && lCase && number && symbol)
    {
        return true;
    }

    return false;
}
