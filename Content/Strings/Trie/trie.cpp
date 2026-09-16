struct Vertex {
    int next[26];
    bool output = false;
    int link = -1;
    int p;
    char pch;
    int go[26];
 
    string text = "";
    int nearestOutput = -2;
    Vertex(int par = 0, char ch = '$'): p(par), pch(ch) {
        fill(begin(next), end(next), -1);
        fill(begin(go), end(go), -1);
    }
};
vector<Vertex> t(1);

int addString(string& s) {
    int v = 0;
    for(char ch: s) {
        int c = ch - 'a';
        if(t[v].next[c] == -1) { 
            t[v].next[c] = t.size();
            t.emplace_back(v, ch);
        }
        v = t[v].next[c];
    }
    t[v].output = true;
    t[v].text = s;
    return v;
}
 
int go(int v, char ch);
 
int getLink(int v) {
    if(t[v].link == -1) {
        if(v == 0 || t[v].p == 0) {
            t[v].link = 0;
        } else {
            t[v].link = go(getLink(t[v].p), t[v].pch);
        }
    }
    return t[v].link;
}
 
int go(int v, char ch) {
    int c = ch - 'a';
    if(t[v].go[c] == -1) {
        if(t[v].next[c] != -1) {
            t[v].go[c] = t[v].next[c];
        } else {
            t[v].go[c] = v == 0 ? 0: go(getLink(v), ch);
        }
    }
    return t[v].go[c];
}
 
int getNearestOutput(int v) {
    if(t[v].nearestOutput == -2) {
        if(v == 0) {
            t[v].nearestOutput = -1;
        } else {
            int u = getLink(v);
            if(u == 0) {
                t[v].nearestOutput = -1;
            } else if(t[u].output) {
                t[v].nearestOutput = u;
            } else {
                t[v].nearestOutput = getNearestOutput(u);
            }
        }
    }
    return t[v].nearestOutput;
}
