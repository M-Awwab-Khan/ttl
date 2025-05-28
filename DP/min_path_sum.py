def min_path_sum(grid):
    m, n = len(grid), len(grid[0])
    dp = [[0 for _ in range(n)] for _ in range(m)]
    dp[0][0] = grid[0][0]

    # Fill first row
    for j in range(1, n):
        dp[0][j] = dp[0][j - 1] + grid[0][j]

    # Fill first column
    for i in range(1, m):
        dp[i][0] = dp[i - 1][0] + grid[i][0]

    for i in range(1, m):
        for j in range(1, n):
            # Cost to reach (i,j) is grid[i][j] + min cost from above or left
            dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1])

    return dp[m - 1][n - 1]


# Example
grid = [[1, 3, 1], [1, 5, 1], [4, 2, 1]]
print(f"Minimum path sum in the grid: {min_path_sum(grid)}")
