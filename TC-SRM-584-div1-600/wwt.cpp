#include <bits/stdc++.h>

using namespace std;

const int maxn = 55;

typedef long long ll;

ll f[maxn][maxn][maxn];//consider the ith kind,the maximum depth chosen before is j,k positions can be chosen
ll c[maxn][maxn];

class Excavations
{
public:
	int ord[maxn],kind_cnt; //relabel kind,so that we can do dp easily

	void relabel(vector<int> &a)
	{
		static int co[100005];
		memset(co,0,sizeof co);
		for(auto p : a) co[p] = 1;
		for(int i = 1;i <= 100000;i ++) co[i] += co[i - 1];
		for(int i = 0;i < a.size();i ++) a[i] = co[a[i] - 1];
	}

	long long count(vector<int> kind,vector<int> depth,vector<int> found,int K)
	{
		int n = kind.size();
		relabel(depth);
		memset(ord,0,sizeof ord);
		kind_cnt = 0;
		for(auto p : found) ord[p] = ++ kind_cnt;
		int good_cnt = kind_cnt;
		for(int i = 1;i <= 50;i ++) if (!ord[i]) ord[i] = ++ kind_cnt;
		for(int i = 0;i <= 50;i ++)
		{
			c[i][0] = 1;
			for(int j = 1;j <= i;j ++) c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
		}
		vector<int> ava[55]; //t he depths that kind i possesses.
		for(int i = 0;i < n;i ++) ava[ord[kind[i]] - 1].push_back(depth[i]);
		f[0][0][0] = 1;
		for(int i = 0;i < 50;i ++)
		{
			sort(ava[i].begin(),ava[i].end()),reverse(ava[i].begin(),ava[i].end());
			for(int maxdep = 0;maxdep < n;maxdep ++)
				for(int extra = 0;extra <= n;extra ++)
					if (f[i][maxdep][extra])
					{
						if (i < good_cnt) //select a lowest depth
						{
							for(int j = 0;j < ava[i].size();j ++)
								f[i + 1][max(maxdep,ava[i][j])][extra + j] += f[i][maxdep][extra];
						} else
						{
							int far = 0;
							for(;far < ava[i].size() && ava[i][far] > maxdep;far ++);
							f[i + 1][maxdep][extra + far] += f[i][maxdep][extra];
						}
					}							
		}
		long long ans = 0;
		for(int maxdep = 0;maxdep < n;maxdep ++)
			for(int extra = 0;extra <= n;extra ++)
				ans += f[50][maxdep][extra] * c[extra][K - found.size()]; //we can choose another K - |found| items
		return ans;
 	}
};
