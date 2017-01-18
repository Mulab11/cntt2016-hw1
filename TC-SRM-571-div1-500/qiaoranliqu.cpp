#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,ans,val[N],sum,a[N],b[N],tot,vis[N];
void dfs(int x,int s,int m) //直接进行爆搜,使用一些中途剪枝. 
{
		if (s<=ans) return;
		if (x>tot)
		{
				ans=s;
		}
		else 
		{
				if (vis[a[x]]||vis[b[x]]) dfs(x+1,s,m);
				else  if (m>0)
				{
					vis[a[x]]=1;
					dfs(x+1,s-val[a[x]],m-1);
					vis[a[x]]=0;
					
					vis[b[x]]=1;
					dfs(x+1,s-val[b[x]],m-1);
					vis[b[x]]=0;
				}
		}
}
class MagicMolecule{
	public:
		int maxMagicPower(vector <int> magicPower, vector <string> magicBond)
		{
				n=magicPower.size();
				for (i=0;i<n;++i) val[i]=magicPower[i],sum+=val[i];
				ans=-1;
				for (i=0;i<n;++i)
					for (j=i+1;j<n;++j)
						if (magicBond[i][j]=='N') a[++tot]=i,b[tot]=j;
				for (;3*m<2*n;++m);
				dfs(1,sum,n-m); 
				return ans;
		}
};
