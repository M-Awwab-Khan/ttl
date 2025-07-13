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
	T sum(int u, int l, int d, int r) { // Calculate the sum of the submatrix [u, l] to [d, r)
		return p[d][r] - p[d][l] - p[u][r] + p[u][l];
	}
};

int main() {
	vector<vector<int>> v = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};
	SubMatrix<int> sm(v);
	cout << sm.sum(0, 0, 2, 2) << endl; // 
	cout << sm.sum(1, 1, 2, 2) << endl; // 
	cout << sm.sum(0, 1, 3, 2) << endl; // 
	return 0;
}