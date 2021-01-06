#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(void)
{
    //Prompt user for text.
    string text = get_string("Prompt your text: \n");
    //Calculate the parameters of the index.
    int letters = 0, words = 0, sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char l = text[i];
        //Count letters.
        if (isalpha(l))
        {
            letters++;
        }
        //Count words.
        if (isspace(l))
        {
            words++;
        }
        //Count sentences.
        if ((l == '!') || (l == '.') || (l == '?'))
        {
            sentences++;
        }
    }
    //add the last word of the text.
    words += 1;
    //Calculate index.
    //To ensure the division is a floating point, add to the constant ".0f": 100.0f
    float L = (letters * 100.0f) / words, S = (sentences * 100.0f) / words;
    int index = round((0.0588 * L) - (0.296 * S) - 15.8);
    //Print grade. Before grade 1, between grade 1 and 15, 16+
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}