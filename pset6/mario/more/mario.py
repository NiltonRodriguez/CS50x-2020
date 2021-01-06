from cs50 import get_int


def main():
    x = get_number()
    # Draw the pyramid.
    draw(x)


def get_number():
    # Get the number between 1 to 8 from the user.
    while True:
        n = get_int("From 1 to 8, How height is your pyramid?\n")
        if n >= 1 and n <= 8:
            break
    return n
    
    
def draw(x):
    # Iteration to draw each row.
    for i in range(0, x, 1):
        # Iteration to draw the spaces to align to right.
        for j in range(1, x - i, 1):
            print(" ", end="")
        # Iteration to draw the hashes.    
        for j in range(0, i + 1, 1):
            print("#", end="")
        # Print the Gap.
        print("  ", end="")
        # Print the left oriented piramyd.
        for j in range(0, i + 1, 1):
            print("#", end="")
        # Print a new line.    
        print()      
    
    
main()