# Python script to prove concept of using modulo 4 and mod 13 to make each card unique


def print_card(i):
    match i%4:
        case 0:
            cs = "hearts"
        case 1:
            cs = "clubs"
        case 2:
            cs = "diamonds"
        case 3:
            cs = "spades"
    cn = i%13
    print("This card is a: ", cn, " of ", cs)
#52 cards
#4 suits of 13
suits = list()
for i in range(4):
    suits.append(0)

cards = list()
for i in range(13):
    cards.append(0)

for i in range(52):
    suits[i%4] += 1
    cards[i%13] += 1
    print_card(i)

print(suits)
print(cards)
