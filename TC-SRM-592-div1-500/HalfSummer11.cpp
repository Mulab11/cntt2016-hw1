#line 2 "LittleElephantAndPermutationDiv1.cpp"
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
#define mo 1000000007
typedef long long ll;
using namespace std;
int f[maxn][maxn][maxn * maxn], O;
void add(int &a, int b) {
	a += b; a %= mo;
}
class LittleElephantAndPermutationDiv1 {
	public:
		int getNumber(int n, int K) {
			int all = 0;
			for (int i = 1; i <= n; ++i) all += i;
			all *= 2;
			cl(f);
			f[0][0][0] = 1;
			for (int i = 1; i <= n; ++i)
				for (int j = 0; j < i; ++j) 
					for (int v = 0; v <= all; ++v)
						if (f[i - 1][j][v]) {
							int now = f[i - 1][j][v];
							add(f[i][j][v + i], now);
							add(f[i][j - 1][v + 2 * i], 1ll * now * j % mo * j % mo);
							add(f[i][j][v + i], 1ll * now * j % mo);
							add(f[i][j][v + i], 1ll * now * j % mo);
							add(f[i][j + 1][v], now);
						}
			int ans = 0;
			for (int i = K; i <= all; ++i)
				add(ans, f[n][0][i]);
			for (int i = 1; i <= n; ++i)
				ans = 1ll * ans * i % mo;
			return ans;
		}
};
