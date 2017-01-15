#line 5 "KingdomAndCities.cpp"
#include <bits/stdc++.h>

using namespace std;

#define SZ(x) (int)(x).size()
#define pb push_back
#define mp make_pair

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long ll;
typedef pair<int,int> pii;

const int N = 50, K = 50;
const int MOD = 1e9 + 7;

int c[N * N + 9][N + 9];
int f[N + 9][K + 9];

class KingdomAndCities {
public:
	int get1(int n, int k) {
		return ((k >= 1 ? (ll)f[n - 1][k - 1] * (k - 1) % MOD : 0) + (k >= 2 ? (ll)f[n - 1][k - 2] * (k - 2) % MOD : 0)) % MOD;
		// Making one node with 2 degrees in n-graph equals adding a node on a edge of (n - 1)-graph
	}
	int get2(int n, int k) {
		if(k < 3) return 0;
		int a = get1(n - 1, k - 1), b = get1(n - 1, k - 2);
		f[n - 1][k - 1] = a, f[n - 1][k - 2] = b;
		return ((ll)f[n - 1][k - 1] * (k - 1) % MOD + (k >= 4 ? (ll)f[n - 1][k - 2] * (k - 4) % MOD : 0) + (ll)f[n - 2][k - 3] * (n - 2)) % MOD;
		// repeat get1 and consider some special situation
	}
    int howMany(int n, int m, int k) {
		//calculate combinatory number
		for(int i = 0; i <= N * N; ++i) {
			c[i][0] = 1;
			for(int j = 1; j <= i && j <= N; ++j)
				c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % MOD;
		}
		//f[i][j] -> the number of different connected graphs with i nodes and j edges
		f[1][0] = 1;
		for(int i = 2; i <= n; ++i)
			for(int j = i - 1; j <= k; ++j) {
				f[i][j] = c[c[i][2]][j];
				for(int p = 1; p < i; ++p)
					for(int q = p - 1; q <= j; ++q)
						(f[i][j] += MOD - (ll)c[i - 1][p - 1] * f[p][q] % MOD * c[c[i - p][2]][j - q] % MOD) %= MOD;
			}
		if(m == 0) return f[n][k];
		else if(m == 1) return get1(n, k);
		else return get2(n, k);
    }
};
