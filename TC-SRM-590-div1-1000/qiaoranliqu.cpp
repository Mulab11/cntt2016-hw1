#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 45
#define M 1000005
#define seed 23333
#define Mo 998244353

using namespace std;
const int inf=(int)1e9;
int i,j,m,n,p,k,id[N][N],st,ed,tot,k1=1;
struct Node{int ed,before,flow;}s[M];
int dis[N*N],que[N*N],fox[N*N];
int sqr(int x) { return x*x; }
inline int bfs()
 { int i,j,p,k,l,r;
   memset(dis,-1,sizeof(dis));
    l=r=1;
    dis[st]=0;
   que[1]=st;
   while (l<=r)
    { p=que[l];
      for (i=fox[p];i;i=s[i].before)
        if (s[i].flow>0)
        if (dis[s[i].ed]==-1)
         { 
           que[++r]=s[i].ed;
           dis[s[i].ed]=dis[p]+1;
           }
    l++;
}
 if (dis[ed]==-1) return 0;
 return 1;
}
void add(int p1,int p2,int p3) {s[++k1].ed=p2; s[k1].flow=p3; s[k1].before=fox[p1]; fox[p1]=k1;
  s[++k1].ed=p1; s[k1].flow=0; s[k1].before=fox[p2]; fox[p2]=k1; }
int dfs(int num,int flow)
 {  int i,p;
    int a,nowans=0;
   if (num==ed) return flow;
     for (i=fox[num];i&&flow;i=s[i].before)
       if (s[i].flow>0&&dis[s[i].ed]==dis[num]+1)
        if(a=dfs(s[i].ed,min(s[i].flow,flow)))
         { s[i].flow-=a;
           s[i^1].flow+=a;
           flow-=a;nowans+=a;
           }if (!nowans) dis[num]=(int)1e9;
   return nowans;
}
int maxflow()
{ int i,j;
  int ans=0;
    while (bfs())
    { j=dfs(st,(int)1e9);  while (j) ans+=j,j=dfs(st,(int)1e9); }
  return ans;
}
class FoxAndCity{
	public:
		int minimalCost(vector<string> v,vector<int> goal)
		{
			  n=v.size();
			  st=++tot; ed=++tot;
			  for (i=0;i<n;++i) 
			  {
			  	   for (j=0;j<=n;++j) id[i][j]=++tot;
			  	   if (i!=0) add(st,id[i][0],inf);
			  	   for (j=1;j<=n;++j) 
			  	     if (i!=0) add(id[i][j-1],id[i][j],sqr(j-goal[i]));
			  	     else add(id[i][j-1],id[i][j],inf);
			  	   add(id[i][n],ed,inf);
			  }
			  for (i=0;i<n;++i)
			    for (j=0;j<n;++j)
			      if (v[i][j]=='Y') 
			        for (k=1;k<=n;++k)
			          add(id[i][k],id[j][k-1],inf);
			  return maxflow(); 
		}
}FFT;
int main()
{
  vector<string>s;
 s.pb("NYNN"),
 s.pb("YNYN"),
 s.pb("NYNY");
 s.pb("NNYN"); 
  vector<int>t;
 t.pb(0); t.pb(3); t.pb(3); t.pb(3);
 printf("%d\n",FFT.minimalCost(s,t));
}
