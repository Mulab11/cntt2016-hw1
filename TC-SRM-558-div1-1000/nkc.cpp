#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<vector>
#include<map>
#include<set>
#include<bitset>
#include<queue>
#include<stack>
using namespace std;
#define MAXN 10010
#define MAXM 1000010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
struct vec
{
	int to;
	int fro;
	int v;
};
vec mp[MAXM];
int tai[MAXN],cnt=1;
int d[MAXN];
int q[MAXN],hd,tl;
int s,t;
int dx[4]=
{0,0,1,-1};
int dy[4]=
{1,-1,0,0};
int n,m;
int ans;
inline void be(int x,int y,int z)
{
	mp[++cnt].to=y;
	mp[cnt].fro=tai[x];
	tai[x]=cnt;
	mp[cnt].v=z;
}
inline void bse(int x,int y,int z)
{
	be(x,y,z);
	be(y,x,0);
}
bool bfs()
{//最大流 
	int i,x,y;
	memset(d,0,sizeof(d));
	hd=tl=0;
	d[s]=1;
	q[tl++]=s;
	while(hd!=tl)
	{
		x=q[hd++];
		for(i=tai[x];i;i=mp[i].fro)
		{
			y=mp[i].to;
			if(!d[y]&&mp[i].v)
			{
				d[y]=d[x]+1;
				q[tl++]=y;
			}
		}
	}
	return d[t];
}
int dfs(int x,int mx)
{
	if(x==t)
	{
		return mx;
	}
	int i,y,tmp,re=0;
	for(i=tai[x];i;i=mp[i].fro)
	{
		y=mp[i].to;
		if(d[y]==d[x]+1&&mp[i].v)
		{
			tmp=dfs(y,min(mx,mp[i].v));
			mx-=tmp;
			re+=tmp;
			mp[i].v-=tmp;
			mp[i^1].v+=tmp;
			if(!mx)
			{
				return re;
			}
		}
	}
	if(!re)
	{
		d[x]=0;
	}
	return re;
}
int pt(int x,int y,int z)
{
	return z*n*m+x*m+y;
}
int val(char x)
{
	if(x>='0'&&x<='9')
	{
		return x-'0';
	}
	if(x>='a'&&x<='z')
	{
		return x-'a'+10;
	}
	if(x>='A'&&x<='Z')
	{
		return x-'A'+36;
	}
}
struct SurroundingGame
{
	int maxScore(vector<string>c,vector<string>b)
	{
		int i,j,k;
		n=c.size();
		m=c[0].size();
		s=pt(0,0,2);
		t=s+1;
		for(i=0;i<n;i++)
		{//建图 
			for(j=0;j<m;j++)
			{
				bse(pt(i,j,0),pt(i,j,1),val(b[i][j]));
				ans+=val(b[i][j]);
				if(i+j&1)
				{
					bse(s,pt(i,j,0),val(c[i][j]));
					for(k=0;k<4;k++)
					{
						int x=i+dx[k];
						int y=j+dy[k]; 
						if(x>=0&&x<n&&y>=0&&y<m)
						{
							bse(pt(i,j,1),pt(x,y,1),INF);
						}
					}
				}
				else
				{
					bse(pt(i,j,1),t,val(c[i][j]));
					for(k=0;k<4;k++)
					{
						int x=i+dx[k];
						int y=j+dy[k];
						if(x>=0&&x<n&&y>=0&&y<m)
						{
							bse(pt(x,y,0),pt(i,j,0),INF);
						}
					}
				}
			}
		}
		while(bfs())
		{
			ans-=dfs(s,INF);
		}
		return ans;
	}
};
/*

*/