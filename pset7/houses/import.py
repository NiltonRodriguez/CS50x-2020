from sys import argv, exit
from cs50 import SQL
import csv
# Open de database with SQLite
db = SQL("sqlite:///students.db")
# Check command-line arguments.
# Send an error message for the incorrect number of command-line arguments.
if len(argv) != 2:
    print("Usage: python import.py data.csv")
    exit(1)
# Open csv file.
with open(argv[1], "r") as csvfile:
    # Create a DictReader.
    reader = csv.DictReader(csvfile)
    # For each row, parse name.
    for row in reader:
        fullname = row["name"].split()
        # Check for middle name.
        if len(fullname) == 2:
            first = fullname[0]
            middle = None
            last = fullname[1]
        else:
            first = fullname[0]
            middle = fullname[1]
            last = fullname[2]
        house = row["house"]
        birth = int(row["birth"])
        # Insert each student into de table of the database.
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)", first, middle, last, house, birth)
exit(0)