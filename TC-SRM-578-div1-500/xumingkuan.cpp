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
const int MOD = 1000000007;
const int MAXN = 310;
const int MAXM = 310;
bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
	return a.first == b.first ? a.second > b.second : a.first < b.first;
}
class WolfInZooDivOne
{
private:
	vector<int> concatenate(const vector<string> &vec)
	{
		static char buf[10101];
		char *head = buf, *tail = buf;
		for(int i = 0; i < vec.size(); i++)
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
	vector<int> l, r;
	int m;
	int f[MAXN][MAXN];//f[i][j]: interval [1, i], the SECOND LAST wolf's place is <= j, number of ways in which wolves can be distributed in the sections of the road
	pair<int, int> a[MAXM];
public:
	int count(int N, vector<string> L, vector<string> R)
	{
		l = concatenate(L);
		r = concatenate(R);
		m = l.size();
		for(int i = 0; i < m; i++)
			a[i] = make_pair(l[i] + 1, r[i] + 1);//combine L and R and increase the number by 1 (in range [1, n])
		sort(a, a + m, cmp);//sort by l ascend then r descend, as the code in 'cmp'
		int tmp = 0;
		for(int i = 0; i < m; i++)
			if(!i || a[i].second > a[i - 1].second)//a[i] is useful
				a[tmp++] = a[i];
		m = tmp;//remove useless information
		a[m].first = N + 1;//for convenience
		int ptr = 0;
		memset(f, 0, sizeof(f));
		f[0][0] = 1;
		for(int i = 1; i <= N; i++)
		{
			while(ptr < m && a[ptr].second < i)
				ptr++;
			for(int j = 0; j < i; j++)
				f[i][j] = (f[i - 1][j] + f[j][min(j, a[ptr].first - 1)]) % MOD;//if there isn't wolf at i: f[i - 1][j]; else: f[j][a[ptr].first - 1];
			f[i][i] = f[i][i - 1];
		}
		return f[N][N];
	}
};

