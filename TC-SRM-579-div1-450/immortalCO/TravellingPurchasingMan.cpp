#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

#include <sstream>
struct Range{int l, r, v;} ran[110];
int e[110][110];
int f[1 << 16][16];

void cmin(int &a, int b) {if(a > b) a = b;}

class TravellingPurchasingMan
{
public:
	int maxStores(int N, vector<string> A, vector<string> B)
	{
		stringstream stream;
		const int M = A.size(), E = B.size();
		for(int i = 0; i != M; ++i) stream << A[i] << ' ';
		for(int i = 0; i != E; ++i) stream << B[i] << ' ';
		for(int i = 0; i != M; ++i)
		{
			stream >> ran[i].l >> ran[i].r >> ran[i].v;
		}
		for(int i = 0; i != N; ++i)
		{
			memset(e[i], 63, N << 2);
			e[i][i] = 0;
		}
		for(int i = 0; i != E; ++i)
		{
			int x, y, v;
			stream >> x >> y >> v;
			e[x][y] = min(e[x][y], v);
			e[y][x] = min(e[y][x], v);
		}
		// Floyd 预处理掉，懒得写那个啥了
		for(int k = 0; k != N; ++k)
			for(int i = 0; i != N; ++i)
				for(int j = 0; j != N; ++j)
					e[i][j] = min(e[i][j], e[i][k] + e[k][j]);
		// 直接 DP
		const int S = 1 << M;
		memset(f, 63, sizeof f);
		int ans = 0;
		for(int i = 0; i != M; ++i)
			if(max(e[N - 1][i], ran[i].l) <= ran[i].r)
				f[1 << i][i] = max(e[N - 1][i], ran[i].l) + ran[i].v;
		for(int s = 0; s != S; ++s)
			for(int p = 0; p != M; ++p)
				if(f[s][p] <= 100000000)
				{
					ans = max(ans, __builtin_popcount(s));
					int val = f[s][p];
					// 考虑下一个去的点
					for(int i = 0; i != M; ++i)
					{
						if(s & 1 << i) continue;
						if(max(val + e[p][i], ran[i].l) > ran[i].r) continue;
						cmin(f[s | 1 << i][i], max(val + e[p][i], ran[i].l) + ran[i].v);
					}
				}
		return ans;
	}
}	user;
