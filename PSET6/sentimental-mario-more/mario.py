from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height > 0 and height < 9:
        break
aux = 0
for i in range(height):
    aux = aux+1
    print(" " * ((height-i)-1), end="")
    print("#" * aux, end="")
    print("  ", end="")
    print("#" * aux)
