#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>

#define N 55

using namespace std;

const int inf=(int)1e9;
int i,j,m,n,p,k,f[N][N][1305],g[N][N][1305],val[N][N],V[N][N],E[N][N],tot;

int Val(int x,int sy,int ey)
{
  return V[x][ey]-V[x][sy-1];
}

inline int dfs(int x,int y,int ex,int ey,int ty) //本题的结论是第二个人一定在第一个人走到某个格子的时候再决定要不要放格子, 
{												//而第一个人一定是如果第二个人不拦他就一定走下去.如此,最后每层放的板子一定是连续的一段 
	 if (ty==0)									//令f_{i,j,l,r,x}表示当前是x决策,棋子在(i,j)这个位置 ,且层i的板子放在[l,r)的最优解 
	 {
	   int& res=f[x][y][E[ex][ey]];
	   if (res==-1)
	   {
	   	   res=inf;
	   	   if (!(ex<=y&&y<ey)) res=val[x+1][y]+dfs(x+1,y,y,y,1); //第一个人一定是能走就走,否则走到最左边或最右边 
	   	   else 
	   	   {
	   	   	    if (ex>1) res=min(res,dfs(x,ex-1,ex,ey,1)+Val(x,ex-1,y-1));
			    if (ey<=m) res=min(res,dfs(x,ey,ex,ey,1)+Val(x,y+1,ey)); 
	   	   }
	   }
	   return res;
     }
     else 
     {
       int& res=g[x][y][E[ex][ey]];
	   if (x==n) return 0;
	   if (res==-1) //第二个人可以决策要不要放板子 
	   {
	   	     if (ey-ex<m-1)
		     {
		     	   res=max(res,dfs(x,y,min(ex,y),max(y+1,ey),0));
		     }
		     res=max(res,dfs(x,y,ex,ey,0));
       }
       return res;
     }
}
class WallGameDiv1{
   public:
    int play(vector<string> s)
	{
	     n=s.size(); m=s[0].length();
	     for (i=1;i<=m;++i)
	       for (j=i;j<=m+1;++j) E[i][j]=tot++;
		 for (i=1;i<=n;++i)
		   for (j=1;j<=m;++j)
		       val[i][j]=s[i-1][j-1]-'0'; 
		 for (i=1;i<=n;++i)
		   for (j=1;j<=m;++j) V[i][j]=val[i][j]+V[i][j-1];
		 memset(g,-1,sizeof(g));
		 memset(f,-1,sizeof(f));
		 int ans=inf;
		 for (i=1;i<=m;++i) 
		 ans=min(ans,dfs(1,i,i,i,1)+val[1][i]);
		 return ans;
	}
}FFT;
int main()
{
	  vector<string> v;
	  v.push_back("12"); v.push_back("34");
	  printf("%d\n",FFT.play(v));
}
