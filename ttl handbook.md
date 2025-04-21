# $(ttl)^n$ Handbook
## 🧠 **General Must-Know Math Concepts**

### ✅ Number Theory
- **GCD/LCM**: `gcd(a, b) = gcd(b, a % b)`
- **Extended Euclidean Algorithm**: Useful for solving Diophantine equations
- **Modular Inverse**:
  - When `m` is prime: `a^(-1) ≡ a^(m-2) mod m`
  - Use Extended Euclid when `m` is not prime
- **Fermat’s Little Theorem**: `a^(p−1) ≡ 1 (mod p)` (if `p` is prime and `a` is not divisible by `p`)
- **Chinese Remainder Theorem**
- **Sieve of Eratosthenes** (for primes ≤ 10^7)
- **Factorization using sqrt(n)**

## 🧠 DEEP DIVE: NUMBER THEORY FOR CP
### 1. **Divisibility & Prime Basics**
- **Divides**: `a | b` → `b % a == 0`
- **Properties**:
  - If `a | b` and `a | c` ⇒ `a | (b ± c)`
  - If `a | bc` and `gcd(a, b) = 1` ⇒ `a | c`

#### ✅ **Prime Check** (basic)
```cpp
bool isPrime(int n) {
  if (n <= 1) return false;
  for (int i = 2; i*i <= n; i++)
    if (n % i == 0) return false;
  return true;
}
```

---

### 2. **GCD, LCM & Extended Euclid**

#### ✅ GCD
```cpp
int gcd(int a, int b) {
  return b == 0 ? a : gcd(b, a % b);
}
```

#### ✅ Extended Euclidean Algorithm
Find `x` and `y` such that `ax + by = gcd(a, b)`

```cpp
int extendedGCD(int a, int b, int &x, int &y) {
  if (b == 0) {
    x = 1; y = 0;
    return a;
  }
  int x1, y1;
  int d = extendedGCD(b, a % b, x1, y1);
  x = y1;
  y = x1 - (a / b) * y1;
  return d;
}
```

---

### 3. **Modular Arithmetic**

#### ✅ Properties
- `(a + b) % m = ((a % m) + (b % m)) % m`
- `(a * b) % m = ((a % m) * (b % m)) % m`
- Modular subtraction: `((a % m) - (b % m) + m) % m`

#### ✅ Modular Inverse
- Only exists if `gcd(a, m) = 1`
- If `m` is prime: `a^-1 = a^(m-2) % m` (Fermat)
```cpp
ll modpow(ll a, ll b, ll m) {
  ll res = 1;
  while (b > 0) {
    if (b & 1) res = (res * a) % m;
    a = (a * a) % m;
    b >>= 1;
  }
  return res;
}
```

---

### 4. **Sieve of Eratosthenes**
Find all primes up to `N` in `O(N log log N)`

```cpp
const int N = 1e7;
bool prime[N+1];
void sieve() {
  fill(prime, prime + N + 1, true);
  prime[0] = prime[1] = false;
  for (int i = 2; i * i <= N; i++) {
    if (prime[i])
      for (int j = i*i; j <= N; j += i)
        prime[j] = false;
  }
}
```

---

### 5. **Prime Factorization**
- **Trial division** up to √n
- For multiple queries: **precompute smallest prime factors** (SPF) using sieve

```cpp
int spf[N+1];
void computeSPF() {
  for (int i = 1; i <= N; i++) spf[i] = i;
  for (int i = 2; i*i <= N; i++) {
    if (spf[i] == i) {
      for (int j = i*i; j <= N; j += i)
        if (spf[j] == j) spf[j] = i;
    }
  }
}
// Use SPF to factor any number in O(log n)
while (x != 1) {
  cout << spf[x] << " ";
  x /= spf[x];
}
```

---

### 6. **Euler’s Totient Function φ(n)**
Counts numbers `1 ≤ x < n` such that `gcd(x, n) = 1`

#### ✅ Properties
- `φ(p) = p - 1` for prime `p`
- `φ(p^k) = p^k - p^(k-1)`
- `φ(a * b) = φ(a) * φ(b)` if `gcd(a, b) = 1`

