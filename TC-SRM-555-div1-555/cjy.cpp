#include<bits/stdc++.h>
using namespace std;
int P=555555555,C[2555][2555],i,j,s;
class XorBoard//枚举，组合
{
	public:
		int count(int n,int m,int r,int c,int S)
		{
			for(;i<2555;i++)for(j=C[i][0]=1;j<=i;j++)C[i][j]=(C[i-1][j]+C[i-1][j-1])%P;
			for(i=r;i>=0;i-=2)for(j=c;j>=0;j-=2)if(i*m+j*n-i*j*2==S)s=(1ll*C[n][i]*C[m][j]%P*C[r-i+n+n-2>>1][n-1]%P*C[c-j+m+m-2>>1][m-1]+s)%P;
			return s;
		}
};
