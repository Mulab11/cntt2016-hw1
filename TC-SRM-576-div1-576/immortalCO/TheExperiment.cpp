#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

const int mod = 1e9 + 9;
int sum[310];
int f[310][310][3];

class TheExperiment
{
public:
	int countPlacements(vector<string> inp, int M, int len, int l, int r)
	{
		string val;
		for(int i = 0; i != (int) inp.size(); ++i) val += inp[i];
		// 一个海绵所计算的一定是一段区间
		// 但是不一定会覆盖满整个区间
		int N = val.size();
		for(int i = 1; i <= N; ++i) sum[i] = sum[i - 1] + val[i - 1] - '0';
		// 对于一个山，左边能覆盖的是一个前缀，右边能覆盖的是一个后缀，山顶覆盖的是一整段
		// 0：未开始
		// 1：在爬左边的山峰
		// 2：在爬右边的山峰
		f[0][0][0] = 1;
		int tmp;
		for(int i = 0; i != N; ++i) for(int j = 0; j <= i && j <= M; ++j)
			for(int step = 0; step != 3; ++step) if((tmp = f[i][j][step]))
			{
				if(step != 1) (f[i + 1][j][0] += tmp) %= mod;
				// 枚举下一个区间中露出来的部分
				for(int k = i + 1; k <= N && k <= i + len; ++k)
					if(l <= sum[k] - sum[i] && sum[k] - sum[i] <= r)
					{
						// 考虑转移
						switch(step)
						{
							case 0:
							case 1:
								// 新增一个贡献的是前缀
								if(i + len <= N) (f[k][j + 1][1 + (k == i + len)] += tmp) %= mod;
								break;
							case 2:
								// 新增的是后缀
								(f[k][j + 1][2] += tmp) %= mod;
						}
					}
			}
		int ans = 0;
		for(int i = 0; i <= N; ++i) (ans += f[i][M][2]) %= mod;
		return ans;
	}
}	user;
