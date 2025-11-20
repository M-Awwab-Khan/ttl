#include <bits/stdc++.h>
using namespace std;

template<class T>
struct SubMatrix {
	vector<vector<T>> p;
	SubMatrix(vector<vector<T>>& v) {
		int R = v.size(), C = v[0].size();
		p.assign(R+1, vector<T>(C+1));
        for (int r = 0; r < R; r++)
            for (int c = 0; c < C; c++)
                p[r+1][c+1] = v[r][c] + p[r][c+1] + p[r+1][c] - p[r][c];
	}
	T sum(int sr, int sc, int er, int ec) { // Calculate the sum of the submatrix from [sr, sc] to [er, ec] inclusive
		return p[er+1][ec+1] - p[er+1][sc] - p[sr][ec+1] + p[sr][sc];
	}
};

int main() {
	vector<vector<int>> v = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};
	SubMatrix<int> sm(v);
	cout << sm.sum(0, 0, 1, 1) << endl; // Sum from (0,0) to (1,1): 1+2+4+5 = 12
	cout << sm.sum(1, 1, 1, 1) << endl; // Sum from (1,1) to (1,1): 5 = 5
	cout << sm.sum(0, 1, 2, 1) << endl; // Sum from (0,1) to (2,1): 2+5+8 = 15
	return 0;
}