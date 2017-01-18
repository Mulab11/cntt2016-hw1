#line 2 "MonstersValley.cpp"
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
int n; // monster个数
ll f[maxn][maxn * 2]; // f[i][j]表示经过前i只monster，花费j，所能得到的最大dread值之和
class MonstersValley {
	public:
		int minimumPrice(vector<long long> dread, vector <int> price) {
			n = dread.size();
			memset(f, -0x3f, sizeof(f));
			f[0][0] = 0;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j <= 2 * i; ++j) {
					if (f[i][j] >= dread[i]) // 可以选择pass
						f[i + 1][j] = max(f[i + 1][j], f[i][j]);
					f[i + 1][j + price[i]] = max(f[i + 1][j + price[i]], f[i][j] + dread[i]); // bribe这只monster
				}
			for (int j = 0; j <= 2 * n; ++j)
				if (f[n][j] >= 0) return j;
		}
};
