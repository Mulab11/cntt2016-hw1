//============================================================================
// Author       : Sun YaoFeng
//============================================================================

#include <stdio.h>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

#define N4	31622
#define N3	1000000
#define I64	long long

bool	P2[N3+5],P3[N4+5];
int		*cnt[N4+5];
vector<int>F[N4+5];

void	Pre(){	//预处理质数幂次的信息
		memset(P2,1,sizeof(P2));
		memset(P3,1,sizeof(P3));
		for	(int i=2;i*i<=N3;i++)
		for	(int t=i*i;t<=N3;t+=i*i)	P2[t]=0;
		for	(int i=2;i*i*i<=N4;i++)
		for	(int t=i*i*i;t<=N4;t+=i*i*i)P3[t]=0;
		for	(int i=1;i<=N4;i++){
			int l=N3/i;
			cnt[i]=new int[l+1];	cnt[i][0]=0;
			for	(int j=1;j<=l;j++)	cnt[i][j]=cnt[i][j-1]+P2[i*j];
		}
		for	(int i=2;i<=N4;i++)	if	(F[i].empty())
		for	(int j=i;j<=N4;j+=i)F[j].push_back(i);
}

int		sqrt2(I64 N){	//开根
		int l=1,r=1e9;
		for	(;l+1<r;){
			int Mid=l+r>>1;
			(1ll*Mid*Mid<=N)?l=Mid:r=Mid;
		}	return	l;
}
int		sqrt3(I64 N){	//开三次方根
		int l=1,r=N3;
		for	(;l+1<r;){
			int Mid=l+r>>1;
			(1ll*Mid*Mid*Mid<=N)?l=Mid:r=Mid;
		}	return	l;
}

I64		Calc(I64 N){
		I64	Ans=0;
		for	(int i=1;1ll*i*i*i<=N;i++)
			if	(P2[i])	Ans+=sqrt2(N/i)-i;
		for	(int b=1;1ll*b*b*b*b<=N;b++)
		if	(P3[b]){
			for	(int k=1;k*k*k<=b;k++){
				int g=__gcd(b,k*k),b_=b/g,k_=k*k/g;
				if	(!P2[b_])	continue;
				int L=b,R=sqrt3(N/b),siz=F[b_].size(),sta=1<<siz;
				for	(int i=0;i<sta;i++){
					int d=1,u=1;
					for	(int j=0;j<siz;j++)
						if	(i>>j&1)	d*=F[b_][j],u=-u;
					Ans+=u*(cnt[d][R/k_/d]-cnt[d][L/k_/d]);
				}
			}
		}	return	Ans;
}

class	SemiPerfectPower{
	public:
		I64	count(long long L, long long R)	{
			Pre();
			return	Calc(R)-Calc(L-1);	//前缀答案相减
		}
};