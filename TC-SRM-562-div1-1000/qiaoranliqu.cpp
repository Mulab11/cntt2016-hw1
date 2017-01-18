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

#define N 45
#define M 200005
#define seed 23333
#define Mo 1000000009

using namespace std;
int i,j,m,n,p,k,ans,fa[N],vis[N],size[N],f[N],C[N][N];
int deep[N];
vector<int>v[N];
void add(int x,int y)
{
		v[x].pb(y);
		v[y].pb(x);
}
void jia(int &x,int y)
{
		x+=y; if (x>=Mo) x-=Mo;
}
void dfs(int x)
{
		int i;
		for (i=0;i<(int)v[x].size();++i)
		{
				int p=v[x][i];
				if (fa[x]==p) continue;
				fa[p]=x; deep[p]=deep[x]+1;
				dfs(p);
		}
}
void Dfs(int x)
{
		int i;
		vis[x]=1;
		for (i=0;i<(int)v[x].size();++i)
		{
				int p=v[x][i];
				if (vis[p]) continue;
				Dfs(p);
				size[x]+=size[p];
		}
		size[x]++;
}
void work(int x)
{
		vis[x]=2;
		int i,used=0;
		f[x]=1;
		for (i=0;i<(int)v[x].size();++i)
		{
				int p=v[x][i];
				if (vis[p]==2) continue;
				work(p);
				used+=size[p];
				f[x]=1ll*f[x]*f[p]*C[used][size[p]]%Mo; //计算答案,标号用组合数分配 
		} 
}
void workA() 
{
		dfs(0); 
		for (i=0;i<n;++i) //当2*k<=n时,中间存在一条链,两边分别是两棵父亲标号大于孩子的树,不妨枚举两棵子树的根 
			for (j=0;j<n;++j)
				if (i!=j)
				{
						memset(vis,0,sizeof(vis));
						memset(size,0,sizeof(size)); 
						memset(f,0,sizeof(f));
						int x=i,y=j,s=-1;
						while (x!=y)
						{	
							if (deep[x]>deep[y]) vis[x]=2,++s,x=fa[x];
							else vis[y]=2,++s,y=fa[y];
						}
						vis[x]=2;
						if (s!=n-2*k) continue;
						Dfs(i); 
						vis[i]=vis[j]=2; 
						Dfs(j);
						if (size[i]!=k||size[j]!=k) continue; //判断中间是否成链即两边的size是否对 
						vis[i]=vis[j]=2;
						work(i);
						vis[i]=vis[j]=2;
						work(j);
						jia(ans,1ll*f[i]*f[j]%Mo);
				}
}
int fac(int x)
{
		int s=1,i;
		for (i=1;i<=x;++i) s=1ll*s*i%Mo;
		return s;
}
int g[N][N][N];
int merge(int x)
{
		vis[x]=1; size[x]=0;
		int i,sum=1;
		for (i=0;i<(int)v[x].size();++i)
		{
				int p=v[x][i];
				if (vis[p]) continue;
				sum=1ll*sum*merge(p)%Mo*C[size[x]+size[p]][size[p]]%Mo;
				size[x]+=size[p];
		}
		size[x]++;
		return sum;
}
int in[N],out[N],h[N][N];
void gao(int x)
{	
	int i,j,k,l,y;
	vis[x]=1;
	g[x][0][0]=1;	size[x]=1;
	for (i=0;i<(int)v[x].size();++i)
	{
			int p=v[x][i];
			if (vis[p]) continue;
			gao(p);
			memset(h,0,sizeof(h));
			for (j=size[x];j>=0;--j)
				for (k=size[x];k>=0;--k)
					if (g[x][j][k])
					{
							if(j+size[p]<=n-::k)
							jia(h[j+size[p]][k],1ll*g[x][j][k]*in[p]%Mo*C[size[p]+j][size[p]]%Mo);
							if(k+size[p]<=n-::k)
							jia(h[j][k+size[p]],1ll*g[x][j][k]*in[p]%Mo*C[size[p]+k][size[p]]%Mo);
							for (l=size[p];l>=0;--l)
								for (y=size[p];y>=0;--y)
									if (g[p][l][y])
									jia(h[j+l][k+y],1ll*g[x][j][k]*g[p][l][y]%Mo*C[j+l][l]%Mo*C[k+y][y]%Mo);
					}
			memcpy(g[x],h,sizeof(h));
			size[x]+=size[p];
	}
}
void workB() //2*k>n时[n-k+1,k]形成一个联通块,其他都为一些分散的子树 
{
		int i,j,k;
		dfs(0);
		for (i=0;i<n;++i) //预处理每个点子树或子树外构成一棵大根树的方案 
		{
				memset(vis,0,sizeof(vis));
				vis[fa[i]]=1;
				in[i]=merge(i);
				vis[fa[i]]=0;
				out[i]=merge(i);
		}
		memset(vis,0,sizeof(vis));
		gao(0); //计算f_{i,j,l}表示以i为根的子树里有j个[1,n-k]的点,l个[k+1,n]里点的方案 
		for (i=0;i<n;++i)   //枚举[n-k+1,k]中深度最浅的点 
			for (j=0;j<=n;++j)
				for (k=0;k<=n;++k)
					if (g[i][j][k]&&size[i]-j-k==2*::k-n)
					{
						if (j+(n-size[i])==n-::k) jia(ans,1ll*g[i][j][k]*out[i]%Mo*C[n-::k][j]%Mo);
						if (size[i]<n&&k+(n-size[i])==n-::k) jia(ans,1ll*g[i][j][k]*out[i]%Mo*C[n-::k][k]%Mo);
					}
		ans=1ll*ans*fac(2*::k-n)%Mo; //中间点可以乱标号 
}
class InducedSubgraphs{
	public:
		int getCount(vector <int> edge1, vector <int> edge2, int k)
		{
			::k=k;
			n=edge1.size()+1;
			if (k==1) return fac(n);
			for (i=0;i<n-1;++i) add(edge1[i],edge2[i]);
			for (i=0;i<N;++i)
			{
				 C[i][0]=1;
				 for (j=1;j<=i;++j) C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mo;
			}
			if (2*k<=n) workA(); 
			else workB();
			return ans; 
		}
}E;

int main()
{
	 cout<<E.getCount({0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6},{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14},11);
}
