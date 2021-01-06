#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Get the number between 1 to 8 from the user.
    int x;
    do
    {
        x = get_int("From 1 to 8, how height is your pyramid?\n");
    }
    while (x < 1 || x > 8);
    //Print the pyramid.
    for (int i = 1; i <= x; i++)
    {
        //Print space to align to right.
        for (int j = 1; j <= (x - i); j++)
        {
            printf(" ");
        }
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        //Print the gap.
        printf("  ");
        //Print the left oriented pyramid.
        for (int j = 1; j <= i; j++)
        {
            printf("#");
        }
        //Print the new line.
        printf("\n");
    }
}