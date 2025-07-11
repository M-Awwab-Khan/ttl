# Euler Totient Function
# https://en.wikipedia.org/wiki/Euler's_totient_function

# What is Euler's Totient Function?
# The Euler's Totient Function, denoted as φ(n), counts the positive integers upto a given integer n that are relatively prime to n.
# In other words, it counts the integers k in the range 1 to n such that gcd(n, k) = 1.
# The function is defined as:
# φ(n) = n * (1 - 1/p1) * (1 - 1/p2) * ... * (1 - 1/pk)
# where p1, p2, ..., pk are the distinct prime factors of n.
# The value of φ(1) is defined to be 1.
# The function is multiplicative, meaning that if gcd(a, b) = 1,
# then φ(a * b) = φ(a) * φ(b).


def etf(n):
    """Calculate the Euler's Totient Function for a given integer n."""
    if n < 1:
        raise ValueError("n must be a positive integer")

    result = n
    p = 2

    while p * p <= n:
        if n % p == 0:
            while n % p == 0:
                n //= p
            result -= result // p
        p += 1

    if n > 1:  # If n is a prime number greater than 1
        result -= result // n

    return result


# for numbers upto MAXN
def etf_upto(maxn):
    """Calculate Euler's Totient Function for all integers up to maxn."""
    if maxn < 1:
        raise ValueError("maxn must be a positive integer")

    phi = list(range(maxn + 1))
    for p in range(2, maxn + 1):
        if phi[p] == p:  # p is a prime
            for k in range(p, maxn + 1, p):
                phi[k] -= phi[k] // p

    return phi


# Example usage:
if __name__ == "__main__":
    print(etf(9))  # Output: 6
    print(etf_upto(10))  # Output: [0, 1, 1, 2, 2, 4, 2, 6, 4, 6, 4]
