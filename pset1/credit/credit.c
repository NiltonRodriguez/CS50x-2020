#include <cs50.h>
#include <stdio.h>

int main(void)
{
//Take users input.
    long card, goodcard;
    int checksum = 0, odd = 0;
    do
    {
        card = get_long("What is your credit card number?\n");
        goodcard = card;
    }
    while (card <= 0);
//Calculate the checksum.
    while (card > 0)
    {
//Add the last number to the checksum (if even multiply for 2).
//If the result of the multiplication is 2 digits, split and add each to checksum.
//To get the second digit, use "% 10". To get the first digit use "/ 10"
        if (odd % 2 != 0)
        {
            int mult = 2 * (card % 10);
            if (mult > 9)
            {
                checksum += (mult % 10 + mult / 10);
            } 
//If the result of the multiplication is 1 digit, add to checksum.
            else
            {
                checksum += mult;
            }
        }
//Add the last number to checksum (if odd).
//To take the last number of the credit card, % by 10.
        else
        {
            checksum += card % 10; 
        }
//Change to the new last number.
//To change the last digit by 1, divide the credit card number in 10.
        card = card / 10;
        odd ++;
    }
    long amexval = goodcard / 10000000000000;
    long masterval = goodcard / 100000000000000;
    long visaval = goodcard / 1000000000000;
    if (checksum % 10 == 0)
//Check for Amex to be a valid card.
//Amex total digits = 15
//Amex first numbers 34 || 37
    {
        if ((amexval == 34 || amexval == 37) && odd == 15)
        {
            printf("AMEX\n");
        }
//Check for MasterCard to be a valid car.
//Master card total digits = 16
//Master card first digits = 51, 52, 53, 54, 55
        else if ((masterval >= 51 && masterval <= 55) && odd == 16)
        {
            printf("MASTERCARD\n");
        }
//Check for Visa to be a valid card.
//Visa total digits = 13 || 16
//Visa first number = 4
        else if ((odd == 16 || odd == 13) && (visaval == 4 || masterval / 10 == 4))
        {
            printf("VISA\n");
        }
//If non of the parameters are true, validate as invalid.
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