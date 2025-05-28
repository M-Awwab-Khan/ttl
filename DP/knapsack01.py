def knapsack_01(weights, values, capacity):
    n = len(weights)
    dp = [[0 for _ in range(capacity + 1)] for _ in range(n + 1)]

    for i in range(1, n + 1):
        for w in range(1, capacity + 1):
            if weights[i - 1] <= w:
                dp[i][w] = max(
                    values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]
                )
            else:
                dp[i][w] = dp[i - 1][w]
    return dp[n][capacity]


weights = [1, 2, 3]
values = [60, 100, 120]
capacity = 5
print(f"Maximum value in 0/1 Knapsack: {knapsack_01(weights, values, capacity)}")
