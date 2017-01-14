#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
const int N=3333,M=555555555;

inline void up(int &x,const int &y)
{x+=y;if(x>=M)x-=M;}

class XorBoard
{
	public:
	int C[N+5][N+5];
	
	int calc(int n,int m,int k)//chose m repeatable objects from n objects among which exactly k objects are chosen odd times.
	{
		if(k>m||k>n||m-k&1)return 0;
		return (LL)C[n][k]*C[n+(m-k>>1)-1][n-1]%M;
	}
	
	int count(int H,int W,int Rcount,int Ccount,int S)
	{
		for(int i=0,j;i<=N;i++)
			for(C[i][0]=C[i][i]=j=1;j<i;j++)
				C[i][j]=C[i-1][j-1],up(C[i][j],C[i-1][j]);
		int ans=0;
		//Pick R,C that exactly R rows are flipped odd times and C colomns are flipped odd times.
		for(int R=0;R<=H;R++)
			for(int C=0;C<=W;C++)
				if(R*W+C*H-R*C*2==S)
					up(ans,(LL)calc(H,Rcount,R)*calc(W,Ccount,C)%M);//use the combinimal number to count the way.
		return ans;
	}
};


