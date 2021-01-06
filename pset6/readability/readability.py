import re
# Promt the use for text.
text = input("Prompt your text: ")
# Count letters.
letters = len(re.findall(r'[a-zA-Z]', text))
# Count words.
words = len(text.split())
# Count Sentences.
sentences = len(re.findall(r'[.!?]', text))
# Calculate the index with the Coleman-Liau formula.
L = float(letters * 100.0) / words
S = float(sentences * 100.0) / words
index = round((0.0588 * L) - (0.296 * S) - 15.8)
# Print the grade.
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")