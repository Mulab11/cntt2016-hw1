#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>

using namespace std;
const int INF=(int)1e9;
const int x[4]={0,0,-1,1};
const int y[4]={-1,1,0,0};
struct Node{int ed,before,flow;}s[5000001];
int fox[10005],que[10005],dis[10005],st,ed,k1=1,n,i,j,k;
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
int ID(int x,int y) { return (x-1)*n+y; }
int check(int x,int y)
{
	 if (x<1||y<1||x>n||y>n) return 0;
	 return 1;
}
class FoxAndGo3
{
	public:
		int maxEmptyCells(vector<string> s)
	    {
		     int ans=0; n=s.size();
			 st=n*n+1; ed=st+1;
			 for (i=1;i<=n;++i)
			   for (j=1;j<=n;++j)
			     if (s[i-1][j-1]=='.') ++ans,add(st,ID(i,j),1);
				 else if (s[i-1][j-1]=='o')
				 {
				      ++ans; add(ID(i,j),ed,1); 
				      for (k=0;k<4;++k) if (check(i+x[k],j+y[k])&&s[i+x[k]-1][j+y[k]-1]=='.')
				      add(ID(i+x[k],j+y[k]),ID(i,j),INF);
				 }
				 return ans-maxflow();
	    }
}ETT;
