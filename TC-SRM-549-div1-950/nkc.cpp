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
#define MAXN 20
#define MAXM 1010
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
int tai[MAXN],cnt;
int n;
int num[MAXN];
int L,R;
int lev[MAXN];
bool has[MAXN];
int ans;
int tot;
int flow,sum;
int v1[MAXN],v2[MAXN];
bool used[MAXN];
int p[MAXN],deg[MAXN];
vector<int>MP[MAXN];
int c;
int io[MAXN];
int s;
int t;
int S,T;
int q[MAXN],hd,tl;
int d[MAXN];
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
{  
    int i,x,y;  
    memset(d,0,sizeof(d));  
    d[s]=1;  
    hd=tl=0;  
    q[tl++]=s;  
    while(hd!=tl)
{  
        x=q[hd++];  
            for(i=tai[x];i;i=mp[i].fro)
{  
            y=mp[i].to;  
            if(mp[i].v&&(!d[y]))
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
    int i,y,tt;  
    int re=0;  
    for(i=tai[x];i;i=mp[i].fro)
{  
        y=mp[i].to;  
        if(d[y]==d[x]+1&&mp[i].v)
{  
            tt=dfs(y,min(mx,mp[i].v));  
            mp[i].v-=tt;  
            mp[i^1].v+=tt;  
            mx-=tt;  
            re+=tt;  
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
void Dfs(int x)
{
	int i,j;
	if(x>n)
	{
		c++;
		/*
		for(i=1;i<=n;i++)
		{
			cerr<<p[i]<<' ';
		}
		cerr<<endl;
		//*/
		return ;
	}
	for(i=1;i<=n;i++)
	{
		if(!used[i]&&!deg[i])
		{
			used[p[x]=i]=1;
			for(j=0;j<MP[i].size();j++)
			{
				deg[MP[i][j]]--;
			}
			Dfs(x+1);
			used[i]=0;
			for(j=0;j<MP[i].size();j++)
			{
				deg[MP[i][j]]++;
			}
		}
	}
}
bool chk()
{
	flow=0;
	int i;
	cnt=1;
	memset(tai,0,sizeof(tai));
	memset(io,0,sizeof(io));
	S=n*2+1+1;
	T=S+1;
	s=T+1;
	t=s+1;
	for(i=1;i<=tot;i++)
	{
		bse(v1[i],n+v2[i],num[v1[i]]-1);
		io[n+v2[i]]++;
		io[v1[i]]--;
	}
	for(i=1;i<=n;i++)
	{
		io[i]+=num[i];
		if(lev[i]==1)
		{
			bse(i,n+n+1,num[i]-1);
			io[n+n+1]++;
			io[i]--;
		}
	}
	io[S]-=sum;
	num[n+1]=INF;
	for(i=1;i<=n+1;i++)
	{
		bse(n+i,T,num[i]);
	}
	int tt=cnt+2;
	bse(T,S,INF);
	int tc=0;
	for(i=1;i<=T;i++)
	{
		if(io[i]>0)
		{
			tc+=io[i];
			bse(s,i,io[i]);
		}
		if(io[i]<0)
		{
			bse(i,t,-io[i]);
		}
	}
	while(bfs())
	{
		flow+=dfs(s,INF);
	}
	return flow==tc;
}
void DFS2(int i,int j)
{
	if(i>n)
	{
		if(chk())
		{
			/*
			for(i=1;i<=n;i++)
			{
				cerr<<lev[i]<<'#';
			}
			cerr<<' ';
			for(i=1;i<=tot;i++)
			{
				cerr<<v1[i]<<"!"<<v2[i]<<' ';
			}
			cerr<<endl;
			//*/
			c=0;
			memset(deg,0,sizeof(deg));
			for(i=1;i<=n;i++)
			{
				MP[i].clear();
			}
			for(i=1;i<=tot;i++)
			{
				MP[v1[i]].push_back(v2[i]);
				deg[v2[i]]++;
			}
			Dfs(1);
			if(c>=L&&c<=R)
			{
				ans++;
			}
		}
		return ;
	}
	for(;i<=n;i++)
	{
		for(;j<=n;j++)
		{
			if(lev[j]==lev[i]-1)
			{
				v1[++tot]=i;
				v2[tot]=j;
				if(j==n)
				{
					DFS2(i+1,1);
				}
				else
				{
					DFS2(i,j+1);
				}
				tot--;
				if(j==n)
				{
					DFS2(i+1,1);
				}
				else
				{
					DFS2(i,j+1);
				}
				return ;
			}
		}
		j=1;
	}
	DFS2(n+1,1);
}
void DFS(int x)
{
	int i;
	if(x>n)
	{
		tot=0;
		DFS2(1,2);
		return ;
	}
	for(i=1;i<=n;i++)
	{
		lev[x]=i;
		DFS(x+1);
	}
}
struct CosmicBlocks
{
	int getNumOrders(vector<int>_num,int _L,int _R)
	{
		int i;
		L=_L;
		R=_R;
		n=_num.size();
		for(i=1;i<=n;i++)
		{
			num[i]=_num[i-1];
			sum+=num[i];
		}
		DFS(1);
		return ans;
	}
};