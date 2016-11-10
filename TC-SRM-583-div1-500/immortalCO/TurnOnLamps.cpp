#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;

struct Edge{int to, type;};
// type = -1 必须不取反
// type = 0 随便
// type = 1 必须取反
vector<Edge> e[60];
int f[60][2];
bool v[60];
void cmin(int &a, int b) {a > b ? a = b : 0;}
void dfs(const int i)
{
	v[i] = 1;
	f[i][0] = 0;
	f[i][1] = 0;
	// f[i][j] : i 往下有链的条数的奇偶性
	// 这里只在封闭路径的时候计算费用
	// 因此如果要直接用 f[i][1] 需要 +1
	for(int k = 0; k != (int) e[i].size(); ++k)
		if(!v[e[i][k].to])
		{
			int t = e[i][k].to;
			dfs(t);
			static int g[2];
			memcpy(g, f[i], 8);
			memset(f[i], 63, 8);
			if(e[i][k].type != 1) // 可以不选
			{
				cmin(f[i][0], g[0] + min(f[t][0], f[t][1] + 1));
				cmin(f[i][1], g[1] + min(f[t][0], f[t][1] + 1));
			}
			if(e[i][k].type != -1) // 可以选
			{
				cmin(f[i][0], g[1] + min(f[t][1], f[t][0]) + 1);
				cmin(f[i][1], g[0] + min(f[t][1], f[t][0]));
			}
		}
	v[i] = 0;
}

class TurnOnLamps
{
public:
	int minimize(vector<int> a, string b, string c)
	{
		int n = a.size() + 1;
		for(int i = 0; i + 1 != n; ++i)
			e[a[i]].push_back((Edge) {i + 1, (c[i] == '0') ? 0 : (b[i] == '1') ? -1 : 1});
		dfs(0);
		return min(f[0][0], f[0][1] + 1);
	}
}	user;
