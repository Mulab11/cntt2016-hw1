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

#define N 100005
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,ans=4,w;
bool check(int n,int x)
{
	  if (n<=w&&(x==1||x==n)) return 1;
	  if (w==1&&x==1) return 1;
	  if (x==n&&x%w==1) return 1;
	  if (x==w&&n<2*w) return 1;
	  return 0;
}
void dfs(int n,int x,int sum)
{
	  if (n==1) { 
	  ans=min(ans,sum);
	 return; 
	 }
	  if (check(n,x)) 
	  {
	  	  ans=min(ans,sum+1);
	  	  return;
	  }
      if (sum==2) return;
      int xx=(x-1)/w+1,yy=(x-1)%w+1,i,j,ax=(n-1)/w+1,ay=(n-1)%w+1; 
      //down
      dfs(min(n,xx*w),x,sum+1);
      //up 
      for (i=1;i<xx;++i)
        for (j=1;j<=w;++j) 
           dfs(n-i*j,x-i*j,sum+1);         
      //left
         for (i=1;i<=xx;++i)
           for (j=1;j<yy;++j)
             dfs(n-j*(ax-i)-min(ay,j),x-j*(xx-i+1),sum+1);
      //right
         for (i=1;i<=xx;++i)
           for (j=1;j+yy<=w;++j) 
             dfs(n-j*(ax-i)-min(j,max(ay-yy,0)),x-(xx-i)*j,sum+1);
}
class FoxAndAvatar{
	public:
		int minimalSteps(int n,int width,int x)
		{
			    w=width;
			    dfs(n,x,0);
			    return ans;
		}
}FFT;