#### ✅ Precompute φ(i) for all `i ≤ N`
```cpp
int phi[N+1];
void computeTotient() {
  for (int i = 1; i <= N; i++) phi[i] = i;
  for (int i = 2; i <= N; i++) {
    if (phi[i] == i) {
      for (int j = i; j <= N; j += i)
        phi[j] -= phi[j] / i;
    }
  }
}
```

---

### 7. **Chinese Remainder Theorem (CRT)**
Solve:
```
x ≡ a1 (mod m1)
x ≡ a2 (mod m2)
```
Works when `m1` and `m2` are coprime.

```cpp
// Solves for 2 congruences: x ≡ a1 mod m1, x ≡ a2 mod m2
pll CRT(ll a1, ll m1, ll a2, ll m2) {
  ll x, y;
  ll g = extendedGCD(m1, m2, x, y);
  if ((a2 - a1) % g != 0) return {-1, -1}; // No solution
  ll mod = m1 / g * m2;
  ll res = (a1 + (a2 - a1) / g * x % (m2 / g) * m1) % mod;
  if (res < 0) res += mod;
  return {res, mod}; // x ≡ res (mod mod)
}
```

---

###  8. Number of Divisors of `n`
If `n = p₁^e₁ * p₂^e₂ * ... * pₖ^eₖ` (prime factorization),  
then:  
### ➤ `Number of Divisors `= $(e₁ + 1) * (e₂ + 1) * ... * (eₖ + 1)$

```cpp
int numberOfDivisors(int n) {
    int res = 1;
    for (int i = 2; i*i <= n; i++) {
        int count = 0;
        while (n % i == 0) {
            n /= i;
            count++;
        }
        res *= (count + 1);
    }
    if (n > 1) res *= 2; // if n is prime at the end
    return res;
}
```

---

### 9. Sum of Divisors of `n`
If `n = p₁^e₁ * p₂^e₂ * ... * pₖ^eₖ`,  
then:  
### ➤ `Sum of Divisors = [(p₁^(e₁+1) - 1) / (p₁ - 1)] * ...`
```cpp
int sumOfDivisors(int n) {
    int sum = 1;
    for (int i = 2; i*i <= n; i++) {
        int curr_sum = 1, term = 1;
        while (n % i == 0) {
            n /= i;
            term *= i;
            curr_sum += term;
        }
        sum *= curr_sum;
    }
    if (n > 1) sum *= (1 + n);
    return sum;
}
```

---

### 10. Precompute Number and Sum of Divisors for all `1 <= i <= N`

#### O(N log N)

```cpp
const int N = 1e6;
int numDiv[N+1], sumDiv[N+1];

void precomputeDivisors() {
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j += i) {
            numDiv[j]++;     // i is a divisor of j
            sumDiv[j] += i;  // add i as a divisor
        }
    }
}
```

---

## ✅ Examples

| n   | Divisors      | #Divisors | Sum     |
|-----|----------------|-----------|----------|
| 12  | 1, 2, 3, 4, 6, 12 | 6         | 28       |
| 18  | 1, 2, 3, 6, 9, 18 | 6         | 39       |
| 36  | 1, 2, 3, 4, 6, 9, 12, 18, 36 | 9 | 91 |

---

### ✅ Combinatorics
Perfect — **Combinatorics** is a goldmine for speed programming: from counting problems to probability, DP transitions, and even constructive proofs.

Let’s break it down into the most **useful formulas, theorems, and algorithms** you need to remember and code quickly during a contest

### 🔹 1. Factorials & Modular Inverse
- `n! = n × (n-1)!`
- For large `n`, use precomputation.
- When working modulo `mod`, use:
  - Fermat’s Little Theorem if `mod` is prime:
    ```
    a^(-1) ≡ a^(mod - 2) (mod mod)
    ```

---

### 🔹 2. nCr (Binomial Coefficient
$$
C(n, r) = \frac{n!}{r! \cdot (n-r)!}
$$

