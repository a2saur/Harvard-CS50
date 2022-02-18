#include <cs50.h>
#include <stdio.h>
#include <math.h>

int coleman_liau(int letters, int words, int sentences)
{
    // index = 0.0588 * L - 0.296 * S - 15.8
    float for_conversion = 100 / ((float) words);
    float letters_per_100_words = letters * for_conversion;
    float sentences_per_100_words = sentences * for_conversion;
    float index = (0.0588 * letters_per_100_words) - (0.296 * sentences_per_100_words) - 15.8;
    return round(index);
}

int length(string str)
{
    int i = 0;
    // while the string isn't the end character
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

bool is_letter(char character)
{
    if ('A' <= character && character <= 'Z')
    {
        return true;
    }
    else if ('a' <= character && character <= 'z')
    {
        return true;
    }
    else
    {
        return false;
    }
}

int count_letters(string text)
{
    int count = 0;
    for (int i = 0; i < length(text); i++)
    {
        if (is_letter(text[i]))
        {
            count++;
        }
    }
    return count;
}

int count(string text, char seperator)
{
    int count = 0;
    for (int i = 0; i < length(text); i++)
    {
        if (text[i] == seperator)
        {
            count++;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    for (int i = 0; i < length(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }
    return count;
}

int main(void)
{
    // get text
    string text = get_string("Text: ");
    // count words (for future use) with  + 1 because it doesn't count the first word because there's no space

    int word_count = count(text, ' ') + 1;
    // count letters ( +  make that per 100 words)
    int letter_count = count_letters(text);
    // count sentences ( +  make that per 100 words)
    int sentence_count = count_sentences(text);
    // put into formula
    int index = coleman_liau(letter_count, word_count, sentence_count);
    // print grade level
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
    return 0;
}