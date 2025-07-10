from math import gcd, combinations
from functools import reduce


def lcm(a, b):
    return a * b // gcd(a, b)


def count_divisible(n, divisors):
    """
    Counts how many numbers in [1, n] are divisible by at least one number in `divisors`
    """
    total = 0
    k = len(divisors)
    for r in range(1, k + 1):
        for combo in combinations(divisors, r):
            l = reduce(lcm, combo)
            if l == 0:
                continue
            cnt = n // l
            total += (-1) ** (r + 1) * cnt
    return total


# === SAMPLE DRIVER ===
if __name__ == "__main__":
    N = 100
    divs = [2, 3, 5]
    print("Count in [1, 100] divisible by 2, 3, or 5:", count_divisible(N, divs))  # 74
