# Sieve of Eratosthenes
# This function generates a list of prime numbers up to a given limit using the Sieve of Eratosthenes algorithm.


def sieve_of_eratosthenes(limit):
    """Returns a list of prime numbers up to the specified limit."""
    if limit < 2:
        return []

    # Initialize a boolean array of True values
    is_prime = [True] * (limit + 1)
    is_prime[0] = is_prime[1] = False  # 0 and 1 are not prime numbers

    for number in range(2, int(limit**0.5) + 1):
        if is_prime[number]:
            # Mark all multiples of the prime number as False
            for multiple in range(number * number, limit + 1, number):
                is_prime[multiple] = False

    # Collecting all prime numbers
    primes = [num for num, prime in enumerate(is_prime) if prime]
    return primes


# Example usage:
if __name__ == "__main__":
    limit = 100
    primes = sieve_of_eratosthenes(limit)
    print(f"Prime numbers up to {limit}: {primes}")
