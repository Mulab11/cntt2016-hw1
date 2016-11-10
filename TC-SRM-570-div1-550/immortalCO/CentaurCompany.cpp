#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

// $0 子树中，总共有 $1 个连通块，和 $0 同色的有 $2 个节点、有 $3 个连通块的概率
double f[40][40][40][40];
vector<int> e[40];
bool v[40];

int dp(int i)
{
	v[i] = 1;
	int s = 1;
	// 初始情况
	f[i][1][1][1] = 1;
	for(int _ = e[i].size(); _--; )
	{
		const int k = e[i][_];
		if(v[k]) continue;
		int t = dp(k);
		// 进行转移
		double (*fi)[40][40] = f[i], (*fk)[40][40] = f[k], tmp;
		for(int i1 = s; i1; --i1) for(int i2 = s; i2; --i2) for(int i3 = i1; i3; --i3) if(fi[i1][i2][i3] > 1e-12)
		{
			for(int k1 = t; k1; --k1) for(int k2 = t; k2; --k2) for(int k3 = k1; k3; --k3) if(fk[k1][k2][k3] > 1e-12)
			{
				tmp = 0.5 * fi[i1][i2][i3] * fk[k1][k2][k3];
				fi[i1 + k1 - 1	][i2 + k2		][i3 + k3 - 1	] += tmp;
				fi[i1 + k1		][i2 + (t - k2)	][i3 + (k1 - k3)] += tmp;
			}
			fi[i1][i2][i3] = 0;// 清空数组
		}
		// 更新大小
		s += t;
	}
	return s;
}

// 如果有 a 个连通块，b 个节点
// 那么就有 b 个点度承担 2(a-1) 个点度
int cost(int a, int b) {return max(2 * (a - 1) - b, 0);}

class CentaurCompany
{
public:
	double getvalue(vector<int> ex, vector<int> ey)
	{
		for(int i = 0; i != (int) ex.size(); ++i)
			e[ex[i]].push_back(ey[i]),
			e[ey[i]].push_back(ex[i]);
		int n = dp(1);
		double ans = 0;
		for(int i1 = n; i1; --i1) for(int i2 = n; i2; --i2) for(int i3 = i1; i3; --i3)
		{
			// 连通块个数：i3, i1 - i3
			// 大小：i2, n - i2
			ans += f[1][i1][i2][i3] * (cost(i3, i2) + cost(i1 - i3, n - i2));
		}
		return ans;
	}
}	user;
