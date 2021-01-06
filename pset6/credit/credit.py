import re
# Take users input.
card = input("What is your credit card number? ")
# Calculate the Checksum.
# Reverse the number to start calculating the checksum.
reverse_card = card[::-1]
# Add every other digit starting from the last number.
last_every = sum([int(i) for i in reverse_card[0::2]])
# Multiply every other digit by 2 starting from the secont-to-last digit.
# If the product is a 2 digit number, split the number.
# Add de product's digit together.
second_every = sum([((int(i) * 2) // 10) + ((int(i) * 2) % 10) for i in reverse_card[1::2]])
# Check for valid card.
if (last_every + second_every) % 10 == 0:
    # Check for Amex to be a valid card.
    # Amex total digits = 15 // first numbers 34 || 37
    if len(card) == 15 and re.search("^34|^37", card):
        print("AMEX")
    # Check for MasterCard to be a valid car.
    # Master card total digits = 16 // first digits = 51, 52, 53, 54, 55
    elif len(card) == 16 and re.search("^51|^52|^53|^54|^55", card):
        print("MASTERCARD")    
    # Check for Visa to be a valid card.
    # Visa total digits = 13 || 16 // first number = 4
    elif len(card) in [13, 16] and re.search("^4", card):
        print("VISA")
else:
    print("INVALID")