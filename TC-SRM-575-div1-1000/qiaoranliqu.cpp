#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>

#define pb push_back

#define N 105
#define M 2000005

using namespace std;

const int x[4]={0,0,-1,1};
const int y[4]={-1,1,0,0};
int dis[N*N],st,ed,que[N*N],fox[N*N],k1=1,id[N][N][2],n,m,i,j,tot,k;

struct Node{int ed,before,flow;}s[M];

bool check(int x,int y)
{
	   if(x<0||y<0||x>=n||y>=m) return 0; 
	   return 1;
}

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

class TheTilesDivOne{
	  public:
	  int find(vector<string> s) //考虑同一个L形的三个点,对于两个非转折点,他们i,j一定奇偶不同,那么一条路径就可以视为(i是奇数的白点->黑点->i是偶数的点) 
	  {
	  	       n=s.size(); m=s[0].length();
	  	       for (i=0;i<n;++i)
	  	         for (j=0;j<m;++j)
	  	           if (s[i][j]!='X')
	  	           {
	  	           if ((i+j)&1)
	  	           	      id[i][j][0]=++tot;
	  	           else id[i][j][0]=++tot,id[i][j][1]=++tot,add(id[i][j][0],id[i][j][1],1); //注意黑点要拆点,否则无法控制流量 
				   }
			   st=++tot; ed=++tot;
			   for (i=0;i<n;++i)
			     for (j=0;j<m;++j)
			       if (s[i][j]!='X'&&((i+j)&1))
			       {
			       	     if(i&1) 
							{
							     add(st,id[i][j][0],1);
							     for (k=0;k<4;++k)
								   if (check(i+x[k],j+y[k])&&s[i+x[k]][j+y[k]]!='X')
								    add(id[i][j][0],id[i+x[k]][j+y[k]][0],1); 
							}
						 else 
						 {
						 	     add(id[i][j][0],ed,1);
							     for (k=0;k<4;++k)
								   if (check(i+x[k],j+y[k])&&s[i+x[k]][j+y[k]]!='X') 
								    add(id[i+x[k]][j+y[k]][1],id[i][j][0],1); 
						 }
				   }
				   return maxflow(); //跑网络流 
	  }
}ETT;

int main()
{
	  vector<string> A;
	  A.pb(".............X.............X.X.....X.....X..."),
      A.pb("X.X.....X.X.....X.......X.X...X.X.X.X.X.X.X.."),
      A.pb(".X...X.X.................X.X...........X.X...");
      A.pb("X.X.X.X.....X.X.....X.....X.....X.X.X.....X..");
      printf("%d\n",ETT.find(A));
}


