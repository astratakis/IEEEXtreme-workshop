t = int(input())

for _ in range(t):

    n = int(input())

    words = input().strip().split(' ')

    cipher = False

    if "the" in words:
        cipher = True

    text = str()
    for index, w in enumerate(words):
        if index < len(words)-1:
            text += (w + " ")
        else:
            text += w

    for i in range(len(text)):
        if text[i] == ' ':
            print(" ", end="")
            continue
        else:
            if cipher:
                val = ord(text[i]) - n
                if val < 97:
                    val += 26
                print(chr(val), end="")
            else:
                val = ord(text[i]) + n
                if val > 122:
                    val -= 26
                print(chr(val), end="")

    print()