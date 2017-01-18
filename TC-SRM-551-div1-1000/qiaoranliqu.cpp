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

#define N 45
#define M 1100005
#define seed 23333
#define Mo 1000000007

using namespace std;
int good,bad,i,j,m,n,p,k,A[N],val[N],B[N][N],g[N],C[N],tota,totb,V,G[N],c[N][N];
int F[21];
void jia(int &x,int y) { x+=y; if (x>=Mo) x-=Mo; }
struct Node{int val,id;}a[M],b[M];
void dfs(int x,int y,int z) //折半搜索 
{
	 if (x>good/2)
	 {
	 	  a[++tota]=(Node){y,z};
	 }
	 else 
	 {
	 	   dfs(x+1,y,z);
	 	   dfs(x+1,y+A[x],z+1);
	 }
}
void Dfs(int x,int y,int z)
{
	 if (x>good)
	 {
	 	  b[++totb]=(Node){y,z};
	 }
	 else 
	 {
	 	   Dfs(x+1,y,z);
	 	   Dfs(x+1,y+A[x],z+1);
	 }
}
int power(int x,int y)
{
	   int sum=1;
	   for (;y;y>>=1)
	   {
	   	   if (y&1) sum=1ll*sum*x%Mo;
	   	   x=1ll*x*x%Mo;
	   }
	   return sum;
}
int guass() //基尔霍夫矩阵求生成树个数 
{
       int ret=1,i,j,k;
       for(i=1;i<n;++i)
       {
          for (j=i;j<=n;++j) if (B[j][i]) break;
          if (j>n) return 0;
          for (k=1;k<=n;++k) swap(B[i][k],B[j][k]);
          int inv=power(B[i][i],Mo-2);
          for (j=i+1;j<=n;++j) 
            if (B[j][i])
            {
                  int res=1ll*B[j][i]*inv%Mo;
                  for (k=i;k<=n;++k) jia(B[j][k],Mo-1ll*res*B[i][k]%Mo);
            }
          ret=1ll*ret*B[i][i]%Mo;
       }
       return ret;
}
int cal() //计算当孤立点个数为i时的方案数 
{
	   int i,j;
	  memset(B,0,sizeof(B));
	  for (i=1;i<=n;++i)
	    for (j=i+1;j<=n;++j)
	    {
	    	   if (C[i]==1&&C[j]==2) continue;
	    	   if (C[i]==1&&C[j]==1) continue;
	    	   jia(B[i][j],Mo-1);jia(B[j][i],Mo-1);B[i][i]++;B[j][j]++;
	    }
	  return guass();
}
inline bool cmp(Node a,Node b)
{
	 return a.val<b.val;
}
class SweetFruits{
  public:
  	int countTrees(vector<int> v,int Vc)
	  	{
  	  n=v.size();
  	  for (i=1;i<=n;++i) val[i]=v[i-1];  V=Vc;
	  for (i=0;i<N;++i)
	  {
	  	   c[i][0]=1;
	  	   for (j=1;j<=i;++j) c[i][j]=(c[i-1][j]+c[i-1][j-1])%Mo;
	  }
	  	  good=0,bad=0; 
	  	  memset(G,0,sizeof(G));
	  	  for (i=1;i<=n;++i) 
		  {
		      if (val[i]==-1) bad++;
		      else good++,A[good]=val[i];
		  }
		  memset(C,0,sizeof(C));
		  for (i=1;i<=good;++i) C[i]=1;
		  memset(g,0,sizeof(g));
		  for (i=good;i>=0;--i)
		  {
		  	   g[i]=cal();
		  	   for (j=i+1;j<=good;++j) g[i]=(g[i]-1ll*c[good-i][j-i]*g[j]%Mo+Mo)%Mo;
		  	   C[i]=2;
		  }
		  tota=totb=0;
		  dfs(1,0,0); Dfs(good/2+1,0,0);
		  sort(a+1,a+tota+1,cmp);
		  sort(b+1,b+totb+1,cmp);
		  memset(F,0,sizeof(F));
		  for (i=1;i<=totb;++i) F[b[i].id]++;
		  int L=totb; //求i个点不孤立的合法选取数 
		  for (i=1;i<=tota;++i)
		  {
		  	    while (L&&a[i].val+b[L].val>V) F[b[L].id]--,--L;
				  for (j=0;j<=20;++j) jia(G[j+a[i].id],F[j]); 
		  }
		  int ans=0;
		  for (i=0;i<=good;++i) jia(ans,1ll*G[i]*g[good-i]%Mo); 
		  return ans;
	}
};

