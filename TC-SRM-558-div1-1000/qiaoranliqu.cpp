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

#define N 1005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
const int x[4]={0,0,-1,1};
const int y[4]={1,-1,0,0};
const int inf=(int)1e9;
int i,j,m,n,p,k,st,ed,tot,fox[N],k1=1,dis[N],que[N];
struct Node{int ed,before,flow;}s[M];
void add(int x,int y,int u)
{
	  s[++k1].ed=y; s[k1].before=fox[x]; fox[x]=k1; s[k1].flow=u;
	  s[++k1].ed=x; s[k1].before=fox[y]; fox[y]=k1; s[k1].flow=0;
}
inline int bfs()
 { int i,p,l,r;
   memset(dis,-1,sizeof(dis));
    l=r=1;
    dis[st]=0;
   que[1]=st;
   while (l<=r&&dis[ed]==-1)
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
int dfs(int num,int flow)
 {  int i;
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
int maxflow() //网络流 
{ 
  int ans=0;
    while (bfs()) ans+=dfs(st,(int)1e9); 
  return ans;
}

#define T 25 
int A[T][T],B[T][T],ID[T][T][2];

int got(char c)
{
		if (c<='9') return c-'0';
		if (c>='a') return c-'a'+10;
		return c-'A'+36;
}

int check(int x,int y)
{
		if (x<0||y<0||x>=n||y>=m) return 0;
		return 1;
}

class SurroundingGame{
		public:
			int maxScore(vector <string> cost, vector <string> benefit)
			{
					n=cost.size(); m=cost[0].length();
					for (i=0;i<n;++i)
					{
							for (j=0;j<m;++j)
							  A[i][j]=got(cost[i][j]),B[i][j]=got(benefit[i][j]),
							  ID[i][j][0]=++tot,ID[i][j][1]=++tot;
					}
					st=++tot; ed=++tot; int ans=0;
					for (i=0;i<n;++i)
						for (j=0;j<m;++j)
							if ((i+j)&1) //如果这个点是白点的话 
							{
								 int C=B[i][j]-A[i][j];
								 ans+=max(0,C)+B[i][j];
								 add(ID[i][j][1],ID[i][j][0],inf);
								 add(st,ID[i][j][1],B[i][j]);
								 add(st,ID[i][j][0],max(0,-C));
								 add(ID[i][j][0],ed,max(0,C));
								 for (k=0;k<4;++k) //和周围的黑点连边 
								 	if (check(i+x[k],j+y[k]))
								 	  add(ID[i][j][0],ID[i+x[k]][j+y[k]][1],inf),
								 	  add(ID[i][j][1],ID[i+x[k]][j+y[k]][0],inf);
							} 
							else  //黑点的构图,和白点的方向相反 
							{
								 int C=B[i][j]-A[i][j];
								 ans+=max(0,C)+B[i][j];
								 add(ID[i][j][0],ID[i][j][1],inf);
								 add(st,ID[i][j][0],max(0,C));
								 add(ID[i][j][0],ed,max(0,-C));
								 add(ID[i][j][1],ed,B[i][j]);
							}
					return ans-maxflow();  //最小割 
			}
};