### ➤ Efficient C++ with Modulo (1e9+7)
```cpp
const int N = 1e6;
const int MOD = 1e9 + 7;

int fact[N+1], invFact[N+1];

int power(int a, int b) {
    int res = 1;
    while (b) {
        if (b % 2) res = 1LL * res * a % MOD;
        a = 1LL * a * a % MOD;
        b /= 2;
    }
    return res;
}

void precomputeFactorials() {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = 1LL * fact[i-1] * i % MOD;
        invFact[i] = power(fact[i], MOD - 2);
    }
}

int nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return 1LL * fact[n] * invFact[r] % MOD * invFact[n - r] % MOD;
}
```

---

### 🔹 3. Pascal’s Triangle
- `C(n, k) = C(n-1, k-1) + C(n-1, k)`
- Useful for small `n`, or when no mod inverse allowed.

```cpp
int C[1005][1005]; // up to 1000
void pascal() {
    for (int n = 0; n < 1000; n++) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; k++)
            C[n][k] = (C[n-1][k-1] + C[n-1][k]);
    }
}
```

---

## ✅ USEFUL COMBINATORIAL FORMULAS & TECHNIQUES

### 🔸 1. Stars and Bars (Distributions)
#### ➤ Ways to distribute `k` identical items into `n` boxes:
- No empty box: `C(k-1, n-1)`
- Empty allowed: `C(k + n - 1, n - 1)`

---

### 🔸 2. Inclusion-Exclusion Principle (PIE)
Count total - overcounts:
$$
|A \cup B| = |A| + |B| - |A \cap B|
$$
For 3 sets:
$$
|A \cup B \cup C| = |A| + |B| + |C| - |A\cap B| - |A\cap C| - |B\cap C| + |A\cap B\cap C|
$$

---

### 🔸 3. Derangement (No object stays in its place)
- `!n = (n-1) * (!(n-1) + !(n-2))`
- Base: `!0 = 1`, `!1 = 0`
```cpp
int derange(int n) {
    vector<int> D(n+1);
    D[0] = 1, D[1] = 0;
    for (int i = 2; i <= n; i++)
        D[i] = 1LL * (i - 1) * (D[i - 1] + D[i - 2]) % MOD;
    return D[n];
}
```

---

### 🔸 4. Catalan Numbers
$$
C_n = \frac{1}{n+1} C(2n, n)
$$
Used in:
- Valid parentheses,
- BST count,
- Polygon triangulation.

```cpp
int catalan(int n) {
    return 1LL * nCr(2*n, n) * power(n+1, MOD-2) % MOD;
}
```

---

### 🔸 5. Multinomial Coefficients
$$
\text{Ways to partition n items into groups of sizes } a, b, c:
= \frac{n!}{a! \cdot b! \cdot c!}
$$

---

### 🔸 6. Subset Count
- Number of subsets of an `n`-element set: `2^n`
- Number of **k-sized** subsets: `C(n, k)`

---

### ✅ Modular Arithmetic
- `(a + b) % m = ((a % m) + (b % m)) % m`
- `(a * b) % m = ((a % m) * (b % m)) % m`
- Use **modulo normalization**: `((x % mod) + mod) % mod`
- Power under modulo: **Binary Exponentiation**

---

### ✅ Algebra & Polynomials
- **Sum of first n natural numbers**: `n(n+1)/2`
- **Sum of squares**: `n(n+1)(2n+1)/6`
- **Sum of cubes**: `(n(n+1)/2)^2`
- Roots of quadratic equation: `x = [-b ± sqrt(b² - 4ac)] / 2a`
- **Vieta’s formulas**:
  - Sum of roots: `−b/a`, Product of roots: `c/a`

---

### ✅ Geometry (2D)
Awesome, let’s jump into a **Competitive Programming Geometry Deep Dive** 🚀 — geometry is a game-changer, especially in Div 2/Div 1 contests where visual thinking + precision = 🔥.

---

## ✅ Must-Know Geometry Concepts & Formulas

### 🔸 1. Distance Between Two Points
For points `(x1, y1)` and `(x2, y2)`:
$$
\text{Distance} = \sqrt{(x2 - x1)^2 + (y2 - y1)^2}
$$

---

### 🔸 2. Area of Triangle
Given 3 points `(x1, y1), (x2, y2), (x3, y3)`:

