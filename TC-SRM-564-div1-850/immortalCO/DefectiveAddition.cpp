#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

const int mod = 1e9 + 7;

int f[2][32][2];

void add(int &a, int b) {(a += b) >= mod ? a -= mod : 0;}

int solve(const int N, const int *a, const int V)
{
	bool d = 0;
	// f(i, p, v) ： 考虑到第 i 个数，后面有 j 个自由位置，且右边第 j 个非自由位置的位为 k
	f[d][0][0] = 1;
	int S = 0, tmp;
	for(int i = 0; i != N; ++i)
	{
		const int x = a[i] + 1;
		memset(f[d ^= 1], 0, sizeof f[0]);
		for(int p = 0; p != 32; ++p) for(int v = 0; v != 2; ++v)
			if((tmp = f[!d][p][v])) for(int k = 0; k != 32; ++k) if(x & 1 << k)
			{
				int a, b, c;
				if(k > p) 	a = p, b = k, c = bool(S & 1 << k);
				else 		a = k, b = p, c = bool(v != (p == k ? 0 : bool(x & 1 << p)));
				add(f[d][b][c], ((ll) tmp << a) % mod);
			}
		S ^= x;
	}
	int ans = 0;
	for(int i = 31; i >= 0; --i)
	{
		add(ans, f[d][i][bool(V & 1 << i)]);
		if((S ^ V) >> i) break;
	}
	return ans;
}

class DefectiveAddition
{
public:
	int count(vector<int> lim, int n)
	{
		// 先把 lim 每一位都加上 1，转为小于等于的个数
		// 那么对于每个数，都必然有一位满足其在 lim[i] 中是 1，在最终数组中是 0
		// 后面的位置都是自由的
		return solve(lim.size(), lim.data(), n);
	}
}	user;
