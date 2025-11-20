// #include <bits/stdc++.h>
// using namespace std;

// /* TYPES  */
// #define ll long long
// #define pii pair<int, int>
// #define pll pair<long long, long long>
// #define vi vector<int>
// #define vll vector<long long>
// #define mii map<int, int>
// #define si set<int>
// #define sc set<char>

// /* FUNCTIONS */
// #define f(i, s, e) for (long long int i = s; i < e; i++)
// #define fe(i, s, e) for (long long int i = s; i <= e; i++)
// #define fr(i, e, s) for (long long int i = e - 1; i >= s; i--)
// #define pb push_back
// #define eb emplace_back
// #define all(x) x.begin(), x.end()

// /* PRINTS */
// template <class T>
// void print_v(vector<T> &v)
// {
//     for (auto x : v)
//         cout << x << ' ';
// }

// /* UTILS */
// #define MOD 1000000007
// #define PI 3.1415926535897932384626433832795
// #define read(type) readInt<type>()
// ll min(ll a, int b)
// {
//     if (a < b)
//         return a;
//     return b;
// }
// ll min(int a, ll b)
// {
//     if (a < b)
//         return a;
//     return b;
// }
// ll max(ll a, int b)
// {
//     if (a > b)
//         return a;
//     return b;
// }
// ll max(int a, ll b)
// {
//     if (a > b)
//         return a;
//     return b;
// }
// ll gcd(ll a, ll b)
// {
//     if (b == 0)
//         return a;
//     return gcd(b, a % b);
// }
// ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
// bool prime(ll a)
// {
//     if (a == 1)
//         return 0;
//     for (int i = 2; i <= round(sqrt(a)); ++i)
//         if (a % i == 0)
//             return 0;
//     return 1;
// }
// void yes() { cout << "YES\n"; }
// void no() { cout << "NO\n"; }
// void printCase(int i) { cout << "Case " << i << ": "; }

// unordered_map<string, unordered_set<int>> prefixMap;

// string getSignature(string &s)
// {
//     vi freq(26, 0);
//     for (char c : s)
//     {
//         freq[c - 'a']++;
//     }
//     string sig = "";
//     for (int x : freq)
//     {
//         sig += to_string(x) + '#';
//     }
//     return sig;
// }

// void solve()
// {
//     int n;
//     cin >> n;
//     string s;
//     string prefix;
//     f(i, 0, n)
//     {
//         cin >> s;
//         prefix = "";
//         for (char c : s)
//         {
//             prefix += c;
//             prefixMap[getSignature(prefix)].insert(i);
//         }
//     }

//     int q;
//     cin >> q;
//     while (q--)
//     {
//         cin >> s;
//         int ans = prefixMap[getSignature(s)].size();
//         cout << (ans == 0 ? -1 : ans) << '\n';
//     }
// }

// // Problem Link:

// int main()
// {
//     ios::ios_base::sync_with_stdio(0);
//     cin.tie(NULL);
//     int t = 1;
//     // cin >> t;
//     while (t--)
//     {
//         solve();
//     }
//     return 0;
// }


#include <bits/stdc++.h>
using namespace std;


/* FUNCTIONS */
#define f(i, s, e) for (long long int i = s; i < e; i++)
#define fe(i, s, e) for (long long int i = s; i <= e; i++)
#define fr(i, e, s) for (long long int i = e - 1; i >= s; i--)
#define pb push_back
#define eb emplace_back
#define all(x) x.begin(), x.end()

/* PRINTS */
template <class T>
void print_v(vector<T> &v)
{
    for (auto x : v)
        cout << x << ' ';
}

/* UTILS */
#define MOD 1000000007
#define PI 3.1415926535897932384626433832795
#define read(type) readInt<type>()
ll min(ll a, int b)
{
    if (a < b)
        return a;
    return b;
}
ll min(int a, ll b)
{
    if (a < b)
        return a;
    return b;
}
ll max(ll a, int b)
{
    if (a > b)
        return a;
    return b;
}
ll max(int a, ll b)
{
    if (a > b)
        return a;
    return b;
}
ll gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }
bool prime(ll a)
{
    if (a == 1)
        return 0;
    for (int i = 2; i <= round(sqrt(a)); ++i)
        if (a % i == 0)
            return 0;
    return 1;
}
void yes() { cout << "YES\n"; }
void no() { cout << "NO\n"; }
void printCase(int i) { cout << "Case " << i << ": "; }

int g(int n)
{
    return n ^ (n >> 1);
}

string getBin(int n, int size)
{
    string s(size, '0');

    int j = size - 1;
    while (n)
    {
        s[j] = char('0' + (n % 2));
        j--;
        // j = max(0, j);
        n /= 2;
    }

    return s;
}

void solve()
{
    int n;
    cin >> n;

    f(i, 0, pow(2, n))
    {
        cout << getBin(g(i), n) << '\n';
    }
}

// Problem Link: https://cses.fi/problemset/result/13797980/