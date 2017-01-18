#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string> 

#define N 55

using namespace std;

vector<int>v[N*N];

const int x[4]={0,0,-1,1};
const int y[4]={1,-1,0,0};

int i,j,m,n,p,k,deep[N*N],fa[N*N],vis[N*N],Max[N*N],A,B,dis[2][N*N],Q[N*N];

int ID(int x,int y)
{
	 return x*m+y;
}

void add(int x,int y)
{
	 v[x].push_back(y);
}

bool Check(int x,int y)
{
	  if (x<0||y<0||x>=n||y>=m) return 0;
	  return 1;
}
void bfs(int x,int A[])
{
	   memset(vis,0,sizeof(vis));
	   vis[x]=1;
	   Q[Q[0]=1]=x;
	   int l,i;
	   for (l=1;l<=Q[0];++l)
	   {
	        int p=Q[l];
			for (i=0;i<(int)v[p].size();++i)
			  if (!vis[v[p][i]])
			  {
			         int k=v[p][i];
					 vis[k]=1;
					 Q[++Q[0]]=k;
					 A[k]=A[p]+1;
			  }
	   }
}
void dfs(int x)
{
	   int i;
	   for (i=0;i<(int)v[x].size();++i)
	   {
	   	     int p=v[x][i];
	   	     if (fa[x]==p) continue;
	   	     fa[p]=x;
	   	     Max[p]=deep[p]=deep[x]+1;
	   	     dfs(p);
	   	     Max[x]=max(Max[x],Max[p]);
	   }
}
class GameInDarknessDiv1{
	  public:
	  	string check(vector<string> s)
	  	{
	  		  n=s.size();
	  		  m=s[0].length();
			  for (i=0;i<n;++i)
			    for (j=0;j<m;++j)
				   if (s[i][j]!='#') 
				   {
				     for (k=0;k<4;++k)
					   if (Check(i+x[k],j+y[k])&&s[i+x[k]][j+y[k]]!='#') 
					    add(ID(i,j),ID(i+x[k],j+y[k])); 
					 if (s[i][j]=='A') A=ID(i,j);
					 if (s[i][j]=='B') B=ID(i,j); 
				   }
			  bfs(A,dis[0]); bfs(B,dis[1]);
			  for (i=0;i<ID(n-1,m-1);++i)
			     if (dis[0][i]-dis[1][i]>=2)
			     {
                        memset(Max,0,sizeof(Max));
                        memset(fa,0,sizeof(fa));
                        memset(deep,0,sizeof(deep));
			     	    dfs(i); int cnt=0;
			     	    for (j=0;j<(int)v[i].size();++j)
			     	        if (Max[v[i][j]]>=3) ++cnt;
			     	    if (cnt>=3) return "Bob wins";
			     }
			 return "Alice wins";
	  	}
};
