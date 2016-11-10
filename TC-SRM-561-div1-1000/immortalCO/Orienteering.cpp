#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

vector<int> E[2555];
int pid[55][55];
int mark[2555];

void link(int a, int b)
{
	E[a].push_back(b);
	E[b].push_back(a);
}

vector<pair<int, int> > e[2555];
void link(int a, int b, int v)
{
	e[a].push_back(make_pair(b, v));
	e[b].push_back(make_pair(a, v));
}
int mcnt[2555], M, K;
double ans;
bool v[2555];
double subprob[305]; // K 个 关键点全部在一个大小为 t 的集合中的概率
double catprob[305]; // K 个 关键点全部在一个大小为 t+2 的集合中，并且至少存在给定的两个点的概率
// 预处理关键点的虚树，返回子树的虚树的根和距离
pair<int, int> dfs_init(int i)
{
	v[i] = 1;
	mcnt[i] = bool(mark[i]);
	vector<pair<int, int> > branches;
	for(int k = E[i].size(); k--; )
		if(!v[E[i][k]])
		{
			pair<int, int> ret = dfs_init(E[i][k]);
			mcnt[i] += mcnt[E[i][k]];
			if(ret.first) ++ret.second, branches.push_back(ret);
		}
	v[i] = 0;
	if(min(mcnt[i], M - mcnt[i]))
	{
		// 计算这条边被经过的概率（这里要算两次）
		// 没经过的概率：完全在一边的子树里面
		// 设子树大小为 t，完全在里面的概率为
		//  comb(t,k) / comb(m,k)
		ans += 2 * (1 - subprob[mcnt[i]] - subprob[M - mcnt[i]]);
	}
	if(branches.size() >= 2u || mark[i])
	{
		for(int k = 0; k != (int) branches.size(); ++k)
			link(i, branches[k].first, branches[k].second);
		return make_pair(i, 0);
	}
	if(!branches.size()) branches.push_back(make_pair(0, 0));
	return branches.front();
}
int pre[305][305], *Pre;
void dfs_make(int i, int d)
{
	v[i] = 1;
	if(mark[i]) Pre[mark[i] - 1] = d;
	for(int k = e[i].size(); k--; )
		if(!v[e[i][k].first])
			dfs_make(e[i][k].first, d + e[i][k].second);
	v[i] = 0;
}

class Orienteering
{
public:
	double expectedLength(vector<string> inp, int K)
	{
		::K = K;
		const int R = inp.size(), C = inp[0].size();
		int N = 0;
		vector<int> mp;
		for(int i = 0; i != R; ++i)
			for(int j = 0; j != C; ++j)
				if(inp[i][j] != '#')
				{
					pid[i][j] = ++N;
					if(inp[i][j] == '*') mark[N] = ++M, mp.push_back(N);
				}
		for(int i = 0; i != R; ++i)
			for(int j = 0; j != C; ++j)
				if(pid[i][j])
				{
					if(pid[i + 1][j]) link(pid[i][j], pid[i + 1][j]);
					if(pid[i][j + 1]) link(pid[i][j], pid[i][j + 1]);
				}
		// 预处理 subprob
		for(int t = K; t <= M; ++t)
		{
			// 计算系数
			// C(t,k) / C(m,k)
			// P(t,k) / P(m,k)
			double &ret = subprob[t];
			ret = 1;
			for(int i = 0; i != K; ++i)
				ret = ret * (t - i) / (M - i);
		}
		// 预处理 catprob
		for(int s = K - 2; s <= M - 2; ++s)
		{
			double &ret = catprob[s];
			ret = (double) K * (K - 1) / ((M - K + 2) * (M - K + 1));
			for(int i = 0; i != K - 2; ++i)
				ret = ret * (s - i) / (M - i);
		}
		dfs_init(mp.front());
		// 预处理两点之间的距离
		for(int i = 0; i != (int) mp.size(); ++i)
		{
			Pre = pre[i], dfs_make(mp[i], 0);
		}
		// 枚举链上两个点，计算它是最小字典序的最长链的概率
		for(int p = 0; p != (int) mp.size(); ++p)
			for(int q = p + 1; q != (int) mp.size(); ++q)
			{
				const int d = pre[p][q];
				const pair<int, int> cur = make_pair(p, q);
				// 猜想结论：一定是某一个集合的子集
				// 这个集合中，加入任意多个节点，最小字典序最长链都不变
				int s = 0;
				for(int k = 0; k != (int) mp.size(); ++k)
					if(k != p && k != q)
					{
						if(pre[k][p] > d || pre[k][q] > d) continue;
						if(pre[k][p] == d && cur > make_pair(min(k, p), max(k, p))) continue;
						if(pre[k][q] == d && cur > make_pair(min(k, q), max(k, q))) continue;
						++s;
					}
				// 现在取到这个集合的子集的概率为 C(s,k-2) / C(m,k)
				ans -= catprob[s] * d;
			}
		return ans;
	}
}	user;
