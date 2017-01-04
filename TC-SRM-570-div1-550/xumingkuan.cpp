#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <cctype>
#include <queue>
#include <map>
using namespace std;
const double EPS = 1e-12;
template <int negsize, int possize, class T = int> class Negative_array
{
private:
	T a[negsize + possize];
public:
	void clear(int val = 0)
	{
		memset(a, val, sizeof(a));
	}
	Negative_array()
	{
		clear();
	}
	T &operator [](int x)
	{
		return a[x + negsize];
	}
	const T &operator [](int x) const
	{
		return a[x + negsize];
	}
};
class Edge
{
public:
	int to, next;
};

class CentaurCompany
{
private:
	Negative_array <40, 40, double> f[40][2], tmpf[2];//f[i][0/1][j]: subtree i, choose i or not, j = (2 * (block - 1) - point), possibility
	Edge e[80];
	int n, head[40], en;
	bool visit[40];
	int mnv[40], mxv[40];//range of f[i]
	void insert(int u, int v)
	{
		e[++en].to = v;
		e[en].next = head[u];
		head[u] = en;
		e[++en].to = u;
		e[en].next = head[v];
		head[v] = en;
	}
	void dfs(int p)
	{
		visit[p] = true;
		f[p][0][-2] = f[p][1][-1] = 0.5;
		mnv[p] = -2;
		mxv[p] = -1;
		for(int i = head[p]; i > 0; i = e[i].next)
			if(!visit[e[i].to])
			{
				dfs(e[i].to);
				for(int j = mnv[p]; j <= mxv[p]; j++)//copy and clear
				{
					tmpf[0][j] = f[p][0][j], tmpf[1][j] = f[p][1][j];
					f[p][0][j] = f[p][1][j] = 0;
				}
				int nowmnv = mnv[p], nowmxv = mxv[p];
				for(int t1 = 0; t1 <= 1; t1++)
					for(int j1 = mnv[p]; j1 <= mxv[p]; j1++)
						if(tmpf[t1][j1] >= EPS)
						{
							const double now = tmpf[t1][j1];
							for(int t2 = 0; t2 <= 1; t2++)
								for(int j2 = mnv[e[i].to]; j2 <= mxv[e[i].to]; j2++)
									if(f[e[i].to][t2][j2] >= EPS)
									{
										const int tmp = j1 + j2 + 2 * (!t1 || !t2);
										if(tmp < nowmnv)
											nowmnv = tmp;
										if(tmp > nowmxv)
											nowmxv = tmp;
										f[p][t1][tmp] += now * f[e[i].to][t2][j2];
									}
						}
				mnv[p] = nowmnv;
				mxv[p] = nowmxv;
			}
	}
public:
	double getvalue(vector<int> a, vector<int> b)
	{
		memset(head, -1, sizeof(head));
		en = 1;
		n = a.size() + 1;
		for(int i = 0; i < n - 1; i++)//build tree
			insert(a[i], b[i]);
		memset(visit, false, sizeof(visit));
		dfs(1);
		//printf("[%d, %d]\n", mnv[1], mxv[1]);
		double ans = 0;
		for(int i = 1; i <= mxv[1]; i++)
			ans += (f[1][0][i] + f[1][1][i]) * i;//get expectation
		ans *= 2;//two companies
		return ans;
	}
};

