#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long ccNumber, div = 1;
    int aux = 0, digit = 0, sum1 = 0, sum2 = 0, firstDigit, sumcheck;
    bool valid;

    ccNumber = get_long("Type your credit card number: ");

    do
    {
        digit = (ccNumber / div) % 10;

        if (aux % 2 == 0)
        {
            sum1 = sum1 + digit;
        }
        if (aux % 2 != 0)
        {
            if (digit * 2 >= 10)
            {
                sum2 = sum2 + (((digit * 2) / 10) % 10) + ((digit * 2) % 10);
            }
            else
            {
                sum2 = sum2 + (digit * 2);
            }
        }

        if (ccNumber / div < 100 && ccNumber / div >= 10)
        {
            firstDigit = (ccNumber / div);
        }

        div = div * 10;
        aux = aux + 1;
    }
    while (ccNumber / div > 1);

    sumcheck = sum1 + sum2;

    if (sumcheck % 10 == 0)
    {
        valid = true;
    }
    else
    {
        valid = false;
    }

    if ((firstDigit > 50 && firstDigit < 56) && valid == true && aux == 16)
    {
        printf("MASTERCARD\n");
    }
    else if ((firstDigit > 39 && firstDigit < 50) && valid == true && (aux == 13 || aux == 16))
    {
        printf("VISA\n");
    }
    else if ((firstDigit == 34 || firstDigit == 37) && valid == true && aux == 15)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
