#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


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


int letter_score(char letter)
{
    // Points assigned to each letter of the alphabet
    int POINTS[] =
    {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10}
    ;

    // convert the letter to lowercase
    char lower_letter = (char) tolower(letter);

    // check if the letter is an alphabet letter versus a character
    if ('a' <= lower_letter && lower_letter <= 'z')
    {
        // change the letter to a number (where 0 is a and 25 is z)
        int let_idx = ((int) lower_letter) - 97;
        // return the points
        return POINTS[let_idx];
    }
    else
    {
        return 0;
    }
}


int compute_score(string word)
{
    int score = 0;
    for (int i = 0; i < length(word); i++)
    {
        score += letter_score(word[i]);
    }
    return score;
}


int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
    return 0;
}