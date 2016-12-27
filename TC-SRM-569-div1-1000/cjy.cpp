#include<bits/stdc++.h>
#define LL long long
using namespace std;
int _p[11]={0,0,2,3,2,5,3,7,2,3,5},_a[11]={0,0,1,1,2,1,1,1,3,2,1},n,m,i,j,k,p;
LL P=1e9+9;
struct MX{LL x[20][20];}e,o,S,x;
MX CF(MX x,MX y)
{
	MX z=e;
	for(i=0;i<=m;i++)for(j=0;j<=m;j++)for(k=0;k<=m;k++)z.x[i][j]=(x.x[i][k]*y.x[k][j]+z.x[i][j])%P;
	return z;
}
MX PW(MX x,int y)
{
	MX z=o;
	while(y--)z=CF(z,x);
	return z;
}
class MegaFactorial//矩阵乘法
{
	public:
		int countTrailingZeros(int N,int M,int B)
		{
			for(P*=_a[B],p=_p[B],m=M,n=N;i<=m;i++)for(o.x[i][i]=1,j=i;j<=m;j++)x.x[i][j]=(i>0);
			for(x.x[0][0]=1,S=o;n;n/=p)for(S=CF(PW(x,n%p),S),x=PW(x,p),i=1;i<=m;i++)x.x[0][i]++;
			return S.x[0][m]/_a[B];
		}
};
