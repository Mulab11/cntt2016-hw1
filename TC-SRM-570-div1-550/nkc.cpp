#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 110
#define D 50
using namespace std;
struct CentaurCompany
{
	int fa[N];
	long long f[N][N][2],g[N][N];
	int to[N],nxt[N],pre[N],cnt;
	void ae(int ff,int tt)
	{
		cnt++;
		to[cnt]=tt;
		nxt[cnt]=pre[ff];
		pre[ff]=cnt;
	}
	//f[i][j]表示以i为根子树（2*连通块-点数=j）的方案数
	//0表示不包含i
	//1表示包含i 
	void dfs(int x)
	{
		int i,j,k,l;
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(j==fa[x]) continue;
			fa[j]=x;
			dfs(j);
		}
		int cnt=0;
		memset(g,0,sizeof(g));
		//求f[i][j][0] 
		g[0][D]=1;
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(j==fa[x]) continue;
			for(k=0;k<=D+D;k++)
			{
				for(l=max(0,D-k);l+k-D<=D+D&&l<=D+D;l++)
				g[cnt+1][l+k-D]+=(f[j][k][0]+f[j][k][1])*g[cnt][l];
			}
			cnt++;
		}
		for(i=0;i<=D+D;i++)
		f[x][i][0]=g[cnt][i];
		memset(g,0,sizeof(g));
		cnt=0;
		//求f[i][j][1] 
		g[0][D+1]=1;
		for(i=pre[x];i;i=nxt[i])
		{
			j=to[i];
			if(j==fa[x]) continue;
			for(k=0;k<=D+D;k++)
			{
				for(l=max(D+2-k,0);l+k-D-2<=D+D&&l<=D+D;l++)
				g[cnt+1][l+k-D-2]+=f[j][k][1]*g[cnt][l];
				for(l=max(0,D-k);l+k-D<=D+D&&l<=D+D;l++)
				g[cnt+1][l+k-D]+=f[j][k][0]*g[cnt][l];
			}
			cnt++;
		}
		for(i=0;i<=D+D;i++)
		f[x][i][1]=g[cnt][i];
	}
	double getvalue(vector <int> a, vector <int> b)
	{
		int n=a.size();
		int i,j;
		for(i=0;i<n;i++)
		{
			ae(a[i],b[i]);
			ae(b[i],a[i]);
		}
		dfs(1);
		double ans=0;
		for(i=D+2;i<=D+D;i++)
		ans+=1.0*(i-D-2)*(f[1][i][0]+f[1][i][1])/(1LL<<n);//除以总方案数 
		return ans;
	}
};
/*CentaurCompany P;
int main()
{
	vector<int>V1,V2;
	V1.push_back(1);
	V1.push_back(2);
	V1.push_back(3);
	V1.push_back(2);
	V1.push_back(2);
	V2.push_back(2);
	V2.push_back(3);
	V2.push_back(4);
	V2.push_back(5);
	V2.push_back(6);
	cout<<P.getvalue(V1,V2);
}*/