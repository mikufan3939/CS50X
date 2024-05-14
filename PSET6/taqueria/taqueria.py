from sys import stdin

menu = {
    "Baja Taco": 4.25,
    "Burrito": 7.50,
    "Bowl": 8.50,
    "Nachos": 11.00,
    "Quesadilla": 8.50,
    "Super Burrito": 8.50,
    "Super Quesadilla": 9.50,
    "Taco": 3.00,
    "Tortilla Salad": 8.00
}
def main():
    total=0

    while True:
        while True:
            try:
                item=input("\nItem: ")
            except EOFError:
                return 0
            item=item.lower().title()
            if item in menu:
                total=total+menu[item]
                print(total, end="")

main()
