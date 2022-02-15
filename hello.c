#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // get name
    string name = get_string("Your name: \n");
    // say Hello, name!
    printf("Hello, %s!\n", name);
}