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

#define N 6505
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
const int x[4]={-1,1,0,0};
const int y[4]={0,0,-1,1}; 
map<pair<int,int>,int>mp;
int i,j,m,n,p,k,st,ed,T,sum,cnt;
int fox[N],k1=1,que[N],flow[N],cost[N],vis[N],fa[N];
struct Node{int ed,before,flow,cost;}s[M];
void add(int p1,int p2,int flow,int cost)
  {  s[++k1].ed=p2; s[k1].flow=flow; s[k1].cost=cost; s[k1].before=fox[p1]; fox[p1]=k1; 
     s[++k1].ed=p1; s[k1].flow=0; s[k1].cost=-cost; s[k1].before=fox[p2]; fox[p2]=k1;
  }
int spfa()
 { int l,r,p,i; l=r=1;
    que[1]=st; memset(flow,-1,sizeof(flow));
      flow[st]=100000000;
      memset(cost,60,sizeof(cost));
      memset(vis,0,sizeof(vis));
      vis[st]=1;
      cost[st]=0;
      for (;l<=r;l++)
       { p=que[l];
         for (i=fox[p];i;i=s[i].before)
           if (s[i].flow)
             if (cost[p]+s[i].cost<cost[s[i].ed])
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
pair<int,int> mincost()
{
  int ans=0,Flow=0;
  for (;spfa();) { Flow+=flow[ed]; ans+=cost[ed]*flow[ed]; doit(); }
  return mk(Flow,ans); 
}
int id(int x,int y)
{
	  return x*m+y;
}
int check(int x,int y)
{
	  if (x<0||y<0||x>=n||y>=m) return 0;
	  return 1; 
}
class CurvyonRails{
	  public:
	  	int getmin(vector<string> s)
	  	{
	  		   n=s.size(); m=s[0].length(); 
	  		   st=3*n*m+1; ed=st+1;
				//黑白染色,然后考虑到一个点一定是匹配了两个点,且要尽量减少关键点在同行同列上的匹配 
				//不妨将一个点i拆为x_i,y_i,i向x_i,y_i分别连两条流量为1的边,如果这个点是关键点,那么i向这两个点连的第二条边费用为1,否则费用为0. 
	  		   for (i=0;i<n;++i)
	  		     for (j=0;j<m;++j)
	  		       if (s[i][j]!='w')
				 {
				 	      sum++;
				 	      if ((i+j)&1)
				 	      {
				 	      	   ++cnt;
				 	      	   add(st,id(i,j),2,0);
				 	      	   add(id(i,j),id(i,j)+n*m,1,0);
				 	      	   add(id(i,j),id(i,j)+2*n*m,1,0);
							   add(id(i,j),id(i,j)+n*m,1,(s[i][j]=='C'));
							   add(id(i,j),id(i,j)+2*n*m,1,(s[i][j]=='C')); 
				 	      	   for (k=0;k<4;++k)
				 	      	     if (check(i+x[k],j+y[k])&&s[i+x[k]][j+y[k]]!='w')
				 	      	     {
				 	      	     	   if (x[k]) add(id(i,j)+n*m,id(i+x[k],j+y[k])+n*m,1,0);
									   else add(id(i,j)+2*n*m,id(i+x[k],j+y[k])+2*n*m,1,0); 
				 	      	     }
				 	      }
				 	      else 
				 	      {
				 	      	   --cnt;
				 	      	   add(id(i,j),ed,2,0);
				 	      	   add(id(i,j)+n*m,id(i,j),1,0);
				 	      	   add(id(i,j)+2*n*m,id(i,j),1,0);
							   add(id(i,j)+n*m,id(i,j),1,(s[i][j]=='C'));
							   add(id(i,j)+2*n*m,id(i,j),1,(s[i][j]=='C')); 
						 }
			     }
			     if (cnt) return -1;
			     pair<int,int> x=mincost(); //直接跑费用流即可. 
			     if(x.fi!=sum) return -1;
			     return x.se;
	  	}
};
