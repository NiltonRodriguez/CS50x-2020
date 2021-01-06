#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Make a variable that store the name of the user.
    string name = get_string("What is your name?\n");
    // Make the program say hello to the user.
    printf("hello, %s\n", name);
}