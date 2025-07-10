from math import isqrt

MOD = 10**9 + 7


# === Arithmetic Progression (AP) ===
def sum_ap(a, d, n):
    """
    Returns sum of AP: a, a+d, a+2d, ..., a+(n-1)d
    Formula: n/2 * [2a + (n-1)d]
    """
    return n * (2 * a + (n - 1) * d) // 2


def sum_ap_mod(a, d, n, mod=MOD):
    """
    Returns sum of AP under modulo
    """
    total = n % mod
    first = (2 * a % mod + ((n - 1) * d) % mod) % mod
    return (total * first * pow(2, mod - 2, mod)) % mod


# === Geometric Progression (GP) ===
def sum_gp(a, r, n):
    """
    Returns sum of GP: a + ar + ar^2 + ... + ar^{n-1}
    If r == 1 → sum = a * n
    """
    if r == 1:
        return a * n
    return a * (r**n - 1) // (r - 1)


def sum_gp_mod(a, r, n, mod=MOD):
    """
    Returns sum of GP under modulo.
    Assumes mod is prime and r != 1
    """
    if r == 1:
        return a * n % mod
    numerator = (pow(r, n, mod) - 1 + mod) % mod
    denominator = (r - 1) % mod
    inv = pow(denominator, mod - 2, mod)
    return (a * numerator % mod) * inv % mod


# === Linear Equation Solver ===
def solve_linear(a, b):
    """
    Solves ax + b = 0 → x = -b / a
    Returns float or None if no solution
    """
    if a == 0:
        return None if b != 0 else "Infinite solutions"
    return -b / a


# === Quadratic Equation Solver ===
def solve_quadratic(a, b, c):
    """
    Solves ax^2 + bx + c = 0
    Returns real roots as a tuple or None if complex
    """
    discriminant = b**2 - 4 * a * c
    if discriminant < 0:
        return None  # Complex roots
    sqrt_d = isqrt(discriminant)
    if sqrt_d * sqrt_d != discriminant:
        return None  # Not perfect square
    x1 = (-b + sqrt_d) // (2 * a)
    x2 = (-b - sqrt_d) // (2 * a)
    return x1, x2 if x1 != x2 else (x1,)


# === Vieta’s Formulas ===
def vieta_from_roots(x1, x2):
    """
    Given roots x1, x2 of a quadratic: x^2 - (x1+x2)x + x1*x2 = 0
    Returns coefficients (a=1, b, c)
    """
    b = -(x1 + x2)
    c = x1 * x2
    return 1, b, c


def vieta_from_coeffs(a, b, c):
    """
    Given coefficients a, b, c of ax^2 + bx + c,
    Returns (sum of roots, product of roots)
    """
    return (-b / a, c / a)


# === SAMPLE DRIVER ===
if __name__ == "__main__":
    print("AP sum (a=2, d=3, n=5):", sum_ap(2, 3, 5))  # 2+5+8+11+14 = 40
    print("AP sum mod:", sum_ap_mod(2, 3, 5))

    print("GP sum (a=2, r=3, n=4):", sum_gp(2, 3, 4))  # 2 + 6 + 18 + 54 = 80
    print("GP sum mod:", sum_gp_mod(2, 3, 4))

    print("Solving ax + b = 0 for a=3, b=6:", solve_linear(3, 6))  # x = -2.0

    print("Quadratic roots for x^2 - 5x + 6 = 0:", solve_quadratic(1, -5, 6))  # (2, 3)

    print("Vieta from roots 2, 3:", vieta_from_roots(2, 3))  # x^2 - 5x + 6
    print(
        "Vieta from coefficients (1, -5, 6):", vieta_from_coeffs(1, -5, 6)
    )  # sum = 5, prod = 6
