#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

const int mod = 1e9 + 7;

int f[2][1500];
int comb[1500][50];

class LISNumber
{
public:
	int count(vector<int> cnt, int M)
	{
		comb[0][0] = 1;
		for(int i = 1; i != 1500; ++i)
		{
			comb[i][0] = 1;
			for(int j = 1; j <= i && j != 50; ++j)
				comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
		}
		
		const int N = cnt.size();
		bool d = 0;
		f[d][cnt[0]] = 1;
		
		for(int i = 1, sum = cnt[0]; i != N; ++i)
		{
			const int C = cnt[i];
			d ^= 1;
			memset(f[d], 0, sizeof f[d]);
			// 枚举当前这个数字会让贡献加上多少
			// 设没贡献的数字为 num，考虑它对 f[i] 的贡献
			// 没有贡献，必然是加在某个段的末尾
			// 方案数为 comb[i][num]
			// 剩下有贡献的呢？
			// 先把这 num 个加进去
			// 然后把剩下 C - num 个一起加入
			// 现在有 sum - (i - num) + 1 个会使得贡献加一的槽
			// 利用插板法，方案数为 comb[C - num + sum - i + num][C - num]
			for(int num = 0; num <= C; ++num)
				for(int i = num; i <= sum && i + C - num <= M; ++i) if(f[!d][i])
					f[d][i + C - num] = (f[d][i + C - num] + (ll) comb[i][num] % mod * comb[C + sum - i][C - num] % mod * f[!d][i]) % mod;
			sum += C;
		}
		return f[d][M];
	}
}	user;
