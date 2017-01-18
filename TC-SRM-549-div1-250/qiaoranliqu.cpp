#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 55
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,vis[N],match[N],ans;
vector<int>v[N]; 
bool dfs(int x)
{
		int i;
		for (i=0;i<(int)v[x].size();++i)
		{
				int p=v[x][i];
				if (vis[p]) continue;
				vis[p]=1;
				if (match[p]==-1||dfs(match[p]))
				{
					  match[p]=x;
					  return 1;
				} 
		}
		return 0;
}
class PointyWizardHats{
	public:
		int getNumHats(vector <int> tH, vector <int> tR, vector <int> bH, vector <int> bR)
		{
			   n=tH.size(); m=bH.size();
			   memset(match,-1,sizeof(match));
			   for (i=0;i<n;++i) //判断两顶帽子是否合法 
			   		for (j=0;j<m;++j)
					   	if (tR[i]<bR[j]&&tH[i]*bR[j]>bH[j]*tR[i]) v[i].pb(j); 
			   for (i=0;i<n;++i) //进行匹配 
			{
					memset(vis,0,sizeof(vis));
					if (dfs(i)) ++ans;
			}
			return ans;
		}
};

