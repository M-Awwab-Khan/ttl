def lis(arr):
    n = len(arr)
    if n == 0:
        return 0
    dp = [1] * n

    for i in range(1, n):
        for j in range(i):
            if arr[i] > arr[j]:
                dp[i] = max(dp[i], 1 + dp[j])
    return max(dp)


# Example
arr = [10, 22, 9, 33, 21, 50, 41, 60]
print(f"Length of LIS: {lis(arr)}")
