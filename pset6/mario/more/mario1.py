from cs50 import get_int

# Get the number between 1 to 8 from the user.
while True:
        n = get_int("From 1 to 8, How height is your pyramid?\n")
        if 1 <= n <= 8:
            break

# Draw the Pyramid
for i in range(1, n + 1):
    print(" " * (n - i) + "#" * i + "  " + "#" * i)