//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include <bits/stdc++.h>

using namespace std;

#define FOR(i,a,b) for (int i = a; i <= b; i++)
#define FORD(i,a,b) for (int i = a; i >= b; i--)
#define SET(a,u) memset(a, u, sizeof(a))
#define mod 1000000007

class TwoConvexShapes{
public:
	vector <string> rotate(vector<string> a) {//return the grid b made by rotate grid a 90 degree
		int m = a.size();
		int n = a[0].size();
		vector <string> b;
		b.clear();
		FOR (i, 0, n - 1) {	//simple
			string s = "";
			FOR (j, 0, m - 1) s += a[j][n - 1 - i];
			b.push_back(s);
		}
		return b;
	}

	long long count_0(vector <string> a, char c) {
	// return 1 (or 0) if we can paint the grid with only color c
		int m = a.size();
		int n = a[0].size();

		FOR (i, 0, m - 1)
		FOR (j, 0, n - 1)
			if (a[i][j] != c && a[i][j] != '?') return 0;

		return 1;
	}

	long long count_1(vector <string> a, char c) {
		//the top left corner will be painted by color c

		int f[55][55];
		int m = a.size();
		int n = a[0].size();
		int high[55], low[55];
		//prepare low and high array
		SET (high, 0);
		FOR (i, 1, m)
			FOR (j, 1, n) if (a[i - 1][j - 1] == c) high[i] = j;

		FOR (i, 1, m) {
			low[i] = n + 1;
			FORD (j, n, 1)
				if (a[i - 1][j - 1] != '?' && a[i - 1][j - 1] != c) low[i] = j;
		}

		//avoid some trivial cases
		FOR (i, 1, m)
			FOR (j, 1, high[i]) if (a[i - 1][j - 1] != c && a[i - 1][j - 1] != '?') return 0;

		SET (f, 0);

		//initialization for dynamic program
		FOR (j, max(high[1], 1), n - 1) f[1][j] = (j < low[1]);

		//evaluate f[i][j] by f[i - 1][j'](s)
		FOR (i, 2, m)
		FOR (j, high[i], low[i] - 1) {
			f[i][j] = 0;
			FOR (k, j, n - 1)
				f[i][j] = (f[i][j] + f[i - 1][k]) % mod;
		}

		return f[m][0];
	}

	long long count_2(vector <string> a, char c) {
		//two top corner will be painted by color c
		int f[55][55][3];
		int m = a.size();
		int n = a[0].size();
		int high[55], low[55];

		SET (high, 0);
		FOR (i, 1, m)
			FOR (j, 1, n) if (a[i - 1][j - 1] == c) high[i] = j;

		FOR (i, 1, m) {
			low[i] = n + 1;
			FORD (j, n, 1)
				if (a[i - 1][j - 1] != '?' && a[i - 1][j - 1] != c) low[i] = j;
		}

		FOR (i, 1, m)
			FOR (j, 1, high[i]) if (a[i - 1][j - 1] != c && a[i - 1][j - 1] != '?') return 0;

		SET (f, 0);
		FOR (i, max(1, high[1]), min(low[1] - 1, n - 1)) f[1][i][0] = 1;

		FOR (i, 2, m)
		FOR (j, max(1, high[i]), min(n - 1, low[i] - 1)) {	//simple Dp
			f[i][j][0] = f[i - 1][j][0];

			f[i][j][1] = f[i - 1][j][1];
			FOR (k, j + 1, n - 1)
				f[i][j][1] = (f[i][j][1] + f[i - 1][k][0] + f[i - 1][k][1]) % mod;

			f[i][j][2] = f[i - 1][j][2];
			FOR (k, 1, j - 1)
				f[i][j][2] = (f[i][j][2] + f[i - 1][k][0] + f[i - 1][k][2]) % mod;
		}


		long long res = 0;
		FOR (i, max(high[m], 1) , min(n - 1, low[m] - 1)) res = (res + f[m][i][0] + f[m][i][1] + f[m][i][2]) % mod;	//sum to ans

		return res;
	}

	int countWays(vector <string> grid) {
		long long res = 0;
		res = (count_0(grid, 'B') + count_0 (grid,'W'));

		int m = grid.size(), n = grid[0].size();
		FOR (i, 0, m - 1) {
			FOR (j, 0, n - 1) cout << grid[i][j] << " ";
			cout << endl;
		}
				cout << endl;
		grid = rotate(grid);
		m = grid.size(), n = grid[0].size();
				FOR (i, 0, m - 1) {
			FOR (j, 0, n - 1) cout << grid[i][j] << " ";
			cout << endl;
		}
				cout << endl;
		grid = rotate(grid);
		m = grid.size(), n = grid[0].size();
				FOR (i, 0, m - 1) {
			FOR (j, 0, n - 1) cout << grid[i][j] << " ";
			cout << endl;
		}
				cout << endl;
		grid = rotate(grid);
		m = grid.size(), n = grid[0].size();
				FOR (i, 0, m - 1) {
			FOR (j, 0, n - 1) cout << grid[i][j] << " ";
			cout << endl;
		}
		cout << endl;

		FOR (i, 1, 4) {
			res = (res + count_1(grid, 'B')) % mod;
			grid = rotate(grid);
		}

		FOR (i, 1, 4) {
			res = (res + count_2(grid, 'B')) % mod;
			grid = rotate(grid);
		}

		FOR (i, 1, 4) {
			res = (res + count_1(grid, 'W')) % mod;
			grid = rotate(grid);
		}

		return res;
	}
};