#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

const int mod = 1e9 + 9;

#include <map>
int C, N;
map<pair<int, vector<int> >, int> mem;
int cap[20];
bool v[20][60];
int vl[20], vr[20];

void cmax(int &a, int b) {a < b ? a = b : 0;}
int dp(int i, const vector<int>& vec)
{
	if(i == N) return 1;
	// 提取记忆化
	if(!mem.empty())
	{
		map<pair<int, vector<int> >, int>::iterator k = mem.find(make_pair(i, vec));
		if(k != mem.end()) return k->second;
	}
	// 计算答案，枚举当前这个放在哪里
	int ans = 0;
	const int V = cap[i], *arr = vec.data();
	const bool *v = ::v[i];
	vector<int> next;
	for(int p = 0; p != C; ++p)
	{
		if(vl[i] <= p - V || p + V <= vr[i]) continue;
		// 判断是否和 v 的情况相同
		for(int k = 0; k != V; ++k)
		{
			if(p - k >= 0 && v[p - k] != ((V - k) > arr[p - k])) goto skipped;
			if(p + k <  C && v[p + k] != ((V - k) > arr[p + k])) goto skipped;
		}
		// 修改状态，递归处理
		next = vec;
		for(int k = 0; k != V; ++k)
		{
			if(p - k >= 0) cmax(next[p - k], V - k);
			if(p + k <  C) cmax(next[p + k], V - k);
		}
		(ans += dp(i + 1, next)) %= mod;
	skipped: continue;
	}
	mem.insert(make_pair(make_pair(i, vec), ans));
	return ans;
}

class Mountains
{
public:
	int countPlacements(vector<int> height, vector<string> vis)
	{
		// 直接记忆化每一列的最大值，爆搜！
		C = vis[0].size();
		N = height.size();
		for(int i = 0; i != N; ++i)
		{
			cap[i] = height[N - i - 1];
			vl[i] = 10000, vr[i] = -10000;
			for(int j = 0; j != C; ++j)
				if((v[i][j] = vis[N - i - 1][j] == 'X'))
				{
					vl[i] = min(vl[i], j);
					vr[i] = max(vr[i], j);
				}
		}
		return dp(0, vector<int>(C, 0));
	}
}	user;
