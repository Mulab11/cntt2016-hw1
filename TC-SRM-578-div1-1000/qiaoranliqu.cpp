#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>

#define N 55
#define M 10005

#define pb push_back

using namespace std;

int dp[N][N][N][N],vis[N],k1,st,ed,que[M*10],flow[N],cost[N],fa[N];

int i,j,m,n,p,k,A[N],B[N],s1,s2,ans,fox[N];

struct Node{int ed,before,flow,cost;}s[M];

vector<int> v[N];

void add(int x,int y)
{
	  v[x].push_back(y);
	  v[y].push_back(x);
}

void Add(int p1,int p2,int flow,int cost)
  {  s[++k1].ed=p2; s[k1].flow=flow; s[k1].cost=cost; s[k1].before=fox[p1]; fox[p1]=k1; 
     s[++k1].ed=p1; s[k1].flow=0; s[k1].cost=-cost; s[k1].before=fox[p2]; fox[p2]=k1;
  }
int spfa()
 { int l,r,p,i; l=r=1;
    que[1]=st; memset(flow,-1,sizeof(flow));
      flow[st]=100000000;
      memset(cost,-1,sizeof(cost));
      memset(vis,0,sizeof(vis));
      vis[st]=1;
      cost[st]=0;
      for (;l<=r;l++)
       { p=que[l];
         for (i=fox[p];i;i=s[i].before)
           if (s[i].flow)
             if (cost[p]+s[i].cost>cost[s[i].ed])
               {  cost[s[i].ed]=s[i].cost+cost[p];
                   flow[s[i].ed]=min(flow[p],s[i].flow);
                   fa[s[i].ed]=i;
                   if (!vis[s[i].ed]) {vis[s[i].ed]^=1; que[++r]=s[i].ed;
                   }
               }
               vis[p]^=1;
       }
    if (flow[ed]==-1) return 0; return 1;
 }
void doit()
{ int i,p;
      for (i=ed;i!=st;i=s[p^1].ed)
        { p=fa[i];
          s[p].flow-=flow[ed];
          s[p^1].flow+=flow[ed];
        }
}
int maxcost()
{
  int ans=0;
  for (;spfa();) { ans+=cost[ed]*flow[ed]; doit(); }
  return ans; 
}

void bfs(int str,int *a)
{
	   a[a[0]=1]=str;
	   vis[str]=1;
	   int i,l;
	   for (l=1;l<=a[0];++l)
	   {
	   	   int p=a[l];
	   	   for (i=0;i<(int)v[p].size();++i)
	   	   {
	   	   	    int k=v[p][i];
	   	   	    if (!vis[k]) a[++a[0]]=k,vis[k]=1;
	   	   }
	   }
}
int dfs(int x,int fx,int y,int fy)
{
	   if (dp[x][fx][y][fy]!=-1) return dp[x][fx][y][fy];
	   int A[55],B[55],i,j; A[0]=0; B[0]=0;
	   for (i=0;i<(int)v[x].size();++i)
	   {
	   	      int p=v[x][i];
	   	      if (p==fx) continue;
	   	      A[++A[0]]=p;
	   }
	   for (i=0;i<(int)v[y].size();++i)
	   {
	   	      int p=v[y][i];
	   	      if (p==fy) continue;
	   	      B[++B[0]]=p;
	   }
	   for (i=1;i<=A[0];++i) //枚举两个子树计算他们的最大匹配值 
	     for (j=1;j<=B[0];++j) dfs(A[i],x,B[j],y);
	   k1=1; st=A[0]+B[0]+1; ed=st+1;
	   memset(fox,0,sizeof(fox));
	   for (i=1;i<=A[0];++i)  //对所有子树做一个最大权匹配 
	     for (j=1;j<=B[0];++j)
	        Add(i,A[0]+j,1,dfs(A[i],x,B[j],y));
	   for (i=1;i<=A[0];++i) Add(st,i,1,0);
	   for (i=1;i<=B[0];++i) Add(i+A[0],ed,1,0);
	   return dp[x][fx][y][fy]=maxcost()+1;
}
class DeerInZooDivOne{
	 public:
	 	int getmax(vector<int> X,vector<int> Y)
	 	{
	 	      n=X.size()+1;
	 	      for (i=0;i<(int)X.size();++i) //考虑要求树上的两个不相交联通块,那么就枚举一条边(x,y)把边分开 
			  {
			  	    memset(dp,-1,sizeof(dp));
			  	    for (j=0;j<n;++j) v[j].clear();
			  	    for (j=0;j<n-1;++j) if(i!=j) add(X[j],Y[j]);
			  	    memset(vis,0,sizeof(vis));
			  	    bfs(0,A); 
			  	    for (j=0;j<n;++j) if (!vis[j]) bfs(j,B);
			  	    for (s1=1;s1<=A[0];++s1)
			  	      for (s2=1;s2<=B[0];++s2)
			  	      {
			  	      	 if (ans>=A[0]||ans>=B[0]) continue;
			  	        ans=max(ans,dfs(A[s1],0,B[s2],0)); //令f_{sx,sy,ex,ey}为sx以sy为父亲的子树与ex以ey为父亲的子树的最大同构值,该问题的总状态数为O(N^2),加上枚举一共是O(n^3)的状态 
			  	      }
			  }
			  return ans;
	 	}
}E;
int main()
{
     vector<int> L,R;
int A[]={0, 0, 0, 19, 0, 0, 38, 0, 40, 15, 26, 0, 0, 0, 0, 10, 0, 0, 46, 25, 0, 0, 0, 0, 44, 0, 49, 0, 22, 0, 0, 0, 0, 0, 0, 0, 30, 0, 27, 0, 13, 0, 0, 2, 0, 0, 3, 0, 0, 37,-1},
B[]={32, 8, 45, 0, 14, 20, 0, 36, 0, 0, 0, 16, 1, 50, 33, 0, 43, 31, 0, 0, 47, 5, 9, 11, 0, 35, 0, 23, 0, 18, 34, 4, 48, 39, 12, 17, 0, 42, 0, 7, 0, 29, 28, 0, 24, 21, 0, 41, 6, 0,-1};
   for (int rr=0;A[rr]!=-1;++rr) L.pb(A[rr]);
   for (int rr=0;B[rr]!=-1;++rr) R.pb(B[rr]);
	 printf("%d\n",E.getmax(L,R));
}
