import numpy as np

happy = [1, 7, 10, 13, 19, 23, 28, 31, 32, 44, 49, 68, 70, 79, 82, 86, 91, 94, 97, 100, 103, 109, 129, 130, 133, 139, 167, 176, 188, 190, 192, 193, 203, 208, 219, 226, 230, 236, 239, 262, 263, 280, 291, 293, 301, 302, 310, 313, 319, 320, 326, 329, 331, 338, 356, 362, 365, 367, 368, 376, 379, 383, 386, 391, 392, 397, 404, 409, 440, 446, 464, 469, 478, 487, 490, 496, 536, 556, 563, 565, 566, 608, 617, 622, 623, 632, 635, 637, 638, 644, 649, 653, 655, 656, 665, 671, 673, 680, 683, 694, 700, 709, 716, 736, 739, 748, 761, 763, 784, 790, 793, 802, 806, 818, 820, 833, 836, 847, 860, 863, 874, 881, 888, 899, 901, 904, 907, 910, 912, 913, 921, 923, 931, 932, 937, 940, 946, 964, 970, 973, 989, 998, 1000, 1003, 1009, 1029, 1030, 1033, 1039, 1067, 1076, 1088, 1090, 1092, 1093, 1112, 1114, 1115, 1121, 1122, 1125, 1128, 1141, 1148, 1151, 1152, 1158, 1177, 1182, 1184, 1185, 1188, 1209, 1211, 1212, 1215]
happy = set(happy)
upper_digits = list()
lower_digits = list()

def compute_square_digit_sum(n: int) -> int:

    res = 0

    while n > 0:
        res += (n % 10)**2
        n //= 10

    return res

inp = input().split(' ')
a = int(inp[0])
b = int(inp[1])

bonus = False
if compute_square_digit_sum(b) in happy:
    bonus = True

if a == b:
    if compute_square_digit_sum(a) in happy:
        print(1)
    else:
        print(0)
    exit()

a -= 1

while True:
    if a > 0:
        lower_digits.append(a % 10)
        a //= 10
    else:
        break

while True:
    if b > 0:
        upper_digits.append(b % 10)
        b //= 10
    else:
        break

upper_digits = upper_digits[::-1]
lower_digits = lower_digits[::-1]

def countUpTo(exponents: int, limit: int, offset: int, final: bool) -> int:

    dp = np.zeros(1216, dtype=object)

    if final:
        dp[[i**2 + offset for i in range(1, limit+1)]] = 1
        dp[offset] = 1
    else:
        dp[[i**2 + offset for i in range(1, 10)]] = 1
        dp[offset] = 1

    for exponent in range(exponents - 1):
        memo = np.zeros(1216, dtype=object)

        if exponent == exponents - 2:
            for d in range(1, limit):
                for i in range(1215, -1, -1):
                    try:
                        memo[i + d**2] += dp[i]
                    except IndexError:
                        continue
        else:
            for d in range(1, 10):
                for i in range(1215, -1, -1):
                    try:
                        memo[i + d**2] += dp[i]
                    except IndexError:
                        continue

        dp = dp + memo

    count = 0
    for index in range(1216):
        if index in happy:
            count += dp[index]

    return count

total_count = 0
offset = 0
for index, digit in enumerate(upper_digits):
    
    if digit == 0:
        continue
    else:
        total_count += countUpTo(exponents=len(upper_digits)-index, limit=digit, offset=offset, final=index==len(upper_digits)-1)
        offset += digit**2

offset = 0
low_count = 0
for index, digit in enumerate(lower_digits):
    if digit == 0:
        continue
    else:
        low_count += countUpTo(exponents=len(lower_digits)-index, limit=digit, offset=offset, final=index==len(lower_digits)-1)
        offset += digit**2

if bonus:
    total_count += 1

print(total_count - low_count)