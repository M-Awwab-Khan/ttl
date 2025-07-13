#include <bits/stdc++.h>
using namespace std;

// === MODULAR ARITHMETIC UTILITIES ===
const long long MOD = 1e9 + 7;  // Default modulus for CP (change if needed)

// --- Modular Addition ---
long long mod_add(long long a, long long b, long long mod = MOD) {
    return ((a % mod) + (b % mod)) % mod;
}

// --- Modular Subtraction ---
long long mod_sub(long long a, long long b, long long mod = MOD) {
    return ((a % mod) - (b % mod) + mod) % mod;
}

// --- Modular Multiplication ---
long long mod_mul(long long a, long long b, long long mod = MOD) {
    return ((a % mod) * (b % mod)) % mod;
}

// --- Modular Exponentiation (a^b % mod) ---
long long mod_pow(long long a, long long b, long long mod = MOD) {
    long long result = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) {
            result = (result * a) % mod;
        }
        a = (a * a) % mod;
        b >>= 1;
    }
    return result;
}

// --- Modular Inverse using Fermat's Little Theorem ---
long long mod_inv_fermat(long long a, long long mod = MOD) {
    // Requires mod to be prime
    return mod_pow(a, mod - 2, mod);
}

// --- Extended Euclidean Algorithm ---
long long extended_gcd(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long g = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

// --- Modular Inverse using Extended Euclidean Algorithm ---
long long mod_inv_euclid(long long a, long long mod = MOD) {
    long long x, y;
    long long g = extended_gcd(a, mod, x, y);
    if (g != 1) {
        throw invalid_argument("No modular inverse exists for " + to_string(a) + " under mod " + to_string(mod));
    }
    return (x % mod + mod) % mod;
}

// --- Chinese Remainder Theorem ---
long long chinese_remainder_theorem(const vector<long long>& remainders, const vector<long long>& moduli) {
    /*
    Solves system of congruences using CRT:
    x ≡ r1 (mod m1)
    x ≡ r2 (mod m2)
    ...
    Returns: (x mod M), where M = product of all moduli
    */
    assert(remainders.size() == moduli.size());
    long long x = 0;
    long long M = 1;
    
    for (long long m : moduli) {
        M *= m;
    }
    
    for (int i = 0; i < remainders.size(); i++) {
        long long r_i = remainders[i];
        long long m_i = moduli[i];
        long long M_i = M / m_i;
        long long inv = mod_inv_euclid(M_i, m_i);
        x = (x + r_i * M_i % M * inv % M) % M;
    }
    
    return x;
}

// --- Precomputed Modular Inverses ---
vector<long long> precompute_inverses(int n, long long mod = MOD) {
    vector<long long> inv(n);
    if (n > 0) inv[1] = 1;
    for (int i = 2; i < n; i++) {
        inv[i] = mod - (mod / i) * inv[mod % i] % mod;
    }
    return inv;
}

// === SAMPLE DRIVER ===
int main() {
    long long a = 7, b = 5;
    cout << a << " + " << b << " mod " << MOD << " = " << mod_add(a, b) << endl;
    cout << a << " - " << b << " mod " << MOD << " = " << mod_sub(a, b) << endl;
    cout << a << " * " << b << " mod " << MOD << " = " << mod_mul(a, b) << endl;
    cout << a << "^" << b << " mod " << MOD << " = " << mod_pow(a, b) << endl;
    cout << "Modular inverse of " << a << " using Fermat = " << mod_inv_fermat(a) << endl;
    cout << "Modular inverse of " << a << " using Extended Euclid = " << mod_inv_euclid(a) << endl;
    
    // Example for CRT:
    // x ≡ 2 mod 3
    // x ≡ 3 mod 5
    // x ≡ 2 mod 7
    vector<long long> rem = {2, 3, 2};
    vector<long long> mod_vals = {3, 5, 7};
    cout << "Solution to system using CRT = " << chinese_remainder_theorem(rem, mod_vals) << endl;
    
    // Precompute inverses example
    auto inv = precompute_inverses(10);
    cout << "Precomputed inverses: ";
    for (int i = 1; i < inv.size(); i++) {
        cout << "inv[" << i << "] = " << inv[i] << " ";
    }
    cout << endl;
    
    return 0;
}