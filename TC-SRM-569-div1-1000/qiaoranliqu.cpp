#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<cmath>
#include<string>

#define ls (t<<1)
#define rs ((t<<1)+1)
#define mid ((l+r)>>1)
#define fi first
#define se second
#define mk make_pair
#define pb push_back

#define N 65
#define M 200005
#define seed 23333
#define Mo 1000000009

using namespace std;
int i,j,m,n,p,k,l;
long long pw[N];
long long mo=0;
struct Matrix{
	long long A[N][N];
	void clear()
	{
		memset(A,0,sizeof(A));
	}
}B[N],A;
void jia(long long &x,long long y)
{
		x+=y; if (x>=mo) x-=mo; 
}
inline Matrix operator *(Matrix a,Matrix b)
{
		int i,j,k;
		Matrix c;c.clear();
		for (k=0;k<N;++k)
			for (i=0;i<N;++i)
				for (j=0;j<N;++j)
					jia(c.A[i][j],1ll*a.A[i][k]*b.A[k][j]%mo);
		return c;
}
int work(int x,int y)
{
		mo=1ll*Mo*y;
		for (i=k+1;i<=k+30;++i) A.A[0][i]=i-k;
		Matrix sum; sum.clear(); int f=1;
		//考虑K=0时1--N在某个质因子上的贡献,若N是p^i,那么就是p^1,p^2....p^(i-1)的矩阵复制(p-1)次再加上p^i的贡献 
		for (i=0;i<=30;++i) 
		{
				for (j=1;j<=k;++j)
					for (l=1;l<=j;++l) B[i].A[l][j]=1;
				if (i) 
					for (j=0;j<=k;++j) B[i].A[i+k][j]=1;
				for (j=k+1;j<=k+30;++j) B[i].A[j][j]=1;
				if (!f) B[i]=sum*B[i];
				for (j=1;j<x;++j)
				 if (!f) 
				 sum=B[i]*sum; 
				 else 
				 f=0,sum=B[i];
		}
		pw[0]=1;
		for (i=1;i<=30;++i) pw[i]=min(1ll*pw[i-1]*x,(long long)1e12);
		//矩阵 
		for (i=30;i>=0;--i)
			while (n>=pw[i]) 
			n-=pw[i],A=A*B[i];
		return A.A[0][k]/y;
}
class MegaFactorial{
	public:
		int countTrailingZeros(int n, int k, int B)
		{
				::n=n; ::k=k;
				//由于B<=10,那么可以把B拆分质因子,有用的只有最小的质因子的幂次(还没有出现2*3^2的情况) 
				if (B==2) return work(2,1);
				if (B==3) return work(3,1);
				if (B==4) return work(2,2);
				if (B==5) return work(5,1);
				if (B==6) return work(3,1);
				if (B==7) return work(7,1);
				if (B==8) return work(2,3);
				if (B==9) return work(3,2);
				if (B==10) return work(5,1);
				return 0;
		}
}MRT;

int main()
{
		cout<<MRT.countTrailingZeros(10,3,10);
}

