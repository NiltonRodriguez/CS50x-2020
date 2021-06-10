from sys import argv, exit
from cs50 import SQL
# Open de database with SQLite
db = SQL("sqlite:///students.db")
# Send an error message for the incorrect number of command-line arguments.
if len(argv) != 2:
    print("Usage: python roster.py House")
    exit(1)
# Query database for all students in house.
students = db.execute("SELECT * FROM students WHERE house = ?", argv[1])
# Sort by last name.
students.sort(key=lambda x: x.get("last"))
# Print out each student full name and birth year.
for student in students:
    if student["middle"] == None:
        print("{} {}, born {}".format(student["first"], student["last"], student["birth"]))
    else:
        print("{} {} {}, born {}".format(student["first"], student["middle"], student["last"], student["birth"]))
