MOD = 10**9 + 7  # Set according to contest

MAXN = 2 * 10**5 + 5  # Choose based on constraints (safe for most CP problems)

# === Precomputed Factorials and Inverses ===
fact = [1] * MAXN  # fact[i] = i!
inv_fact = [1] * MAXN  # inv_fact[i] = (i!)^(-1) mod MOD


def precompute_factorials():
    """
    Precomputes factorials and inverse factorials up to MAXN.
    Enables O(1) nCr queries under modulo.
    """
    for i in range(1, MAXN):
        fact[i] = (fact[i - 1] * i) % MOD

    # Inverse of fact[MAXN-1] using Fermat's Little Theorem
    inv_fact[MAXN - 1] = pow(fact[MAXN - 1], MOD - 2, MOD)

    # Compute inverses backwards
    for i in range(MAXN - 2, 0, -1):
        inv_fact[i] = (inv_fact[i + 1] * (i + 1)) % MOD


# === Binomial Coefficient nCr mod MOD ===
def nCr(n, r):
    """
    Computes C(n, r) = n! / (r! * (n - r)!) mod MOD
    """
    if r < 0 or r > n:
        return 0
    return (fact[n] * inv_fact[r] % MOD * inv_fact[n - r]) % MOD


# === Pascal’s Triangle (Optional: For small n) ===
def generate_pascals_triangle(n):
    """
    Returns Pascal’s Triangle up to row `n`.
    Useful for debugging or educational purposes.
    """
    triangle = [[1]]
    for i in range(1, n + 1):
        row = [1]
        for j in range(1, i):
            row.append((triangle[i - 1][j - 1] + triangle[i - 1][j]) % MOD)
        row.append(1)
        triangle.append(row)
    return triangle


# === Multinomial Coefficients ===
def multinomial(total, parts):
    """
    Computes the multinomial coefficient:
    total! / (parts[0]! * parts[1]! * ... * parts[k]!) mod MOD
    Example: multinomial(7, [2, 2, 3]) for 7! / (2! * 2! * 3!)
    """
    if sum(parts) != total:
        return 0
    res = fact[total]
    for part in parts:
        res = (res * inv_fact[part]) % MOD
    return res


# === Stars and Bars Theorem ===
def stars_and_bars(n, k):
    """
    Counts the number of integer solutions to:
    x1 + x2 + ... + xk = n  where xi ≥ 0
    Formula: C(n + k - 1, k - 1)
    """
    return nCr(n + k - 1, k - 1)


# === SAMPLE DRIVER ===
if __name__ == "__main__":
    precompute_factorials()

    print(f"5C2 = {nCr(5, 2)}")  # Output: 10
    print(f"Multinomial(7, [2, 2, 3]) = {multinomial(7, [2, 2, 3])}")  # Output: 630
    print(f"Stars and Bars for (n=5, k=3): {stars_and_bars(5, 3)}")  # Output: 21

    pascal = generate_pascals_triangle(5)
    print("Pascal’s Triangle (modulo MOD):")
    for row in pascal:
        print(row)
