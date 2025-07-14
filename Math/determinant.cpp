#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for (int i = (a); i < (b); i++)
#define sz(x) ((int)(x).size())

double det(vector<vector<double>>& a) {
	int n = sz(a); double res = 1;
	rep(i,0,n) {
		int b = i;
		rep(j,i+1,n) if (fabs(a[j][i]) > fabs(a[b][i])) b = j;
		if (i != b) swap(a[i], a[b]), res *= -1;
		res *= a[i][i];
		if (res == 0) return 0;
		rep(j,i+1,n) {
			double v = a[j][i] / a[i][i];
			if (v != 0) rep(k,i+1,n) a[j][k] -= v * a[i][k];
		}
	}
	return res;
}

int main() {
    cout << fixed << setprecision(6);
    cout << "=== DETERMINANT TESTING ===" << endl << endl;

    // Example matrix
    vector<vector<double>> mat = {
        {1, 2, 3},
        {0, 1, 4},
        {5, 6, 0}
    };

    double result = det(mat);
    cout << "Determinant: " << result << endl;
    // Expected output: Determinant: 1

    cout << "\n=== TESTING COMPLETE ===" << endl;
    cout << "Compare outputs with expected values above!" << endl;

    return 0;
}