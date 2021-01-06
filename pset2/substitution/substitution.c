#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

bool check_key(string s);
bool check_char(string s);
const int N = 26;

int main(int argc, string argv[])
{
    //Check Valid key.
    //Check for a single command-line argument.
    string s = argv[1];
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    //Check for 26 characters.
    else if (strlen(s) != N)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    //Check for aphabetic characters.
    else if (check_key(s) == false)
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }
    //Check for each letter exactly once.
    else if (check_char(s) == false)
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }
    //Prompt the user for plane text (the unencripted text).
    string pltxt = get_string("planetext: ");
    //Encrypt the text using the user key.
    string cytxt = pltxt;
    for (int i = 0, b = strlen(pltxt); i < b ; i++)
    {
        //Check for letter.
        if (isalpha(pltxt[i]))
        {
            //Check if its upperlower.
            if (isupper(pltxt[i]))
            {
                //Replace the uppercase letter from the planetext with the uppercase letter from the key.
                cytxt[i] = toupper(s[pltxt[i] - 'A']);
            }
            //Check if its lowercase.
            if (islower(pltxt[i]))
            {
                //Replace the lowercase letter from the planetext with the lowercase letter from the key.
                cytxt[i] = tolower(s[pltxt[i] - 'a']);
            }
        }
        else
        {
            //If isn't and aphabetical character, add it to the ciphertext without modificacion.
            cytxt[i] = pltxt[i];
        }
    }
    //Print the encrypted text.
    printf("ciphertext: %s\n", cytxt);
    return 0;
}
//Function to check for alpahetich caracters.
bool check_key(string s)
{
    for (int i = 0; i < N; i++)
    {
        char ch = s[i];
        if (!isalpha(ch))
        {
            return false;
        }
    }
    return true;
}
//Function to check if there is a repeated character.
bool check_char(string s)
{
    char alpha[N];
    bool rep[N];
    for (int i = 0; i < N; i++)
    {
        rep[i] = false;
    }
    for (int i = 0; i < N; i++)
    {
        //Check for uppercase repetition.
        if (isupper(s[i]))
        {
            //Check for repetition.
            //If repeated, send error.
            if (rep[s[i] - 'A'] == true)
            {
                return false;
            }
            //If not repeated, continue.
            else
            {
                rep[s[i] - 'A'] = true;
                alpha[i] = s[i] - 'A';
            }
        }
        //Check for lowercase repetition.
        else
        {
            //Check for repetition.
            //If repeated, send error.
            if (rep[s[i] - 'a'] == true)
            {
                return false;
            }
            //If not repeated, continue.
            else
            {
                rep[s[i] - 'a'] = true;
                alpha[i] = s[i] - 'a';
            }
        }
    }
    return true;
}