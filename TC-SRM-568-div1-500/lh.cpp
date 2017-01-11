#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;

class EqualSums {
private:
	static const int maxn = 55, mod = 1000000007;
	static int a[maxn][maxn];
	int n, m;

	void print() {
		for (int i = 1; i <= m; ++i, puts(""))
			for (int j = 1; j <= n; ++j) printf("%3d ", a[i][j]);
		return;
	}
public:
	int count(vector<string> board) {
		m = n = board.size();
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (board[i][j] == '-') a[i+1][j+1] = -1;
				else a[i+1][j+1] = board[i][j] - '0';
			}
		}
		for (int i = 1; i <= n; ++i) {
			int j = 1,mm=-1;
			for (; j <= m; ++j) if (a[j][i] >= 0) {
				if (mm < 0 || a[j][i] < a[mm][i]) mm = j;
			}
			j = mm;
			if (j != 1) {
				for (int k = 1; k <= n; ++k) swap(a[1][k], a[j][k]);
			}
			
			//puts("------------------------");
			//printf("i=%d\n", i);
			//puts("------------------------");
			//print();

			for (j = 2; j <= m; ++j) if (a[j][i]>=0) {
				for (int k = 1; k <= n; ++k) if (k != i && a[j][k]>=0) {
					if (a[1][k] < 0) {
						a[1][k] = a[1][i] + a[j][k] - a[j][i];
						if (a[1][k] < 0) {
							//printf("k=%d\n", k);
							return 0;
						}
					}
					else if (a[1][k] - a[1][i] != a[j][k] - a[j][i]) return 0;
				}
				for (int k = 1; k <= n; ++k) swap(a[m][k], a[j][k]);
				--m;
				--j;
			}
		}
		for (int i = 1; i <= m; ++i) {
			int k = 1000000;
			for (int j = 1; j <= n; ++j) if (a[i][j] >= 0) k = min(k, a[i][j]);
			a[i][i] = k;
//			printf("a[%d]=%d\n", i, a[i][i]);
		}
		long long ans = 0;
		for (int i = 1; i <= m; ++i) {
			long long tmp = 1;
			for (int j = 1; j < i; ++j) tmp = tmp*a[j][j] % mod;
			for (int j = i + 1; j <= m; ++j) tmp = tmp*(a[j][j] + 1) % mod;
			ans = (ans + tmp) % mod;
		}
		return ans;
	}
};

int EqualSums::a[maxn][maxn];
