def prime_factors(n):  # sqrt of n
    factors = []

    # Check for 2 first to make further loop faster
    while n % 2 == 0:
        factors.append(2)
        n //= 2

    # Check for odd factors from 3 up to sqrt(n)
    i = 3
    while i * i <= n:
        while n % i == 0:
            factors.append(i)
            n //= i
        i += 2

    # If n is still > 2, it's a prime factor
    if n > 1:
        factors.append(n)

    return factors


# Example:
print(prime_factors(100))  # Output: [2, 2, 5, 5]

# OPTIMIZATION: USING SPF
MAXN = 10**6 + 1
spf = [0] * MAXN  # spf[i] = smallest prime factor of i


def compute_spf():
    for i in range(2, MAXN):
        spf[i] = i  # Initialize with itself

    for i in range(2, int(MAXN**0.5) + 1):  # from 2 to sqrt(MAXN)
        if spf[i] == i:  # i is prime
            for j in range(i * i, MAXN, i):
                if spf[j] == j:  # Mark spf only if it's not already marked
                    spf[j] = i


def get_prime_factors(n):
    factors = []
    while n > 1:
        factors.append(spf[n])
        n //= spf[n]
    return factors


# Example usage:
compute_spf()
print(get_prime_factors(100))  # Output: [2, 2, 5, 5]

# 💡 Time Complexity:
# compute_spf(): O(n log log n) (like regular Sieve of Eratosthenes)

# get_prime_factors(n): O(log n) per number
