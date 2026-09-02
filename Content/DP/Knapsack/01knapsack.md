# 0-1 Knapsack

> You are given n items with $i_{th}$ item having weight  $w_i$ and value $v_i$. Given a knapsack with max Weight capacity $W$. Find the max value you can have.

> Note that each item can only be taken *once*.

__Time Complexity: $O(nW)$__
__Space Complexity: $O(W)$__
```cpp
int knapsack(int n, vector<int>& weights, vector<int>& values, int W) {
    vector<int> dp(W + 1, 0);
    for(int i = 0; i < n; i++) {
        for(int j = W; j >= weights[i]; --j) {
            dp[j] = max(dp[j], values[i] + dp[W - j]);
        }
    }
    return dp[W];
}
```