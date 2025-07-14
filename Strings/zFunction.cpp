#include <bits/stdc++.h>

using namespace std;

void zFunction(string &s)
{
    int n = s.size();
    int l = 0, r = 0;
    vector<int> z(n, 0);
    for (int i = 1; i < n; i++)
    {
        if (i < r)
        {
            z[i] = min(r - i, z[i - 1]);
        }

        while ((i + z[i]) < n && s[i + z[i]] == s[z[i]])
        {
            z[i]++;
        }

        if (i + z[i] > r)
        {
            l = i;
            r = i + z[i];
        }
    }

    for (int x : z)
    {
        cout << x << ' ';
    }
}

int main()
{
    string s = "aaabbaxd";
    zFunction(s);

    return 0;
}

/*
Applications:

1. Pattern Matching

string s = p + "#" + t;
vector<int> z = z_function(s);

for (int i = p.size() + 1; i < s.size(); i++) {
    if (z[i] == p.size()) {
        cout << "Pattern occurs at position " << i - p.size() - 1 << "\n";
    }
}

3. Distinct Substrings, in O(N^2)

long long countDistinctSubstrings(const string &s) {
    long long total = 0;
    string curr = "";

    for (char c : s) {
        curr += c;
        string rev = curr;
        reverse(rev.begin(), rev.end());
        vector<int> z = computeZFunction(rev);

        int maxZ = 0;
        for (int zi : z)
            maxZ = max(maxZ, zi);

        total += curr.size() - maxZ;
    }



3. String Compression
Task: Find the smallest string t such that string s = t + t + ... + t

Use Z-function:

for (int i = 1; i < n; i++) {
    if (n % i == 0 && z[i] == n - i) {
        // s is made of repeating t = s.substr(0, i)
        return i;
    }
}

*/