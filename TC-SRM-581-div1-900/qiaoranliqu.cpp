#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>

#define N 14

using namespace std;
const int inf=(int)1e9;
int i,j,m,n,p,k,g[14],ans=inf,A[N][N];
void dfs(int x,int y)
{
	int i;
	if (y>=ans) return;
	if (x>n)
	{
		  for (i=1;i<=m;++i) if (A[n][i]==0) return; 
		   ans=y;
		   return;
	}
	int pre[14],flag=0; vector<int> v;
	memcpy(pre,g,sizeof(g));
	for (i=1;i<=m;++i) if (A[x-1][i]==0) v.push_back(i);
	for (i=0;i<(int)v.size();++i) //考虑上面一行的请况,都使用方案一来做 
	{
		   if(g[v[i]]==1) flag=1;
		   g[v[i]]=0; 
		   A[x][v[i]-1]^=1; A[x-1][v[i]]^=1;
		   A[x][v[i]+1]^=1; A[x+1][v[i]]^=1;
	}
	if(!flag) dfs(x+1,y+v.size());
	flag=0;
	memcpy(g,pre,sizeof(pre));
	for (i=0;i<(int)v.size();++i) //都使用方案二来做 
	{
	       if (g[v[i]]==0) flag=1;
		   g[v[i]]=1;
		   A[x][v[i]]^=1;
	}
	if(!flag) dfs(x+1,y+v.size());
	memcpy(g,pre,sizeof(pre));
	for (i=0;i<(int)v.size();++i) //撤销操作 
	{
		   A[x][v[i]-1]^=1; A[x-1][v[i]]^=1; A[x][v[i]]^=1;
		   A[x][v[i]+1]^=1; A[x+1][v[i]]^=1;
	}
}
class YetAnotherBoardGame
{
    public:
	  int minimumMoves(vector<string> s)
	  {
	  	     n=s.size(); m=s[0].length(); 
	  	     for (i=1;i<=n;++i)
	  	       for (j=1;j<=m;++j) A[i][j]=(s[i-1][j-1]=='B');
	  	     for (i=0;i<(1<<m);++i) //初始一个第0行的初始状态,然后第一行就可以判断了. 
			 {
			          for (j=0;j<m;++j) A[0][j+1]=((i&(1<<j))>0);
					  memset(g,-1,sizeof(g)); 
					  dfs(1,0);
			 }	
			 if(ans==inf) return -1; return ans;
      }
}FFT;
int main()
{
	  vector<string> gg;
	  gg.push_back("WBW"),
      gg.push_back("BBW"),
      gg.push_back("WBW");
      printf("%d\n",FFT.minimumMoves(gg));
}
