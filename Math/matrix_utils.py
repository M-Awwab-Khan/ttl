MOD = 10**9 + 7


# === Matrix Multiplication ===
def mat_mult(A, B, mod=MOD):
    """
    Multiplies two matrices A and B under mod.
    A: m x n, B: n x p → Returns m x p
    """
    m, n, p = len(A), len(B), len(B[0])
    result = [[0] * p for _ in range(m)]
    for i in range(m):
        for j in range(p):
            for k in range(n):
                result[i][j] = (result[i][j] + A[i][k] * B[k][j]) % mod
    return result


# === Matrix Exponentiation ===
def mat_pow(mat, power, mod=MOD):
    """
    Raises matrix `mat` to the power `power` under mod.
    Assumes mat is square.
    """
    size = len(mat)
    result = [[int(i == j) for j in range(size)] for i in range(size)]  # Identity
    while power:
        if power % 2:
            result = mat_mult(result, mat, mod)
        mat = mat_mult(mat, mat, mod)
        power //= 2
    return result


# === Example: nth Fibonacci number in O(log n) ===
def fibonacci(n):
    """
    Returns nth Fibonacci number, F(0)=0, F(1)=1.
    """
    if n == 0:
        return 0
    base = [[1, 1], [1, 0]]
    res = mat_pow(base, n - 1)
    return res[0][0]


# === SAMPLE DRIVER ===
if __name__ == "__main__":
    print("10th Fibonacci:", fibonacci(10))  # 55
