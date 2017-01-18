#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>

#define N 55

using namespace std;

int i,j,m,n,p,k,st,ed,dis[N*N],que[N*N],fox[N*N],k1=1,id[N][N],tot;

struct Node{int ed,before,flow;}s[N*N*N];

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

class BoardPainting{
	  public:
	  	int minimalSteps(vector<string> s)
	  	{
	  		n=s.size(); m=s[0].length();
	  		for (i=1;i<=n;++i)
	  		  for (j=1;j<=m;++j) if (s[i-1][j-1]=='#') id[i][j]=++tot;
	  	    st=++tot; ed=++tot;
	  	    for (i=1;i<=n;++i) //考虑一种染色方案,只有当一个属于左右的点右侧不是一个属于左右的点时才产生贡献;上下同理,于是按照此原理构造最小割即可. 
	  	      for (j=1;j<=m;++j) if (id[i][j])
	  	      {
	  	      	    if (id[i+1][j]) add(id[i][j],id[i+1][j],1);
	  	      	    else add(id[i][j],ed,1);
	  	      	    if (id[i][j+1]) add(id[i][j+1],id[i][j],1);
	  	      	    else add(st,id[i][j],1);
	  	      }
	  	    return maxflow();
	   } 	
};
