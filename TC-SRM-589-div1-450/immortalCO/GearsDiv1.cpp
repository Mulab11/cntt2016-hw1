#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

int N, ans, col[50];
ll e[50], E[50];

__inline__ __attribute__((always_inline)) int dmax(register int a, register int b) {return a > b ? a : b;}
__inline__ __attribute__((always_inline)) void cmax(int &a, register int b) {a < b ? a = b : 0;}
__inline__ __attribute__((always_inline)) bool cmax2(int &a, register int b) {return a < b ? a = b, 1 : 0;}

void dfs(const register ll T, register int C)
{
	// 寻找一个点度最大（可以取的最少的）的点进去
	const register int N = __builtin_popcountll(T);
	if(C + N <= ans) return;
	register int i, p = 0, d = -1;
	for(register ll s = T; s; s -= 1ll << i)
	{
		i = __builtin_ctzll(s);
		if(cmax2(d, N - __builtin_popcountll(T & e[i])))
			p = i;
	}
	if(!d) return cmax(ans, C + N);
	else if(d <= 2)
	{
		// 每个连通块都是环或链，直接贪心
		register ll P = T, Q;
		register int cnt, sum;
		while(P)
		{
			Q = P & -P;
			cnt = sum = 0;
			while(Q)
			{
				i = __builtin_ctzll(Q);
				P -= 1ll << i;
				Q -= 1ll << i;
				Q |= P & E[i];
				
				cnt += 1;
				sum += __builtin_popcountll(T & E[i]);
			}
			sum >>= 1;
			C += ((cnt + (cnt != sum)) >> 1);
		}
		return cmax(ans, C);
	}
	dfs(T & e[p], C + 1);
	dfs(T - (1ll << p), C);
}

class GearsDiv1
{
public:
	int getmin(string inp0, vector<string> inp1)
	{
		N = inp0.size();
		for(int i = 0; i != N; ++i)
			if(inp0[i] == 'R') col[i] = 0;
			else if(inp0[i] == 'G') col[i] = 1;
			else col[i] = 2;
		// 枚举前两种点的颜色，然后跑暴力双搜独立集
		for(int S = 0; S != 8; S += 2)
		{
			memset(e, 0, sizeof e);
			memset(E, 0, sizeof E);
			for(int i = 0; i != N; ++i)
			{
				for(int j = 0; j != N; ++j) if(i != j)
				{
					if(inp1[i][j] == 'N' || (S >> col[i] & 1) != (S >> col[j] & 1))
						e[i] |= 1ll << j;
					else
						E[i] |= 1ll << j;
				}
			}
			dfs((1ll << N) - 1, 0);
		}
		return N - ans;
	}
}	user;
