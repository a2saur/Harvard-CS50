#include <cs50.h>
#include <stdio.h>
#include <math.h>

int get_digit(long number, int digit)
{
    // gets the digit at place [digit] with 1 being on the right
    long only_right_side = number % (long) pow(10, digit);
    int target_digit = only_right_side  /  pow(10, (digit - 1));
    return target_digit;
}


int len(long number)
{
    // returns the length of a number
    int count = 0;
    do
    {
        number = number / 10;
        count++;
    }
    while (number != 0);
    return count;
}



bool valid_card(long credit_num)
{
    // checks whether or not the card is valid
    int length = len(credit_num);
    int answer = 0;
    int to_add;
    for (int i = 2; i <= length; i += 2)
    {
        to_add = get_digit(credit_num, i) * 2;
        for (int j = 1; j <= len(to_add); j++)
        {
            answer += get_digit(to_add, j);
        }
    }

    for (int i = 1; i <= length; i += 2)
    {
        answer += get_digit(credit_num, i);
    }

    if (get_digit(answer, 1) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}



void card_type(long credit_num)
{
    // checks which type of card it is
    // assumes that the credit card number is valid
    int length = len(credit_num);
    if (length == 15)
    {
        // could be AMEX
        if (get_digit(credit_num, 15) == 3)
        {
            if (get_digit(credit_num, 14) == 4 || get_digit(credit_num, 14) == 7)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (length == 16)
    {
        // could be MASTERCARD or VISA
        if (get_digit(credit_num, 16) == 5)
        {
            if (get_digit(credit_num, 15) >= 1 && get_digit(credit_num, 15) <= 5)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (get_digit(credit_num, 16) == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (length == 13)
    {
        // could be VISA
        if (get_digit(credit_num, 13) == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}


int main(void)
{
    long credit_num = get_long("Credit Card Number: ");
    if (valid_card(credit_num))
    {
        card_type(credit_num);
    }
    else
    {
        printf("INVALID\n");
    }
}