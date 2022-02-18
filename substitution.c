#include <ctype.h>
#include <cs50.h>
#include <stdio.h>


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

int format_letter(char letter, char letter_format)
{
    if (isupper(letter_format) != 0)
    {
        return toupper(letter);
    }
    else
    {
        return tolower(letter);
    }
}

int main(int argc, string argv[])
{
    // initialize an array to count the number of times a letter appears
    int counts[26];
    for (int i = 0; i < 26; i++)
    {
        counts[i] = 0;
    }

    // check if the key is there and if it's 26 characters
    if (argc != 2)
    {
        printf("Usage: . / substitution key\n");
        return 1;
    }
    else if (length(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.");
        return 1;
    }
    else
    {
        // it worked! create substitution key
        string key = argv[1];
        for (int i = 0; i < length(key); i++)
        {
            key[i] = tolower(key[i]);
            if (key[i] > 'z' || key[i] < 'a')
            {
                printf("Key must contain 26 characters.");
                return 1;
            }
            else
            {
                counts[key[i] - 97]++;
                if (counts[key[i] - 97] >= 2)
                {
                    // duplicate character
                    printf("Key must contain 26 characters.");
                    return 1;
                }
            }
        }
        // get plaintext
        string plaintext = get_string("Plaintext: ");
        // convert to ciphertext
        char ciphertext[length(plaintext)];
        printf("length: %i\n", length(plaintext));
        int char_idx;
        for (int i = 0; i < length(plaintext); i++)
        {
            char_idx = tolower(plaintext[i]) - 97;
            if (char_idx >= 0 && char_idx < 26)
            {
                // its a letter
                // the ciphertext letter = plaintext letter translated and formatted
                ciphertext[i] = format_letter(key[char_idx], plaintext[i]);
            }
            else
            {
                ciphertext[i] = plaintext[i];
            }
        }
        ciphertext[length(plaintext)] = '\0';
        printf("ciphertext: %s\n", ciphertext);
    }
    return 0;
}