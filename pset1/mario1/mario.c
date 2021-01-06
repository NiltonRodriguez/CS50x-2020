#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Get the number between 1 to 8 from the user.
    int x;
    do
    {
        x = get_int("From 1 to 8, How height is your pyramid?\n");
    }
    while (x < 1 || x > 8);
    //Print the pyramid.
    for (int i = 1; i <= x; i++)
    {
        //Print space.
        for (int j = 1; j <= (x - i); j++)
        {
            printf(" ");
        }
        //Print hasesh.
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        //Print a new line.
        printf("\n");
    }
}