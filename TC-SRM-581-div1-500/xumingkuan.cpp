#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cctype>
#include <queue>
#include <map>
#include <set>
using namespace std;
vector<int> concatenate(const vector<string> &vec)
{
	static char buf[10101];
	char *head = buf, *tail = buf;
	for(int i = 0; i < (int)vec.size(); i++)
		tail += sprintf(tail, "%s", vec[i].c_str());
	vector<int> ret;
	while(1)
	{
		char ch = *head++;
		if(head > tail)
			return ret;
		while(ch < '0' || ch > '9')
		{
			ch = *head++;
			if(head > tail)
				return ret;
		}
		int tmp = 0;
		while(ch >= '0' && ch <= '9')
		{
			tmp = tmp * 10 + ch - '0';
			ch = *head++;
		}
		ret.push_back(tmp);
	}
	return ret;
}
class TreeUnion
{
private:
	int n;
	vector<int> fa[2];
	int son[2][310][5];//son[id][i][t]: tree id, point i, number of t-sons (t-son = son of (t-1)-son, 1-son = son)
	int num[2][5];//num[id][t]: tree id, number of chains of length t
	void calc(int id, int len)
	{
		memset(son[id], 0, sizeof(son[id]));
		for(int i = 0; i < n; i++)
			son[id][i][0] = 1;
		for(int t = 1; t <= len; t++)
			for(int i = n - 1; i > 0; i--)
				son[id][fa[id][i]][t] += son[id][i][t - 1];
		memset(num[id], 0, sizeof(num[id]));
		#define check(x) \
		if(t >= (x) && fa[id][tmp] != -1)\
		{\
			num[id][t] += son[id][fa[id][tmp]][t - (x)] - (t >= (x) + 1 ? son[id][tmp][t - (x) - 1] : 0);\
			tmp = fa[id][tmp]
		for(int t = 1; t <= len; t++)
		{
			for(int i = 0; i < n; i++)//chain start at point i
			{
				num[id][t] += son[id][i][t];//lca = i
				int tmp = i;
				check(1);//lca = fa[i]
				check(2);//lca = fa[fa[i]]
				check(3);//lca = fa[fa[fa[i]]]
				check(4);//lca = fa[fa[fa[fa[i]]]]
			}}}}}
			num[id][t] >>= 1;//each chain is counted twice
		}
	}
public:
	double expectedCycles(vector<string> tree1, vector<string> tree2, int K)
	{
		fa[0] = concatenate(tree1);
		fa[0].insert(fa[0].begin(), -1);//father of root = -1
		fa[1] = concatenate(tree2);
		fa[1].insert(fa[1].begin(), -1);
		n = fa[0].size();
		if(K == 3)
			return 0;
		int len = K - 2;//number of tree edge
		calc(0, len - 1);
		calc(1, len - 1);
		long long ans = 0;
		for(int i = 1; i < len; i++)
			ans += (long long)num[0][i] * num[1][len - i];
		return (double)ans * 2 / n / (n - 1);//each pair of chains' probability to form a circle is (1 / C(n, 2)).
	}
};

