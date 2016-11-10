#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int MaxN = 43;
const int mod = 1000000009;

typedef long long ll;
short p[MaxN * MaxN];
int n, m, comb[MaxN * MaxN][MaxN * MaxN];
int map[MaxN][MaxN];
int deg[MaxN * MaxN], inv[MaxN * MaxN];
int q[MaxN * MaxN * MaxN * MaxN], l, r;
bool v[MaxN][MaxN][MaxN][MaxN];
void push(int a, int b, int c, int d)
{
	if(v[a][b][c][d]) return;
	v[a][b][c][d] = v[c][d][a][b] = 1;
	if(a < c || (a == c && b < d))
		q[r++] = ((a << 8 | b) << 8 | c) << 8 | d;
	else
		q[r++] = ((c << 8 | d) << 8 | a) << 8 | b;
}

const int cx[] = {1, -1, 0, 0};
const int cy[] = {0, 0, 1, -1};

class CoinsGame
{
public:
	int ways(vector<string> input)
	{
		n = input.size();
		m = input[0].size();
		int N = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j)
			{
				if(input[i - 1][j - 1] == '.')
					p[map[i][j] = ++N] = i << 8 | j;
				else
					map[i][j] = -1;
			}
		// 预处理组合数
		comb[0][0] = 1;
		for(int i = 1; i <= N; ++i)
		{
			comb[i][0] = comb[i][i] = 1;
			for(int j = 1; j != i; ++j)
				comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
		}
		// 预处理 pair 是否合法
		// 从结束状态倒着 BFS
		for(int x = 0; x <= n + 1; ++x)
			for(int y = 0; y <= m + 1; ++y)
				if(!map[x][y])
					for(int i = 1; i <= N; ++i)
						push(x, y, p[i] >> 8, p[i] & 255);
		for(int x[2], y[2], X, Y, xx[2], yy[2]; l != r; ++l)
		{
			y[1] = q[l] & 255; q[l] >>= 8;
			x[1] = q[l] & 255; q[l] >>= 8;
			y[0] = q[l] & 255; q[l] >>= 8;
			x[0] = q[l] & 255;
			for(int k = 0; k != 4; ++k)
				for(int set = 1; set != 4; ++set)
				{
					bool f = 1;
					for(int i = 0; i != 2; ++i)
						if(set & (1 << i))
						{
							X = x[i] + cx[k];
							Y = y[i] + cy[k];
							if(X < 0 || Y < 0 || map[X][Y] <= 0) f = 0;
							else xx[i] = X, yy[i] = Y;
						}
						else
						{
							X = x[i] - cx[k];
							Y = y[i] - cy[k];
							if(X < 0 || Y < 0 || map[X][Y] != -1) f = 0;
							else xx[i] = x[i], yy[i] = y[i];
						}
					if(f) push(xx[0], yy[0], xx[1], yy[1]);
				}
		}
		for(int i = 1; i <= N; ++i)
			for(int j = i + 1; j <= N; ++j)
				if(v[p[i] >> 8][p[i] & 255][p[j] >> 8][p[j] & 255])
					++deg[i], ++deg[j];
		
		
		// 到了统计方案数的时候了！
		int ans = 0;
		inv[1] = 1;
		for(int s = 2; s <= N; ++s)
		{
			inv[s] = mod - (ll) (mod / s) * inv[mod % s] % mod;
			ll tmp = 0;
			for(int i = 1; i <= N; ++i)
				tmp += comb[N - 1][s - 1] - comb[N - deg[i] - 1][s - 1];
			ans = (ans + tmp % mod * inv[s]) % mod;
		}
		return (ans + mod) % mod;
	}
}	user;
