#line 2 "StringPath.cpp"
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
#define clear(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define son e[i].t
#define oo 0x3f3f3f3f
#define maxn 10
#define mo 1000000009
#define maxs 310
typedef long long ll;
using namespace std;
int f[maxn][maxn][maxs][maxs], bit[maxn];
void add(int &a, int b)
{
	a += b; while (a > mo) a -= mo;
}
class StringPath
{
	public:
		int countBoards(int n, int m, string A, string B)
		{
			memset(f, 0, sizeof(f));
			bit[0] = 1; for (int i = 1; i <= m; ++ i) bit[i] = 2 * bit[i - 1];
			f[1][1][bit[0]][bit[0]] = 1;
			for (int i = 1; i <= n; ++ i)
				for (int j = 1; j <= m; ++ j)
					for (int sta = 0; sta < bit[m]; ++ sta)
						for (int stb = 0; stb < bit[m]; ++ stb){
							if (sta == 0 && stb == 0) continue;
							if (! f[i][j][sta][stb]) continue;
							int nsta = sta - (sta & bit[j - 1]), nstb = stb - (stb & bit[j - 1]);
							for (int c = 0; c < 26; ++ c){
								nsta = sta - (sta & bit[j - 1]), nstb = stb - (stb & bit[j - 1]);
								if (c + 'A' == A[i + j - 2] && (((sta & bit[j - 1]) || (j > 1 && (sta & bit[j - 2]))))) nsta += bit[j - 1];
								if (c + 'A' == B[i + j - 2] && (((stb & bit[j - 1]) || (j > 1 && (stb & bit[j - 2]))))) nstb += bit[j - 1];
								if (j == m)
									add(f[i + 1][1][nsta][nstb], f[i][j][sta][stb]);
								else
									add(f[i][j + 1][nsta][nstb], f[i][j][sta][stb]);
							}
						}
			int ans = 0;
			for (int i = 0; i < bit[m - 1]; ++ i)
				for (int j = 0; j < bit[m - 1]; ++ j)
					add(ans, f[n + 1][1][bit[m - 1] + i][bit[m - 1] + j]);
			return ans;
		}
};
