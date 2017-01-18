#include<cstdio>
#include<algorithm>
#include<cstring>
#include<string>

#define N 55

using namespace std;
const int Mo=(int)1e9+7;
int i,j,m,n,p,k,f[N][N][N*N],ans;
void jia(int &x,int y) { x+=y; if(x>=Mo) x-=Mo;}
int fac(int x)
{
	  int i,sum=1;
	  for (i=1;i<=x;++i) sum=1ll*sum*i%Mo;
	  return sum;
}
class LittleElephantAndPermutationDiv1{
   public:
    int getNumber(int n,int K)
    {
    	 f[0][0][0]=1;
    	 for(i=0;i<n;++i)
    	   for (j=0;j<=i;++j)
    	     for (k=0;k<=n*i;++k)
    	        if (f[i][j][k])
    	        {
    	        	   jia(f[i+1][j][k+(i+1)],f[i][j][k]);
    	        	   jia(f[i+1][j][k+(i+1)],1ll*f[i][j][k]*j%Mo);
    	        	   jia(f[i+1][j+1][k],f[i][j][k]);
    	        	   jia(f[i+1][j][k+(i+1)],1ll*f[i][j][k]*j%Mo);
    	        	   jia(f[i+1][j-1][k+(i+1)+(i+1)],1ll*f[i][j][k]*j*j%Mo);
    	        }
    	for (i=K;i<=n*n;++i) jia(ans,f[n][0][i]);
    	return 1ll*ans*fac(n)%Mo;
    }
};

