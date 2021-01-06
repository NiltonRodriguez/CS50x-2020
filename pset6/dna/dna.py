from sys import argv, exit
import csv
# Send an error message for the incorrect number of command-line arguments.
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)
# Open the CSV file and read it's contents into memory.
csvfile = open(argv[1], 'r')
# Convert the file contents into a dictionary.
reader = csv.DictReader(csvfile)
STRs = [STRs for STRs in reader.fieldnames[1:]]
# Open the DNA sequence and read its contents into memory.
dna = open(argv[2], 'r').read()
# Compute the longest run of consecutive repeats.
total_matches = {}
# Iteration to start checking for matches for each STR.
for STR in STRs:
    length = len(STR)
    match = 0
    longest_match = 0
    i = 0
    # Compare the current STR for matches in the DNA sequence.
    while i < len(dna):
        # Make block of characters of the length of the current STR.
        match_check = dna[i:i + length]
        # Compare each block with the STR.
        if match_check == STR:
            match += 1
            i += length
        else:
            match = 0
            i += 1
    # Store the longest match for each STR.
        longest_match = max(match, longest_match)
    total_matches[STR] = longest_match
# Check for matches between the STR counts and the people database.
for row in reader:
    if all(total_matches[STR] == int(row[STR]) for STR in total_matches):
        print(row['name'])
        exit(0)
else:
    print("No Match")
csvfile.close()
exit(0)