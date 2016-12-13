#include<bits/stdc++.h>
#define A(x,y) x=(1ll*(y)*f[i][j][k]+x)%P;
using namespace std;
int f[55][55][2505],i,j,k,P=1e9+7,e,h;
class LittleElephantAndPermutationDiv1
{
	public:
		int getNumber(int n,int K)
		{
			f[0][0][0]=1;
			for(i=0;i<n;i++)for(j=0;j<n;j++)for(e=n-i-i+j,h=i-j,k=0;k<=K;k++)
			{
				A(f[i+1][j][min(k+n+n-i-i,K)],e*(e-1));
				A(f[i+1][j+1][min(k+n-i,K)],e+e*h*2);
				A(f[i+1][j+2][k],h*h);
			}
			return f[n][n][K];
		}
};
