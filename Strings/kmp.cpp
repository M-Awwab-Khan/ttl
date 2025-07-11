#include <bits/stdc++.h>

using namespace std;

void computeLps(string &pat, vector<int> &lps)
{
    int i = -1;
    lps[0] = 0;
    for (int j = 1; j < pat.size(); j++)
    {
        while (i >= 0 && pat[j] != pat[i + 1])
        {
            i = lps[i] - 1;
        }
        if (pat[j] == pat[i + 1])
        {
            i++;
        }
        lps[j] = i + 1;
    }
}

void KMP(string &txt, string &pat, char wildCard)
{
    vector<int> lps(pat.size()), matches;
    computeLps(pat, lps);

    int i = 0;
    int j = 0;
    while (i < txt.size())
    {
        if (j < pat.size() && (pat[j] == wildCard || (pat[j] == txt[i])))
        {
            i++;
            j++;
        }

        if (j == pat.size())
        {
            matches.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < txt.size() && j < pat.size() && (pat[j] != txt[i] && pat[j] != wildCard))
        {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i++;
            }
        }
    }

    for (int i : matches)
    {
        cout << i << ' ' << '\n';
    }
}

int main()
{
    string txt = "foobarbarbarfoo";
    string pat = "???bar";
    char wildCard = '?';
    KMP(txt, pat, wildCard);
    return 0;
}