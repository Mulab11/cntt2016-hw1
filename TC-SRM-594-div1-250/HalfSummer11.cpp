#line 2 "AstronomicalRecords.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 60
typedef long long ll;
using namespace std;
int f[maxn][maxn];
void gmax(int &a, int b) {
	if (b > a) a = b;
}
class AstronomicalRecords {
	public:
		int minimalPlanets(vector <int> A, vector <int> B) {
			int n = A.size(), m = B.size(), ans = n + m;
			for (int x = 0; x < n; ++x)
				for (int y = 0; y < m; ++y) {
					memset(f, -0x3f, sizeof(f));
					f[0][0] = 0;
					for (int i = 0; i <= n; ++i)
						for (int j = 0; j <= m; ++j) 
							if (f[i][j] >= 0) {
								gmax(f[i + 1][j], f[i][j]);
								gmax(f[i][j + 1], f[i][j]);
								if (i < n && j < m && 1ll * A[i] * B[y] == 1ll * A[x] * B[j])
									gmax(f[i + 1][j + 1], 1 + f[i][j]);
							}
					ans = min(ans, n + m - f[n][m]);
				}
			return ans;
		}
};
