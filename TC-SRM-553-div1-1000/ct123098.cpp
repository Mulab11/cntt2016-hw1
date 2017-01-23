#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <ctime>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <typeinfo>

using namespace std;

const long long INF = 1000000000000ll;
const int MAXN = 50 + 10;


class YamanoteLine
{
	public:
	struct Edge
	{
		int next, to;
		pair<long long, int> w;
	}
	e[4 * MAXN];
	int p[2 * MAXN], l;
	void init()
	{
		memset(p, 0, sizeof(p));
		l = 2;
	}
	void addE(int a, int b, pair<long long, int> c)
	{
		e[l].next = p[a];
		e[l].to = b;
		e[l].w = c;
		p[a] = l++;
	}

	int n;
	vector<int> s1, t1, l1, s2, t2, l2;
	pair<long long, int> dis[MAXN];
	int cnt[MAXN], vis[MAXN];
	queue<int> q;

	pair<bool, int> spfa(long long sum)
	{
		init();
		for(int i = 1; i <= n - 1; i++)
			addE(i + 1, i, make_pair(-1, 0));
		addE(1, n, make_pair(sum - 1, 1));
		for(int i = 0; i < s1.size(); i++)
		{
			int s = s1[i] + 1, t = t1[i] + 1, l = l1[i];
			if(t > s) addE(t, s, make_pair(-l, 0));
			else addE(t, s, make_pair(sum - l, 1));
		}
		for(int i = 0; i < s2.size(); i++)
		{
			int s = s2[i] + 1, t = t2[i] + 1, l = l2[i];
			if(t > s) addE(s, t, make_pair(l, 0));
			else addE(s, t, make_pair(l - sum, -1));
		}
		while(!q.empty()) q.pop();
		for(int i = 1; i <= n; i++)
			dis[i] = make_pair(INF, 0), cnt[i] = 0, vis[i] = false;
		dis[1] = make_pair(0, 0), cnt[1]++, vis[1] = true, q.push(1);
		while(!q.empty())
		{
			int x = q.front();
			q.pop();
			vis[x] = false;
			for(int i = p[x]; i; i = e[i].next)
				if(dis[e[i].to].first > dis[x].first + e[i].w.first)
				{
					int y = e[i].to;
					dis[y] = make_pair(dis[x].first + e[i].w.first, dis[x].second + e[i].w.second);
					if(!vis[y])
					{
						cnt[y]++, vis[y] = true;
						q.push(y);
						if(cnt[y] > n)
						{
							return make_pair(false, dis[y].second);
						}
					}
				}
		}
		// cout << dis[n].first << ' ' << sum << endl;
		return make_pair(true, 0);
	}

	long long howMany(int n, vector<int> s1, vector<int> t1, vector<int> l1, vector<int> s2, vector<int> t2, vector<int> l2)
	{
		this->n = n;
		this->s1 = s1, this->t1 = t1, this->l1 = l1;
		this->s2 = s2, this->t2 = t2, this->l2 = l2;

		long long lb, ub, L, R;
		lb = -1, ub = INF;
		L = n, R = INF;
		while(L <= R)
		{
			long long mid = (L + R) / 2;
			pair<bool, int> res = spfa(mid);
			if(res.first || res.second > 0)
			{
				if(res.first) ub = mid;
				L = mid + 1;
			}
			else
				R = mid - 1;
		}
		L = n, R =  INF;
		// cout << "ub = " << ub << endl;
		while(L <= R)
		{
			long long mid = (L + R) / 2;
			pair<bool, int> res = spfa(mid);
			if(res.first || res.second < 0)
			{
					if(res.first) lb = mid;
					R = mid - 1;
			}
			else
				L = mid + 1;
		}
		// cout << "lb = " << lb << endl;
		if(lb >= n && ub == INF)
			return -1;
		if(lb == -1)
			return 0;
		return ub - lb + 1;
	}
};

