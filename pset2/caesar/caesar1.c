#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool check_key(string s);

int main(int argc, string argv[])
{
    //Check if there are 2 command-line arguments.
    //Check for all chars to be digits.
    string s = argv[1];
    if (argc != 2 || check_key(s) == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //Convert the string into an integer.
    int key = atoi(s);
    //Prompt the user for planetext (The unencrypted text).
    string pltxt = get_string("planetext: ");
    printf("ciphertext: ");
    int n = strlen(pltxt);
    //Encypher the text using the key prompted while running the program.
    for (int i = 0; i < n; i++)
    {
        char c = pltxt[i];
        //Check is if is a letter.
        if (isalpha(c))
        {
            //Check if is uppercase.
            //Encypher.
            if (isupper(c))
            {
                int ci = ((c - 'A' - key) % 26) + 'A';
                printf("%c", ci);
            }
            //Check if is lowercase.
            //Encrypt.
            if (islower(c))
            {
                int cj = ((c - 'a' - key) % 26) + 'a';
                printf("%c", cj);
            }
        }
        //If isn't an alphabetical character, add to the cyphertext without modifications.
        else
        {
            printf("%c", c);
        }
    }
    printf("\n");
    return 0;
}
//Function to check each char as digit.
bool check_key(string s)
{
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        char dg = s[i];
        if (!isdigit(dg))
        {
            return false;
        }
    }
    return true;
}
