def derangement_dp(n):
    if n < 0:
        return 0
    D = [0] * (n + 1)
    if n >= 0:
        D[0] = 1
    if n >= 1:
        D[1] = 0
    if n >= 2:
        D[2] = 1

    for i in range(3, n + 1):
        D[i] = (i - 1) * (D[i - 1] + D[i - 2])

    return D[n]


# Example usage:
print(f"Number of derangements for n=4: {derangement_dp(4)}")
