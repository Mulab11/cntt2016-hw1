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

#define N 15
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
const int inf=(int)1e9;
int i,j,m,n,p,k,A[N],ans,dis[N],size[N],st,ed,Q[N],fox[N],k1,Ru[N],Chu[N];
int a,b,f[100];
vector<int>v[N],V[N];
struct Node{int ed,before,flow;}s[M];
void add(int x,int y,int flow) 
{
		s[++k1].ed=y; s[k1].before=fox[x]; fox[x]=k1; s[k1].flow=flow;
		s[++k1].ed=x; s[k1].before=fox[y]; fox[y]=k1; s[k1].flow=0;
}
int bfs()
{
   Q[Q[0]=1]=st; memset(dis,-1,sizeof(dis));
   dis[st]=0;
   int l=1,i;
   for (;l<=Q[0]&&dis[ed]==-1;++l)
  {
        int p=Q[l];
        for (i=fox[p];i;i=s[i].before)
          if (s[i].flow&&dis[s[i].ed]==-1)
            {
            	dis[s[i].ed]=dis[p]+1;
            	Q[++Q[0]]=s[i].ed;
			}
  }
  return dis[ed]!=-1;
}
int dfs(int x,int flow)
{
	if (x==ed) return flow;
	int i; int nowans=0,a;
	for (i=fox[x];i&&flow;i=s[i].before)
	  if (dis[s[i].ed]==dis[x]+1&&s[i].flow)
	  {
	  		   a=dfs(s[i].ed,min(flow,s[i].flow));
	  		   if (a) 
	  		   	{
	  		   		nowans+=a;
	  		   		flow-=a;
	  		   		s[i].flow-=a;
	  		   		s[i^1].flow+=a;
				}
	  }
	 if (!nowans) dis[x]=(int)1e9;
	 return nowans;
}
int maxflow()
{
		int ans=0;
		while (bfs()) ans+=dfs(st,inf);
		return ans;
}
bool work()
{
		int l,i; Q[0]=0; memset(dis,-1,sizeof(dis)); memset(size,0,sizeof(size));
		for (i=0;i<n;++i) size[i]=v[i].size();
		for (i=0;i<n;++i) if (!size[i]) Q[++Q[0]]=i,dis[i]=0;
		for (l=1;l<=Q[0];++l) //判断这是否是一张合法的拓扑图 
		{
				int p=Q[l];
				for (i=0;i<(int)V[p].size();++i)
				{
						int k=V[p][i];
						if (dis[k]==-1) dis[k]=dis[p]+1;
						else if (dis[k]!=dis[p]+1) return 0;
						--size[k];
						if (!size[k]) Q[++Q[0]]=k;	
				}
		}
//		if (v[0].size()==0) return 1; else return 0;
		if (Q[0]!=n) return 0;
		memset(fox,0,sizeof(fox)); k1=1; st=2*n; ed=st+1;
		for (i=0;i<n;++i) Ru[i]=Chu[i]=A[i];
		for (i=0;i<n;++i) //对网络流进行建边 
		{
			for (j=0;j<(int)v[i].size();++j)
			{
				int p=v[i][j];
				Ru[i]--; Chu[p]--;
				add(i,p+n,inf); 
			}
			if (dis[i]==0) add(i,ed,inf);  
		}
		int Ans=0;
		for (i=0;i<n;++i) 
		{
				if (Ru[i]<0||Chu[i]<0) return 0;
				add(st,i,Ru[i]);
				add(i+n,ed,Chu[i]);
				Ans+=Ru[i];
		} 
		if (Ans!=maxflow()) return 0;
		int Maxn=1<<n; 
		for (i=0;i<Maxn;++i) f[i]=0; f[0]=1;
		for (i=0;i<Maxn;++i) //利用dp计算拿取的方案数 
			if (f[i])
				for (j=0;j<n;++j)
					if ((i&(1<<j))==0)
					{
							for (k=0;k<(int)V[j].size();++k)
								if ((i&(1<<V[j][k]))==0)
								  break;
							if (k==(int)V[j].size()) f[i|(1<<j)]+=f[i];
					}
		if (a<=f[Maxn-1]&&f[Maxn-1]<=b)  return 1;
		return 0;
}
void DFS(int x,int y) //搜出所有拓扑图 
{
		if (x==n) ans+=work();
		else if (y==n) DFS(x+1,x+2);
		else 
		{
						v[x].pb(y); V[y].pb(x);
						DFS(x,y+1);
						v[x].pop_back(); V[y].pop_back();
						DFS(x,y+1);
						v[y].pb(x);	V[x].pb(y);
						DFS(x,y+1);
						v[y].pop_back(); V[x].pop_back();
		}
}
class CosmicBlocks{
	public:
	int getNumOrders(vector <int> blockTypes, int minWays, int maxWays)
	{
		n=blockTypes.size(); a=minWays; b=maxWays;
		for (i=0;i<n;++i) A[i]=blockTypes[i];
		DFS(0,1);
		return ans;
	}
}FFT;

int main()
{
	 vector<int> v; v.pb(1); v.pb(2); v.pb(4); v.pb(8);
	 printf("%d\n",FFT.getNumOrders(v,5,30));
}

