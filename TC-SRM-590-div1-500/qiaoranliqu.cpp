#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>

using namespace std;

#define N 55

int i,j,m,n,p,k,lim=50,B[N][N];
long long a[N],ans;

long long gauss()
{
	   int i,j,cnt=0;
	   for (i=1;i<=n;++i)
	   {
	   	    for (j=cnt+1;j<=lim+1;++j) if (B[j][i]) break;
	   	    if (j>lim+1) continue;
	   	    ++cnt;
	   	    for (k=1;k<=n+1;++k) swap(B[j][k],B[cnt][k]);
	   	    for (j=cnt+1;j<=lim+1;++j)
	   	        if (B[j][i])
	   	         for (k=1;k<=n+1;++k) B[j][k]^=B[cnt][k];
	   }
	   for (i=cnt+1;i<=lim+1;++i)
	     if (B[i][n+1]==1) return 0;
	   return 1ll<<(n-cnt);
}
void work(long long sum,int bit)
{
	   int i,j,k;
	   memset(B,0,sizeof(B));
	   m=0;
	   for (i=lim;i>=bit;--i)
	   {
	   	    ++m;
	   	    for (j=1;j<=n;++j) if (a[j]&(1ll<<i)) B[m][j]=1;
	   	    B[m][n+1]=((sum&(1ll<<i))>0);
	   }
	   ans+=gauss();
}
class XorCards
{
    public:
    long long numberOfWays(vector<long long> A,long long k)
    {
    	     n=A.size();
    	     for (i=1;i<=n;++i) a[i]=A[i-1];
    	     work(k,0);
    	     for (i=lim;i>=0;--i)
    	       if (k&(1ll<<i)) 
    	       work((k>>(i+1))<<(i+1),i);
    	     return ans;
    }
}A;
	 
