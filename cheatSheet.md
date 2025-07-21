# Gray Code

`g(n) = n ^ (n >> 1)`

# Inverse Gray Code

<pre> ```
int invGray(int g) {
    int n = 0;
    while(g) {
        n ^= g;
        g >>= 1;
    }
    return n;
} ``` </pre>
