#include <algorithm>
#include <math.h>
#include <set>
#include <map>
using namespace std;
const int p = 1000000009;
const int pr_max = 200000;
int w, fn, fx[pr_max], pn, prime[pr_max];
long long fp[pr_max];
bool pr[pr_max + 1];
int tot, num[10000], cov[10000], st[10000][101];
bool ban[10000];
vector<long long> fac;
map<long long, int> id;
class CharacterBoard
{
public:
	void Dfs(int depth, long long x)
	{
		if(depth == fn)
		{
			if(x <= w)
				fac.push_back(x);
		}
		else
		{
			for(int i = 0; i < fx[depth]; i++, x /= fp[depth])
				Dfs(depth + 1, x);
			Dfs(depth + 1, x);
		}
	}
	void Factor(long long x) //求约数 
	{
		long long tmp = x; 
		fn = 0;
		int max_div = (int)sqrt((double)x);
		for(int i = 0; prime[i] <= max_div; i++)
		{
			if(x % prime[i] == 0)
			{
				fx[fn] = 1;
				x /= prime[i];
				while(x % prime[i] == 0)
					x /= prime[i], fx[fn]++;
				fp[fn++] = prime[i];
			}
		}
		if(x > 1)
			fx[fn] = 1, fp[fn++] = x;
		fac.clear();
		Dfs(0, tmp);
	}
	int GetID(long long x)
	{
		auto it = id.find(x);
		if(it != id.end())
			return it->second;
		num[tot] = x;
		return id[x] = tot++;
	}
	void Ban(long long x)
	{
		Factor(x);
		for(unsigned i = 0; i < fac.size(); i++)
			ban[GetID(fac[i])] = true;
	}
	int Find(int *f, int x)
	{
		return f[x] ? f[x] = Find(f, f[x]) : x;
	}
	void Union(long long x, int u, int v)
	{
		Factor(x);
		for(unsigned i = 0; i < fac.size(); i++)
		{
			int id = GetID(fac[i]);
			if(ban[id])
				continue;
			if(Find(st[id], u) != Find(st[id], v)) //合并限制 
			{
				st[id][Find(st[id], u)] = Find(st[id], v);
				cov[id]++;
			}
		}
	}
	int Pow(int x, int y)
	{
		int ret = 1;
		while(y)
		{
			if(y & 1)
				ret = (long long)ret * x % p;
			x = (long long)x * x % p;
			y >>= 1;
		}
		return ret;
	}
	int countGenerators(vector<string> s, int _w, int i0, int j0)
	{
		w = _w;
		for(int i = 2; i <= pr_max; i++)
			pr[i] = true;
		for(int i = 2; i <= pr_max; i++)
		{
			if(!pr[i])
				continue;
			prime[pn++] = i;
			for(int j = i + i; j <= pr_max; j += i)
				pr[j] = false;
		}
		int n = s.size(), m = s[0].size();
		for(int i = 0; i < n; i++)
		{
			for(int j = 0; j < m; j++)
			{
				for(int u = i; u < n; u++)
				{
					for(int v = u > i ? 0 : j + 1; v < m; v++)
					{
						if(s[i][j] != s[u][v]) //排除与限制矛盾的长度 
							Ban(-((long long)(i + i0) * w + (j + j0)) + ((long long)(u + i0) * w + (v + j0)));
						else //合并使限制重合的长度 
							Union(-((long long)(i + i0) * w + (j + j0)) + ((long long)(u + i0) * w + (v + j0)), i * m + j + 1, u * m + v + 1);
					}
				}
			}
		}
		int ans = 0;
		if(w >= n * m)
			ans = (long long)(Pow(26, w - n * m + 1) + p - 1) * Pow(25, p - 2) % p; //限制均不重合的总方案数 
		for(int i = 0; i < tot; i++)
		{
			if(num[i] >= n * m)
				ans = (ans + p - Pow(26, num[i] - n * m)) % p;
			if(!ban[i])
				ans = (ans + Pow(26, num[i] - n * m + cov[i])) % p;
		}
		return ans;
	}
};