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

#define N 105
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,g[N][N],sg[N],fa[N];
vector<int>v[N];
int sqr(int x)
{
		return x*x;
}
void add(int x,int y)
{
		v[x].pb(y);
}
void dfs(int x)
{
	 int now=0,i;
	 for (i=0;i<(int)v[x].size();++i)
	 {
	 		int p=v[x][i];
	 		dfs(p);
	 		now^=sg[p];
	 }
	 g[x][now]=1;
	 for (i=0;i<(int)v[x].size();++i)
	 {
	 		  int p=v[x][i];
	 		  for (j=0;j<N;++j)
	 		    if (g[p][j]) g[x][now^sg[p]^j]=1;
	 }
	 for (j=0;g[x][j];++j); sg[x]=j;
}
class CirclesGame{
	public:
		string whoCanWin(vector <int> x, vector <int> y, vector <int> r)
		{
			 n=x.size();
			 for (i=0;i<n;++i) //建出树形结构 
			{
					fa[i]=i;
					for (j=0;j<n;++j)
						if (i!=j&&r[j]>sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]))+r[i])
							if (fa[i]==i||r[fa[i]]>r[j]) fa[i]=j;
			}
			for (i=0;i<n;++i)	if (fa[i]!=i) add(fa[i],i);
			for (i=0;i<n;++i)	if (fa[i]==i) dfs(i); //对于每个树计算sg值 
			int ans=0;
			for (i=0;i<n;++i)
			if (fa[i]==i) ans^=sg[i];
			return ans?"Alice":"Bob"; 
		}
};
