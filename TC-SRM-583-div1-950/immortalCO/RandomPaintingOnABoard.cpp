#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

double ans;
int n, m, s;
int map[21][21], sum[21];
int f[4010];

// 容斥枚举不合法的行
void dfs(int i, bool d)
{
	// 处理当前子集
	{
		int all = 0;
		for(int j = 0; j != m; ++j) all += sum[j];
		memset(f + 1, 0, all << 2);
		// all = 0 是全都不满足的情况，因此正负性是要考虑 m 的
		f[all = 0] = ((d ^ m) % 2 ? 1 : -1);
		for(int j = 0, k, v; j != m; ++j)
		{
			v = sum[j];
			// 如果这个不是不合法的，那么用背包统计答案
			// 由于是容斥，因此用减法计算
			for(k = all; k >= 0; --k) f[k + v] -= f[k];
			all += v;
		}
		for(int k = 0; k <= all; ++k) if(f[k] && k != s)
			ans += (double) f[k] / (1.0 - (double) k / s);
	}
	// 枚举下一个不满足的行
	for(; i != n; ++i)
	{
		for(int j = 0; j != m; ++j) sum[j] -= map[i][j];
		dfs(i + 1, !d);
		for(int j = 0; j != m; ++j) sum[j] += map[i][j];
	}
}

class RandomPaintingOnABoard
{
public:
	double expectedSteps(vector<string> inp)
	{
		// 为了节省常数，把 map 拷贝出来
		n = inp.size();
		m = inp[0].size();
		for(int i = 0; i != n; ++i)
			for(int j = 0; j != m; ++j)
				map[i][j] = inp[i][j] - '0';
		if(n > m)
		{
			for(int i = 0; i != n; ++i)
				for(int j = 0; j != m; ++j)
					map[j][i] = inp[i][j] - '0';
			swap(n, m);
		}
		for(int i = 0; i != n; ++i)
			for(int j = 0; j != m; ++j)
			{
				sum[j] += map[i][j];
				s += map[i][j];
			}
		dfs(0, 0);
		return ans;
	}
}	user;
