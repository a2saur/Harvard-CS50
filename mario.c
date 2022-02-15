#include <cs50.h>
#include <stdio.h>

void pyramid(int height)
{
    // go through each row
    for (int i = 1; i <= height; i++)
    {
        // add spaces (# of spaces = height-row = rows left)
        for (int spaces = 0; spaces < height - i; spaces++)
        {
            printf(" ");
        }
        // add blocks (# of blocks = row)
        for (int blocks = 0; blocks < i; blocks++)
        {
            printf("#");
        }

        // add gap
        printf("  ");

        // reverse
        // add blocks (# of blocks = row)
        for (int blocks = 0; blocks < i; blocks++)
        {
            printf("#");
        }

        // add new line
        printf("\n");
    }
}

int main(void)
{
    int height;
    do
    {
        height = get_int("Pyramid Height: ");
    }
    while (height < 1 || height > 8);

    pyramid(height);
}