#include <bits/stdc++.h>

using namespace std;

vector<int> computeLPS(const string &pat)
{
    int n = pat.size();
    vector<int> lps(n, 0);
    int j = 0;

    for (int i = 1; i < n; i++)
    {

        while (j > 0 && pat[i] != pat[j])
        {
            j = lps[j - 1];
        }

        if (pat[i] == pat[j])
        {
            j++;
        }

        lps[i] = j;
    }

    for (int i : lps)
        cout << i << ' ';
    cout << '\n';
    return lps;
}

vector<int> kmpWildcardMatch(string &txt, string &pat)
{
    int n = txt.size(), m = pat.size();
    vector<int> res;
    if (m == 0)
        return res;

    vector<int> lps = computeLPS(pat);
    int j = 0;

    for (int i = 0; i < txt.size(); i++)
    {
        while (j > 0 && txt[i] != pat[j])
        {
            j = lps[j - 1];
        }

        if (txt[i] == pat[j])
        {
            j++;
        }

        if (j == pat.size())
        {
            res.push_back(i - j + 1);
            j = lps[j - 1];
        }
    }

    for (int i : res)
    {
        cout << i << ' ' << txt.substr(i, pat.size()) << "\n";
    }

    return res;
}

int main()
{
    // string txt = "foobarfarfarfoofunffffffff";
    string txt = "fooffffoobarfoo";
    string pat = "fff";
    kmpWildcardMatch(txt, pat);
    return 0;
}