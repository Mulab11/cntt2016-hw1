#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>

#define N 45

using namespace std;

const int Mo=(int)1e9+7;
int i,j,m,n,p,k,sum,f[N][N*N],C[1505][1505];

int workt(int x,int y)
{
	  return C[x+y-1][y];
}
void jia(int &x,int y) {x+=y;if(x>=Mo)x-=Mo; }
class LISNumber{
	public:
   int count(vector<int> v,int K)
   {
   	 n=v.size();
     f[0][sum=v[0]]=1;
     for (i=0;i<=1500;++i)
     {
     	  C[i][0]=1;
     	  for (j=1;j<=i;++j) C[i][j]=(C[i-1][j]+C[i-1][j-1])%Mo;
     }
     for (i=1;i<n;sum+=v[i],++i)
       for (j=0;j<=sum;++j)
	     if (f[i-1][j])
	       for (k=0;k<=v[i]&&k<=j;++k)
	         jia(f[i][j+v[i]-k],1ll*f[i-1][j]*C[j][k]%Mo*workt(sum+1-j+k,v[i]-k)%Mo);
	 return f[n-1][K];
   }
};
