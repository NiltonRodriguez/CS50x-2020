from cs50 import get_float

# Declare the coins variable.
coins = 0
# Take the user input
# convert the change into cents.
while True:
    cents = round(get_float("How many change do I owe you? ") * 100)
    if cents >= 0:
        break
# Apply the greedy algorithm.
for i in [25, 10, 5, 1]:
    # Divide the cents with the coin value to know the total coins.
    coins += cents // i
    # Use Modulo to know the remainder cents.
    cents %= i

print(coins)