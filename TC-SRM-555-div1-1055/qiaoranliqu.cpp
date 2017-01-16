
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<string>
#include<iostream>

#define N 666

using namespace std;
long long ans;
char A[N];
int B[N],n,i,j,C[N],D[N][N],tot,top,G[N],k,F;
inline int check()
{
	   int i;
	   for (i=1;i<=n;++i)
	     if (C[i]!=-1&&B[i]!=C[i]) return 0;
	   return 1;
}
void dfs(int x,int Sum,int xu)
{
	  if (Sum==0) return;
	  if (x>tot)
	  {
	  	   if (!xu) return;
	  	   if (xu&1) ans+=1ll<<Sum,ans--; //Sum为交集大小，容斥计算答案。
	  	   else ans-=1ll<<Sum,++ans;
	  }
	  else 
	  {
	  	    dfs(x+1,Sum,xu);
	  	    int R[50],i;
	  	    for (i=1;i<=n;++i) R[i]=G[i];
	  	    for (i=1;i<=n;++i) if (D[x][i]!=G[i]&&G[i]==-1) G[i]=max(G[i],D[x][i]),--Sum;
            //取交，注意到所有的序列里确定的位置的交上面的数一定都是和目标序列相同的。
			dfs(x+1,Sum,xu+1);
			for (i=1;i<=n;++i) G[i]=R[i];
	  }
}
class MapGuessing{
public:
long long countPatterns(string s,vector<string> v)
{
	  n=s.length();
	  for (i=1;i<=n;++i) B[i]=s[i-1]-'0';
	  for (i=0;i<(int)v.size();++i) //得到序列
	    for (j=0;j<(int)v[i].length();++j)
	      A[++top]=v[i][j];
	  for (i=1;i<=n;++i) //枚举磁头的起始位置
	  {
	  	    memset(C,-1,sizeof(C));
            memset(G,-1,sizeof(G));
	  	    int now=i,flag=0;
	  	    for (j=1;j<=top;++j) 
	  	    {
	  	    	   if (A[j]=='1') C[now]=1;
	  	    	   if (A[j]=='0') C[now]=0;
	  	    	   if (A[j]=='<') --now;
	  	    	   if (A[j]=='>') ++now;
	  	    	   if (now<1||now>n) break;
	  	    	   if (check()) 
	  	    	   {
	  	    	   	  flag=1;
	  	    	   	  for (k=1;k<=n;++k) G[k]=C[k]; //记录最晚一次的情况
	  	    	   }
	  	    }
	  	    if (j>top) F=1; 
	  	    if (j<=top||!flag) continue;
	  	    ++tot;
	  	    for (j=1;j<=n;++j) //存储每种开头位置的序列
			     if(G[j]!=-1) 
				    D[tot][j]=-1;
				 else D[tot][j]=B[j];
      }
      if (!F) return 0;
      ans=1;//将所有位置都确定提前加入答案
      for (i=1;i<=n;++i) G[i]=-1;
      dfs(1,n,0);//搜索
      return ans;
}
};
