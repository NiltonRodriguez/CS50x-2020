#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
    //Declare the coin values.
    int q = 25, d = 10, n = 5, p = 1, coins = 0;
    //Take user input for change.
    float change;
    do
    {
        change = get_float("How many change do I owe you?\n");
    }
    while (change <= 0);
    //Convert the change intro cents.
    int cents = round(change * 100);
    while (cents > 0)
    {
        if (cents - q >= 0)
        {
            cents -= q;
            coins ++;
        }
        else if (cents - d >= 0)
        {
            cents -= d;
            coins ++;
        }
        else if (cents - n >= 0)
        {
            cents -= n;
            coins ++;
        }
        else
        {
            cents -= p;
            coins ++;
        }
    }
    printf("%i\n", coins);
}