#### ➤ Shoelace Formula:
$$
\text{Area} = \frac{1}{2} |x_1(y_2 - y_3) + x_2(y_3 - y_1) + x_3(y_1 - y_2)|
$$

---

### 🔸 3. Cross Product (2D)
For vectors **a = (x1, y1)**, **b = (x2, y2)**:
$$
a \times b = x1*y2 - y1*x2
$$
- `> 0`: counter-clockwise (left turn)  
- `< 0`: clockwise (right turn)  
- `= 0`: collinear

---

### 🔸 4. Orientation of Three Points (Turn Test)
```cpp
int orientation(Point a, Point b, Point c) {
    int val = (b.y - a.y)*(c.x - b.x) - (b.x - a.x)*(c.y - b.y);
    if (val == 0) return 0;  // collinear
    return (val > 0 ? 1 : 2); // clockwise or counter-clockwise
}
```

---

### 🔸 5. Point Inside Triangle (Using Area)
- Compute area of ABC
- Compute area of ABP, BCP, CAP
- If sum of the 3 = ABC → inside

---

### 🔸 6. Convex Hull (Monotone Chain — O(n log n))

Classic algorithm to compute minimal enclosing polygon.

```cpp
vector<Point> convexHull(vector<Point>& pts) {
    sort(pts.begin(), pts.end()); // sort x, then y
    vector<Point> hull;

    // Lower hull
    for (auto p : pts) {
        while (hull.size() >= 2 && cross(hull[hull.size()-2], hull.back(), p) <= 0)
            hull.pop_back();
        hull.push_back(p);
    }

    // Upper hull
    int sz = hull.size();
    for (int i = pts.size()-2; i >= 0; --i) {
        while (hull.size() > sz && cross(hull[hull.size()-2], hull.back(), pts[i]) <= 0)
            hull.pop_back();
        hull.push_back(pts[i]);
    }

    hull.pop_back(); // last point == first point
    return hull;
}
```

---

### 🔸 7. Line Equation
Given 2 points `(x1, y1)` and `(x2, y2)`:

#### ➤ General Form:
$$
Ax + By + C = 0
$$
where  
- `A = y2 - y1`,  
- `B = x1 - x2`,  
- `C = -A*x1 - B*y1`

---

### 🔸 8. Distance from a Point to Line

Given line `Ax + By + C = 0` and point `(x0, y0)`:
$$
\text{Distance} = \frac{|Ax_0 + By_0 + C|}{\sqrt{A^2 + B^2}}
$$

---

### 🔸 9. Circle Geometry
- Circle center at `(h, k)` with radius `r`:  
 $$
  (x - h)^2 + (y - k)^2 = r^2
$$

- Check if point lies **inside**, **on**, or **outside** the circle.

---

### 🔸 10. Polygon Area (Shoelace Formula)
Given vertices `(x0, y0), (x1, y1), ..., (xn-1, yn-1)`:

$$
\text{Area} = \frac{1}{2} \left| \sum_{i=0}^{n-1}(x_i y_{i+1} - x_{i+1} y_i) \right|
$$
where `(xn = x0, yn = y0)` to close the polygon.

---


### ✅ Sequences & Series
- Arithmetic Series: `n/2 * (2a + (n-1)d)`
- Geometric Series: `a * (r^n - 1) / (r - 1)`
- Fibonacci:
  - `F(n) = F(n-1) + F(n-2)`
  - Matrix Exponentiation for O(log n) Fibonacci

---

### ✅ Probabilities
- Basic P(A ∩ B), P(A ∪ B)
- Expected value formula
- Linearity of expectation (even when variables are not independent)

---

### ✅ Bit Manipulation (math-style)
- Check if a number is power of 2: `n & (n - 1) == 0`
- Count bits: `__builtin_popcount(n)` in C++
- `n & (n-1)` removes the lowest set bit
- XOR tricks: `a ^ a = 0`, `a ^ 0 = a`, XOR is its own inverse

---

### ✅ Others
- **Fast I/O (important in speed rounds)**: Use `scanf/printf` or `cin.tie(0); ios::sync_with_stdio(false);`
- **Prefix sums** and **difference arrays**
- **Sliding window** & **two pointers**
- **Math inequalities** like Cauchy-Schwarz (sometimes)

---