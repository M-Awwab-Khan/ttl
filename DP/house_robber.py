def house_robber(nums):
    if not nums:
        return 0
    if len(nums) <= 2:
        return max(nums)

    dp = [0] * len(nums)
    dp[0] = nums[0]
    dp[1] = max(nums[0], nums[1])

    for i in range(2, len(nums)):
        dp[i] = max(dp[i - 2] + nums[i], dp[i - 1])

    return dp[-1]


nums = [2, 7, 9, 3, 1]
print(f"Maximum money from robbing houses: {house_robber(nums)}")


# Variation: Houses are in a circle (first and last are adjacent)
# Solution: Rob from house 0 to n-2 OR rob from house 1 to n-1, and take the max.
def house_robber_circle(nums):
    if not nums:
        return 0
    if len(nums) <= 2:
        return max(nums)
    return max(house_robber(nums[:-1]), house_robber(nums[1:]))


print(f"Maximum money from robbing houses in a circle: {house_robber_circle(nums)}")
