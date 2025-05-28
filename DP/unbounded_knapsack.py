def unbounded_knapsack(weights, values, capacity):
    n = len(weights)
    dp = [0 for _ in range(capacity + 1)]

    for w in range(1, capacity + 1):
        for i in range(n):
            if weights[i] <= w:
                dp[w] = max(dp[w], values[i] + dp[w - weights[i]])
    return dp[capacity]


weights = [1, 2, 3]
values = [60, 100, 120]
capacity = 5
print(
    f"Maximum value in Unbounded Knapsack: {unbounded_knapsack(weights, values, capacity)}"
)
