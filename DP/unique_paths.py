def unique_paths(m, n):
    # dp[i][j] will be the number of ways to reach cell (i, j)
    dp = [[0 for _ in range(n)] for _ in range(m)]

    # There's only one way to reach any cell in the first row (from the left)
    for j in range(n):
        dp[0][j] = 1

    # There's only one way to reach any cell in the first col (from the top)
    for i in range(m):
        dp[i][0] = 1

    for i in range(1, m):
        for j in range(1, n):
            # Ways to reach (i,j) is sum of ways to reach cell above and cell to the left
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1]

    return dp[m - 1][n - 1]


m, n = 3, 7
print(f"Number of unique paths in a {m}x{n} grid: {unique_paths(m, n)}")
