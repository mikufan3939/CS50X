#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text)
{
    int numLetters = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            numLetters = numLetters + 1;
        }
    }

    return numLetters;
}

int count_words(string text)
{
    int numWords = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]) && i == 0)
        {
            numWords = numWords + 1;
        }
        else if (isalpha(text[i + 1]) && text[i] == ' ')
        {
            numWords = numWords + 1;
        }
        else if (isalpha(text[i + 2]) && text[i] == ' ' && text[i + 1] == '"')
        {
            numWords = numWords + 1;
        }
    }

    return numWords;
}

int count_sentences(string text)
{
    int numSentences = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            numSentences = numSentences + 1;
        }
    }

    return numSentences;
}

int main(void)
{
    string text;
    float L, S;
    double index;

    text = get_string("Please type your text: ");

    L = (count_letters(text) * 1.0 / count_words(text)) * 100.0;
    S = (count_sentences(text) * 1.0 / count_words(text)) * 100.0;

    index = 0.0588 * L - 0.296 * S - 15.8;
    index = round(index);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", index);
    }
}
