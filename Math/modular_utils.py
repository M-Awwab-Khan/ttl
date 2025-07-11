# === MODULAR ARITHMETIC UTILITIES ===
MOD = 10**9 + 7  # Default modulus for CP (change if needed)


# --- Modular Addition ---
def mod_add(a, b, mod=MOD):
    return (a % mod + b % mod) % mod


# --- Modular Subtraction ---
def mod_sub(a, b, mod=MOD):
    return (a % mod - b % mod + mod) % mod


# --- Modular Multiplication ---
def mod_mul(a, b, mod=MOD):
    return (a % mod * b % mod) % mod


# --- Modular Exponentiation (a^b % mod) ---
def mod_pow(a, b, mod=MOD):
    result = 1
    a %= mod
    while b > 0:
        if b % 2:
            result = (result * a) % mod
        a = (a * a) % mod
        b //= 2
    return result


# --- Modular Inverse using Fermat's Little Theorem ---
def mod_inv_fermat(a, mod=MOD):
    # Requires mod to be prime
    return mod_pow(a, mod - 2, mod)


# --- Modular Inverse using Extended Euclidean Algorithm ---
def extended_gcd(a, b):
    if b == 0:
        return a, 1, 0
    g, x1, y1 = extended_gcd(b, a % b)
    x = y1
    y = x1 - (a // b) * y1
    return g, x, y


def mod_inv_euclid(a, mod=MOD):
    g, x, _ = extended_gcd(a, mod)
    if g != 1:
        raise ValueError(f"No modular inverse for {a} under mod {mod}")
    return x % mod


# --- Chinese Remainder Theorem ---
def chinese_remainder_theorem(remainders, moduli):
    """
    Solves system of congruences using CRT:
    x ≡ r1 (mod m1)
    x ≡ r2 (mod m2)
    ...
    Returns: (x mod M), where M = product of all moduli
    """
    assert len(remainders) == len(moduli)
    x = 0
    M = 1
    for m in moduli:
        M *= m

    for r_i, m_i in zip(remainders, moduli):
        M_i = M // m_i
        inv = mod_inv_euclid(M_i, m_i)
        x = (x + r_i * M_i * inv) % M

    return x


inv = [0] * MOD  # Precompute inverses for all numbers up to MOD
inv[1] = 1  # assume we already defined this array
for i in range(2, MOD):
    inv[i] = MOD - MOD / i * inv[MOD % i] % MOD

# === SAMPLE DRIVER ===
if __name__ == "__main__":
    a, b = 7, 5
    print(f"{a} + {b} mod {MOD} = {mod_add(a, b)}")
    print(f"{a} - {b} mod {MOD} = {mod_sub(a, b)}")
    print(f"{a} * {b} mod {MOD} = {mod_mul(a, b)}")
    print(f"{a}^{b} mod {MOD} = {mod_pow(a, b)}")
    print(f"Modular inverse of {a} using Fermat = {mod_inv_fermat(a)}")
    print(f"Modular inverse of {a} using Extended Euclid = {mod_inv_euclid(a)}")

    # Example for CRT:
    # x ≡ 2 mod 3
    # x ≡ 3 mod 5
    # x ≡ 2 mod 7
    rem = [2, 3, 2]
    mod = [3, 5, 7]
    print(f"Solution to system using CRT = {chinese_remainder_theorem(rem, mod)}")
