#include "bits/stdc++.h"
using namespace std;

vector<int> manacher_odd(string s) {
    int n = s.size();                 
    s = "$" + s + "^";                
    vector<int> p(n + 2, 0);
    int l = 0, r = 1;
    for (int i = 1; i <= n; i++) {
        if (i <= r)
            p[i] = min(r - i, p[l + (r - i)]);
        while (s[i - p[i]] == s[i + p[i]]) 
            p[i]++;
        if (i + p[i] > r) {
            l = i - p[i];
            r = i + p[i];
        }
    }
    return vector<int>(p.begin() + 1, p.end() - 1);
}
 
vector<int> manacher(const string& s) {
    string t;
    t.reserve(2 * s.size() + 1);
    for (char c : s) {
        t += '#';                  
        t += c;
    }
    t += '#';
    return manacher_odd(t); 
}
 
void solve()
{
    string s;
    cin >> s; 
    string org = s;
 
    vi p = manacher(s);
    vi ans(org.size());
    vi right(org.size());
    f(i, 1, p.size() - 1) {
        int len = p[i] - 1;
        int pos = i / 2 + len / 2;
        if(i % 2 == 0) pos--;
        // Starting from pos with 'len' length palindrome
        right[pos] = max(right[pos], len);
    }
 
    int maxLen = 0;
    fr(i, org.size() - 1, -1) {
        maxLen = max(right[i], maxLen);
        ans[i] = maxLen;
        maxLen -= 2;
    }
 
    f(i, 0, org.size()) {
        cout << ans[i] << ' ';
    }
 
}
