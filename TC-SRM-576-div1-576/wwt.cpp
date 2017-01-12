#include <bits/stdc++.h>

using namespace std;

const int maxn = 305;
const int mo = int(1e9) + 9;

class TheExperiment
{
public:
	int ps[maxn],n,a,b,L;

	void decode(vector<string> a)
	{
		string tmp = "";
		n = 0;
		for(int i = 0;i < a.size();i ++) tmp = tmp + a[i];
		for(auto p : tmp)
			ps[++ n] = p - 48,ps[n] += ps[n - 1];
	}

	int f[maxn][maxn][3];//memorized

	int dfs(int now_x,int m,int sta) //sta = 0:no interval now sta=1:there are intervals,but none of whose length is L,sta=2:some interval's length is L
	{
		if (~f[now_x][m][sta]) return f[now_x][m][sta];
		if (now_x > n)
			return ((m == 0) && (sta != 1));
		int tmp = 0;
		if (m)
		{	
			for(int l = 1;l <= L;l ++) //the length of the interval
			{
				if (now_x + l - 1 > n) break;
				int ss = ps[now_x + l - 1] - ps[now_x - 1];
				if (ss >= a && ss <= b)
				{
					int nsta = (l == L) ? 2 : (!sta ? 1 : sta);
					tmp = (tmp + dfs(now_x + l,m - 1,nsta)) % mo;
				}
			}
		}
		if (sta != 1) tmp = (tmp + dfs(now_x + 1,m,0)) % mo;//no interval covers now_x
		return f[now_x][m][sta] = tmp;
	}

	int countPlacements(vector <string> intensity, int M, int l, int A, int B)
	{
		a = A,b = B,L = l;
		decode(intensity);
		memset(f,255,sizeof f);
		return dfs(1,M,0);
	}
};
