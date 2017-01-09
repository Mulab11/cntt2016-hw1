//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define n	100005
#define P	1000000007
#define For(i,a,b)	for(int i=a;i<=b;i++)

int		N,M,X,Y,A[n],x[n],y[n],L[n],R[n];

int		Pow(int a,int b){
		int ret=1;
		for	(;b;b>>=1,a=1ll*a*a%P)
			if	(b&1)	ret=1ll*ret*a%P;
		return	ret;
}
int		C(int a,int b)	{return	1ll*L[a]*R[b]%P*R[a-b]%P;}

void	Work(int&Ans){
		For(x,-300000,300000){	//枚举相遇点，用组合数计算方案数。
			int ret=1;
			For(i,1,N){
				int t=abs(A[i]-x);
				if	(t>M||(M-t&1))	{ret=0;break;}
					else	ret=1ll*ret*C(M,(M-t)/2+t)%P;
			}	(Ans+=ret)%=P;
		}
}

class	WolfPack{
	public:
		int calc(vector <int> xx, vector <int> yy, int M){
			N= xx.size();
			::M= M;
			For(i, 1, N)	x[i]= xx[i-1], y[i]= yy[i-1];
			
			L[0]=1;
			For(i,1,M)	L[i]=1ll*L[i-1]*i%P;
			
			R[M]=Pow(L[M],P-2);
			for	(int i=M;i;i--)	R[i-1]=1ll*R[i]*i%P;	//预处理阶乘

			For(i,1,N)	A[i]=x[i]-y[i];	Work(X);	//转坐标后，分别计算X轴和Y轴的贡献。
			For(i,1,N)	A[i]=x[i]+y[i];	Work(Y);
			
			return	1ll*X*Y%P;
		}
};