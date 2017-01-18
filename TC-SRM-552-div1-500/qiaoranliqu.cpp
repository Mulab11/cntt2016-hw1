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

#define N 55
#define M 200005
#define seed 23333
#define Mo 998244353

using namespace std;
int i,j,m,n,p,k,A[N][N],B[N][N],L[N][N*N],R[N][N*N],C[N][N],dif,D[N][N],l;
int calc()
{
	for (i=1;i<=n;++i) //对差值和两种花的和做一个前缀和 
		for (j=1;j<=m;++j)
		{
			 C[i][j]=A[i][j];
			 C[i][j]+=C[i-1][j];
			 C[i][j]+=C[i][j-1];
			 C[i][j]-=C[i-1][j-1];
			 D[i][j]=(A[i][j]!=0);
			 D[i][j]+=D[i-1][j];
			 D[i][j]+=D[i][j-1];
			 D[i][j]-=D[i-1][j-1];
		}
	for (i=0;i<=m+1;++i) 
		for (j=0;j<N*N;++j) L[i][j]=R[i][j]=-(int)1e9;
	int s=-1;
	for (i=1;i<=m;++i) //从左向右扫,枚举右边界 
	{
			for (j=0;j<N*N;++j) L[i][j]=max(L[i][j],L[i-1][j]);
			for (j=1;j<=n;++j) //枚举其他三个边界 
				for (k=1;k<=i;++k)
					for (l=1;l<=n;++l)
					{
							int sx=min(j,l),ex=max(j,l),sy=k,ey=i,
							sa=C[ex][ey]-C[sx-1][ey]-C[ex][sy-1]+C[sx-1][sy-1],
							sb=D[ex][ey]-D[sx-1][ey]-D[ex][sy-1]+D[sx-1][sy-1]; 
							L[i][sa+1000]=max(L[i][sa+1000],sb);
					}
	}
	for (i=m;i;--i) //从右向左扫,枚举左边界 
	{
			for (j=0;j<N*N;++j) R[i][j]=max(R[i][j],R[i+1][j]);
			for (j=1;j<=n;++j)
				for (k=i;k<=m;++k)
					for (l=1;l<=n;++l)
					{
							int sx=min(j,l),ex=max(j,l),sy=i,ey=k,
							sa=C[ex][ey]-C[sx-1][ey]-C[ex][sy-1]+C[sx-1][sy-1],
							sb=D[ex][ey]-D[sx-1][ey]-D[ex][sy-1]+D[sx-1][sy-1]; 
							R[i][sa+1000]=max(R[i][sa+1000],sb);
					}
	}
	for (i=1;i<m;++i) //枚举矩阵分界线 
	{
			for (j=0;j<N*N;++j)
			{
					int now=j-1000;
						for (k=max(0,-dif-now+1000);k<=min(N*N-1,dif-now+1000);++k)
						s=max(s,L[i][j]+R[i+1][k]);
			}
	}
	return s;
}
class FoxAndFlowerShopDivOne{
		public:
			int theMaxFlowers(vector <string> flowers, int maxDiff)
			{
					dif=maxDiff;
					n=flowers.size(); m=flowers[0].length();
					for (i=1;i<=n;++i)
					  for (j=1;j<=m;++j)
					  	A[i][j]=(flowers[i-1][j-1]=='L')-(flowers[i-1][j-1]=='P');
					int s=max(-1,calc());
					for (i=1;i<=n;++i)
						for (j=1;j<=m;++j)
						  B[j][i]=A[i][j];
					swap(n,m); //把矩阵翻转再做一次. 
					for (i=1;i<=n;++i)
						for (j=1;j<=m;++j) 
						 A[i][j]=B[i][j];
					return max(s,calc());
			}
}FFT;

int main()
{
	  cout<<FFT.theMaxFlowers(vector<string> {"PP", "PP"}, 3);
}

