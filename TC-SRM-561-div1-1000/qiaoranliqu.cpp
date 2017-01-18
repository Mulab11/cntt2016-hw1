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

#define N 2505
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
double C[305][305],ans;
int ax[4]={0,0,-1,1};
int ay[4]={-1,1,0,0};
bool vis[N][N];
int i,j,m,n,p,k,root,tot=-1,big[N],sz[N],dis[N][N],K,nn;
char c[N][N];
vector<int>v[N];
void add(int x,int y)
{
		v[x].pb(y);
		v[y].pb(x);
}
int check(int x,int y)
{
	if (x<0||y<0||x>=n||y>=m||vis[x][y]||c[x][y]=='#') return 0;
	return 1;
}
int dfs(int x,int y)
{
		vis[x][y]=1;
		int now=++tot,i;
		if (c[x][y]=='*') big[tot]=1,++nn;
		for (i=0;i<4;++i)
			if (check(x+ax[i],y+ay[i])) 
					add(now,dfs(x+ax[i],y+ay[i]));
		return now;
}
void work(int x,int y)
{
	  int i;
	  for (i=0;i<(int)v[x].size();++i)
	  {
	  		int p=v[x][i];
	  		if (p==y) continue;
	  		work(p,x);
	  		sz[x]+=sz[p];
	  }
	  sz[x]+=big[x];
}
void gao(int x,int *dis,int y)
{
		int i;
		for (i=0;i<(int)v[x].size();++i)
		{
				int p=v[x][i];
				if (p==y) continue;
				dis[p]=dis[x]+1;
				gao(p,dis,x);
		}
}
void cnbb(int x,int y)
{
		int i;
		for (i=0;i<(int)v[x].size();++i)
		{
				int p=v[x][i];
				if (p==y) continue;
				cnbb(p,x);
				ans+=1.-(C[sz[p]][K]+C[sz[0]-sz[p]][K])/C[nn][K]; //容斥减去所有选择点在这条边同侧的情况 
		}
}
class Orienteering{
	public:
	double expectedLength(vector <string> field, int K)
	{
			::K=K;
			n=field.size(); m=field[0].length();
			for (i=0;i<n;++i)
				for (j=0;j<m;++j) c[i][j]=field[i][j];
			for (i=0;i<n;++i) 
				for (j=0;j<m;++j) 
					if (!vis[i][j]&&c[i][j]!='#')
							root=dfs(i,j);
			for (i=0;i<=300;++i)
			{ 
				    C[i][0]=1;
					for (j=1;j<=i;++j) C[i][j]=C[i-1][j]+C[i-1][j-1];
			}
			n=tot+1;
			work(0,-1);//计算每个点子树里关键点的个数 
			for (i=0;i<n;++i) if (big[i]) gao(i,dis[i],-1); //预处理从每个关键点出发到每个点的距离 
			cnbb(0,-1);
			ans*=2;
			for (i=0;i<n;++i)
				if (big[i])
				for (j=i+1;j<n;++j)
					if (big[j])
				{
					  int could=0;
					  for (k=0;k<n;++k)
					  	if (k!=i&&k!=j&&big[k])
					  	{
					  		if (max(dis[i][k],dis[j][k])>dis[i][j]) continue;
					  		if (dis[i][k]==dis[i][j]&&k<j) continue;
					  		if (dis[j][k]==dis[i][j]&&k<i) continue;
					  		++could; //计算有多少点在(i,j)作为直径时可选 
					  	}
					  ans-=dis[i][j]*C[could][K-2]/C[nn][K];
				}
			return ans;
	}
}G;

int main()
{
	cout<<G.expectedLength({"*#..#",".#*#.","*...*"},2);	
}
