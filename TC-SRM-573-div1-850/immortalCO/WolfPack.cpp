#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
const int MaxM = 200010;
int inv[MaxM], fac[2][MaxM];
int count_x[MaxM], count_y[MaxM];

class WolfPack
{
public:
	int calc(vector<int> px, vector<int> py, int m)
	{
		const int n = px.size();
		// 判断无解
		const bool odd = (px[0] + py[0]) & 1;
		for(int i = 0; i != n; ++i)
			if(((px[i] + py[i]) & 1) != odd)
				return 0;
		inv[0] = 	inv[1] = 1;
		fac[0][0] = fac[0][1] = 1;
		fac[1][0] = fac[1][1] = 1;
		for(int i = 2; i <= m; ++i)
		{
			inv[i] = mod - (ll) (mod / i) * inv[mod % i] % mod;
			fac[0][i] = (ll) fac[0][i - 1] * i % mod;
			fac[1][i] = (ll) fac[1][i - 1] * inv[i] % mod;
		}
		// 处理出可以作为终点 (s, t) 的区域
		// 是一个 45° 的矩形
		int min_sum = -1e9, max_sum = 1e9;
		int min_del = -1e9, max_del = 1e9;
#define cmax(a, b) ((a) < (b) ? (a) = (b) : 0)
#define cmin(a, b) ((a) > (b) ? (a) = (b) : 0)
		for(int i = 0; i != n; ++i)
		{
			// |s - x| + |t - y| <= m
			// 四种情况都要满足
			// 1. s - x + t - y <= m -> s + t <= m + x + y
			cmin(max_sum, m + px[i] + py[i]);
			// 2. s - x + y - t <= m -> s - t <= m + x - y
			cmin(max_del, m + px[i] - py[i]);
			// 3. x - s + t - y <= m -> -s + t <= m - x + y -> s - t >= -m + x - y
			cmax(min_del, -m + px[i] - py[i]);
			// 4. x - s + y - t <= m -> -s - t <= m - x - y -> s + t >= -m + x + y
			cmax(min_sum, -m + px[i] + py[i]);
		}
		
		// 现在我们把坐标系转了 45 度 (x,y)->(x+y,x-y)
		// 那么每一个坐标就变成了向某一个斜的方向走一步
		// 那么这样就行列独立啦！
#define ddel(a, b) ((a) > (b) ? (a) - (b) : (b) - (a))
		int tmp;
		int ans_sum = 0;
		for(int sum = min_sum; sum <= max_sum; sum += 2)
		{
			int cur = 1;
			for(int i = 0; i != n; ++i)
			{
				tmp = ddel(px[i] + py[i], sum);
				cur = (ll) cur * fac[0][m] % mod
				* fac[1][(m + tmp) >> 1] % mod
				* fac[1][(m - tmp) >> 1] % mod;
			}
			(ans_sum += cur) %= mod;
		}
		int ans_del = 0;
		for(int del = min_del; del <= max_del; del += 2)
		{
			int cur = 1;
			for(int i = 0; i != n; ++i)
			{
				tmp = ddel(px[i] - py[i], del);
				cur = (ll) cur * fac[0][m] % mod
				* fac[1][(m + tmp) >> 1] % mod
				* fac[1][(m - tmp) >> 1] % mod;
			}
			(ans_del += cur) %= mod;
		}
		
		return (ll) ans_sum * ans_del % mod;
	}
}   user;
