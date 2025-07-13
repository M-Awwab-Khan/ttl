#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define rep(i,a,b) for (int i = (a); i < (b); ++i)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
const ll mod = 1000000007; // faster if const
ll euclid(ll a, ll b, ll &x, ll &y) {
    if (!b) return x = 1, y = 0, a;
    ll d = euclid(b, a % b, y, x);
    return y -= a/b * x, d;
}
struct Mod {
	ll x;
	Mod(ll xx) : x(xx) {}
	Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
	Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
	Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
	Mod operator/(Mod b) { return *this * invert(b); }
	Mod invert(Mod a) {
		ll x, y, g = euclid(a.x, mod, x, y);
		assert(g == 1); return Mod((x + mod) % mod);
	}
	Mod operator^(ll e) {
		if (!e) return Mod(1);
		Mod r = *this ^ (e / 2); r = r * r;
		return e&1 ? *this * r : r;
	}
};


// const ll mod = 1000000007, LIM = 200000; ///include-line
// ll* inv = new ll[LIM] - 1; inv[1] = 1;
// rep(i,2,LIM) inv[i] = mod - (mod / i) * inv[mod % i] % mod;


ull modmul(ull a, ull b, ull M) {
    return (a * b) % M;
}

ull modpow(ull b, ull e, ull M) {
    ull ans = 1;
    while (e > 0) {
        if (e & 1) ans = modmul(ans, b, M);  // multiply by b if the current bit is 1
        b = modmul(b, b, M);  // square b modulo M
        e >>= 1;  // divide e by 2
    }
    return ans;
}

const int LIM = 1e6;
bitset<LIM> isPrime;
vi eratosthenes() {
	const int S = (int)round(sqrt(LIM)), R = LIM / 2;
	vi pr = {2}, sieve(S+1); pr.reserve(int(LIM/log(LIM)*1.1));
	vector<pii> cp;
	for (int i = 3; i <= S; i += 2) if (!sieve[i]) {
		cp.push_back({i, i * i / 2});
		for (int j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
	}
	for (int L = 1; L <= R; L += S) {
		array<bool, S> block{};
		for (auto &[p, idx] : cp)
			for (int i=idx; i < S+L; idx = (i+=p)) block[i-L] = 1;
		rep(i,0,min(S, R - L))
			if (!block[i]) pr.push_back((L + i) * 2 + 1);
	}
	for (int i : pr) isPrime[i] = 1;
	return pr;
}

// Miller-Rabin primality test
bool isprime(ull n) {
	if (n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
	    s = __builtin_ctzll(n-1), d = n >> s;
	for (ull a : A) {   // ^ count trailing zeroes
		ull p = modpow(a%n, d, n), i = s;
		while (p != 1 && p != n - 1 && a % n && i--)
			p = modmul(p, p, n);
		if (p != n-1 && i != s) return 0;
	}
	return 1;
}

// --- Modular Inverse using Extended Euclidean Algorithm ---
ll mod_inv_euclid(ll a, ll mod = MOD) {
    ll x, y;
    ll g = extended_gcd(a, mod, x, y);
    if (g != 1) {
        throw invalid_argument("No modular inverse exists for " + to_string(a) + " under mod " + to_string(mod));
    }
    return (x % mod + mod) % mod;
}

// --- Extended Euclidean Algorithm ---
ll extended_gcd(ll a, ll b, ll& x, ll& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}



// --- Chinese Remainder Theorem ---
ll chinese_remainder_theorem(const vector<ll>& remainders, const vector<ll>& moduli) {
    /*
    Solves system of congruences using CRT:
    x ≡ r1 (mod m1)
    x ≡ r2 (mod m2)
    ...
    Returns: (x mod M), where M = product of all moduli
    */
    assert(remainders.size() == moduli.size());
    ll x = 0;
    ll M = 1;
    
    for (ll m : moduli) {
        M *= m;
    }
    
    for (int i = 0; i < remainders.size(); i++) {
        ll r_i = remainders[i];
        ll m_i = moduli[i];
        ll M_i = M / m_i;
        ll inv = mod_inv_euclid(M_i, m_i);
        x = (x + r_i * M_i % M * inv % M) % M;
    }
    
    return x;
}

int main() {
    cout << fixed << setprecision(6);
    cout << "=== MODULAR ARITHMETIC TESTING ===" << endl << endl;

    // Example usage of Mod class
    Mod a(5), b(3);
    cout << "a + b = " << (a + b).x << endl; // Expected: 8
    cout << "a - b = " << (a - b).x << endl; // Expected: 2
    cout << "a * b = " << (a * b).x << endl; // Expected: 15
    cout << "a / b = " << (a / b).x << endl; // Expected: 2

    // Example usage of modpow
    ull base = 2, exp = 10, mod = 1000;
    cout << "2^10 mod 1000 = " << modpow(base, exp, mod) << endl; // Expected: 24

    // Example usage of eratosthenes
    vi primes = eratosthenes();
    cout << "First 10 primes: ";
    for (int i = 0; i < 10 && i < primes.size(); ++i) {
        cout << primes[i] << " ";
    }
    cout << endl;

    // Example usage of isPrime
    ull num = 319993;
    cout << num << " is prime: " << (isprime(num) ? "true" : "false") << endl; // Expected: true

    cout << "\n=== TESTING COMPLETE ===" << endl;
}