#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<iomanip>
#include<cmath>
#include<cstring>
#include<ctime>
#include<vector>
#include<stack>
#include<queue>
#include<set>
#include<bitset>
#include<map>
using namespace std;
#define MAXN 10010
#define MAXM 10010
#define INF 1000000000
#define MOD 1000000007
#define ll long long 
#define eps 1e-8
struct vec
{
    int to;
    int fro;
    int v;
};
vec mp[MAXM];
int tai[MAXN],cnt=1;
int q[MAXM],hd,tl;
bool iq[MAXN];
int dis[MAXN];
int st[MAXM],ed[MAXM],ln[MAXM];
int tot;
int s,t;
int cur[MAXN];
int d[MAXN];
inline void be(int x,int y,int z)
{
    mp[++cnt].to=y;
    mp[cnt].fro=tai[x];
    tai[x]=cnt;
    mp[cnt].v=z;
}
inline void bde(int x,int y,int z)
{
    be(x,y,z);
    be(y,x,z);
}
inline void bse(int x,int y,int z)
{
    be(x,y,z);
    be(y,x,0);
}
bool bfs()
{//dinic求最大流 
    int i,x,y;
    hd=tl=0;
    q[tl++]=s;
    memset(d,0,sizeof(d));
    d[s]=1;
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
    int y;
    int re=0,tmp;
    for(int i=tai[x];i;i=mp[i].fro)
{
        y=mp[i].to;
        if(d[y]==d[x]+1&&mp[i].v)
{
            tmp=dfs(y,min(mx,mp[i].v));
            re+=tmp;
            mx-=tmp;
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
int n,a1,a2,b1,b2,an,bn;
char dt[60][60];
void build()
{//建图函数 
	int i,j;
	memset(tai,0,sizeof(tai));
	cnt=1;
	for(i=1;i<=n;i++)
	{
		for(j=i+1;j<=n;j++)
		{
			if(dt[i][j]=='N')
			{
				bde(i,j,INF);
			}
			if(dt[i][j]=='O')
			{
				bde(i,j,2);
			}
		}
	}
}
struct OldBridges
{
	string isPossible(vector<string>_mp,int a1,int a2,int an,int b1,int b2,int bn)
	{
		int i,j;
		n=_mp.size();
		a1++;
		a2++;
		b1++;
		b2++;
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=n;j++)
			{
				dt[i][j]=_mp[i-1][j-1];
			}
		}
		int ans=0;
		s=n+1;
		t=s+1;
		build();
		bse(s,a1,2*an);
		bse(a2,t,2*an);
		bse(s,b1,2*bn);
		bse(b2,t,2*bn);//第一次建图 
		ans=0;
		while(bfs())
		{
			ans+=dfs(s,INF);
		}
		bool flag=0;
		if(ans!=2*(an+bn))
		{
			flag=1;
		}
		if(!flag)
		{
			build();
			bse(s,a1,2*an);
			bse(a2,t,2*an);
			bse(s,b2,2*bn);
			bse(b1,t,2*bn);//第二次建图 
			ans=0;
			while(bfs())
			{
				ans+=dfs(s,INF);
			}
			if(ans!=2*(an+bn))
			{
				flag=1;
			}
		}
		return flag?"No":"Yes";
	}
};