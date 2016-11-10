#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 9;

int val[1500], f[1500][1500], h[1500][1500], g[3000][1500];
int inv[1500], fac[1500], inv_fac[1500];
int decode(int w) {return w < 'a' ? w - 'A' : w - 'a' + 26;}

class ColorfulBuilding
{
public:
	int count(vector<string> inpfir, vector<string> inpsec, int m)
	{
		string fir, sec;
		for(int i = 0; i != (int) inpfir.size(); ++i) fir += inpfir[i];
		for(int i = 0; i != (int) inpsec.size(); ++i) sec += inpsec[i];
		const int N = fir.size();
		for(int i = 0; i != N; ++i) val[i + 1] = decode(fir[i]) * 52 + decode(sec[i]);
		inv[0] = inv[1] = 1;
		fac[0] = fac[1] = 1;
		inv_fac[0] = inv_fac[1] = 1;
		for(int i = 2; i <= N; ++i)
		{
			inv[i] = mod - (ll) (mod / i) * inv[mod % i] % mod;
			fac[i] = (ll) fac[i - 1] * i % mod;
			inv_fac[i] = (ll) inv_fac[i - 1] * inv[i] % mod;
		}
		// 记录 f(i, j, k) 表示从大到小用到第 i 个，有 j 段，最低那个的颜色是 k
		// 转移的时候，如果放在的不是第一个，方案数为 (N - i)，直接乘上
		// 否则，如果 k' 和自己不同色，则由 f(i - 1, j - 1, k') 转移
		// 否则从 f(i - 1, j, k) 转移
		// 这样复杂度爆炸了.
		// 我们考虑直接枚举上一个同色的点，那么中间所有点都要放在中间
		// 可以直接计算，那就不用记录 k 了
		f[N][1] = h[N][1] = 1;
		g[val[N]][1] = inv_fac[N - N];
		for(int i = N - 1, M = 1, t, p; i; --i, ++M)
		{
			// 先进行基本转移：1. 作为最小的一个；2. 不作为单调栈中的一个元素
			for(int j = 1; j <= M + 1; ++j)
			{
				f[i][j] = (f[i + 1][j - 1] + (ll) f[i + 1][j] * M) % mod;
				h[i][j] = f[i + 1][j - 1];
			}
			// 另一些情况是 j 不 +1 的，我们考虑一下
			// 前面每一个同色的点 k 贡献的答案是 (N - k + 1) * (N - k + 2) * ... * (N - i - 1)
			// 我们开一个 g(c, j) 记录 f(k | val[k] = c, j) * (N - k)!^-1
			// 然后就可以转移啦！
			int v = val[i];
			p = fac[N - i - 1];
			for(int j = 1; j <= M; ++j)
			{
				// 计算本来应该贡献给 j 的答案，然后从 f[i][j + 1] 从扣除
				t = (ll) g[v][j] * p % mod;
				
				(f[i][j] += t) %= mod;
				(f[i][j + 1] -= t) %= mod;
				(h[i][j] += t) %= mod;
				(h[i][j + 1] -= t) %= mod;
			}
			// 最后再更新 g[v][j]
			p = inv_fac[N - i];
			for(int j = 1; j <= M + 1; ++j)
				g[v][j] = (g[v][j] + (ll) h[i][j] * p) % mod;
		}
		return (f[1][m] + mod) % mod;
	}
}	user;
