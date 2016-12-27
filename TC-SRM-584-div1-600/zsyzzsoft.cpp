#include <algorithm>
#include <memory.h>
using namespace std;
int ws[100001], nxt[51];
bool flag[51];
long long c[51][51];
class Excavations
{
public:
	long long count(vector<int> kind, vector<int> depth, vector<int> found, int k)
	{
		int n = kind.size();
		for(int i = 0; i < found.size(); i++)
			flag[found[i]] = true;
		for(int i = 0; i <= n; i++)
		{
			c[i][0] = c[i][i] = 1;
			for(int j = 1; j < i; j++)
				c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
		}
		for(int i = 0; i < n; i++)
			ws[depth[i]]++;
		for(int i = 1; i <= 100000; i++)
			ws[i] += ws[i - 1];
		for(int i = 0; i < n; i++)
			depth[i] = ws[depth[i]];
		vector<pair<int, int> > v;
		for(int i = 0; i < n; i++)
		{
			if(flag[kind[i]])
				v.push_back(make_pair(kind[i], depth[i]));
		}
		sort(v.begin(), v.end(), [] (pair<int, int> a, pair<int, int> b) {return a.first < b.first || (a.first == b.first && a.second > b.second); });
		nxt[v.size()] = v.size();
		for(int i = v.size() - 1; i >= 0; i--)
		{
			nxt[i] = nxt[i + 1];
			if(i + 1 < v.size() && v[i].first != v[i + 1].first)
				nxt[i] = i + 1;
		}
		long long ans = 0, pre[51] = {0};
		for(int d = n + 1, sum = 0; d >= 0; d--) //枚举未探测到的类型的最小深度 
		{
			for(int i = 0; i < n; i++)
			{
				if(depth[i] == d && !flag[kind[i]])
					sum++;
			}
			long long f[51][51] = {0};
			f[0][0] = 1;
			for(int i = 0; i < v.size(); i++) //背包dp 
			{
				for(int j = 0; j <= v.size(); j++)
				{
					if(!f[i][j])
						continue;
					if(v[i].second < d) //当前类型已经可探测到，可以转移到下一类型 
						f[nxt[i]][j + 1] += f[i][j];
					if(i + 1 < v.size() && v[i + 1].first == v[i].first)
					{
						f[i + 1][j] += f[i][j];
						f[i + 1][j + 1] += f[i][j];
					}
				}
			}
			for(int i = 0; i <= k; i++) //枚举未探测到的数量 
				ans += f[v.size()][k - i] * (c[sum][i] - pre[i]), pre[i] = c[sum][i];
		}
		return ans;
	}
};