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
#define MAXN 3010
#define MAXM 1000010
#define INF 1000000000
#define MOD 1000000007
#define eps 1e-8
#define ll long long
struct BoardPainting
{
	struct vec
	{
		int to;
		int fro;
		int v;
	};
	vec mp[MAXM];
	int tai[MAXN],cnt;
	char MP[MAXN][MAXN];
	int d[MAXN];
	int q[MAXN],hd,tl;
	int n,m;
	int ans;
	int s,t;
	int pt(int x,int y)
	{
		return (x-1)*m+y;
	}
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
	int minimalSteps(vector<string> _mp)
	{
		cnt=1;
		int i,j;
		n=_mp.size();
		m=_mp[0].size();
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
			{
				MP[i][j]=_mp[i-1][j-1];
			}
		}
		s=pt(n,m)+1;
		t=s+1;
		for(i=1;i<=n;i++)
		{
			for(j=1;j<=m;j++)
			{
				if(MP[i][j]=='#')
				{
					if(MP[i-1][j]=='#')
					{
						bse(pt(i-1,j),pt(i,j),1);
					}
					else
					{
						bse(s,pt(i,j),1);
					}
					if(MP[i+1][j]=='#')
					{
						bse(pt(i+1,j),pt(i,j),1);
					}
					else
					{
						bse(s,pt(i,j),1);
					}
					if(MP[i][j-1]=='#')
					{
						bse(pt(i,j-1),pt(i,j),1);
					}
					else
					{
						bse(pt(i,j),t,1);
					}
					if(MP[i][j+1]=='#')
					{
						bse(pt(i,j+1),pt(i,j),1);
					}
					else
					{
						bse(pt(i,j),t,1);
					}
				}
			}
		}
		while(bfs())
		{
			ans+=dfs(s,INF);
		}
		return ans/2;
	}
};