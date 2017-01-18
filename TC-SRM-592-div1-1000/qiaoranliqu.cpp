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
#include<complex>

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
const double pi=acos(-1.0);
int i,j,m,n,p,k,A[N],ans[N],F[N],x[N];
complex<double> W[N][2],B[N],C[N],D[N],E;
void IDFT()
{
		int i,j;
		for (i=0;i<n;++i)
		{
				D[i]=E;
				for (j=0;j<n;++j) 
				D[i]+=W[(i*j)%n][1]*C[j];
				D[i]/=(double)n; 
		}
}
bool bi()
{
		int i;
		for (i=0;i<n;++i) if (ans[i]!=x[i]) return x[i]<ans[i];
		return 0; 
}
void check(vector<int> amount)
{
	    int i,j; 
		for (i=0;i<n;++i) x[i]=(int)(D[i].real()+0.5);
		for (i=0;i<n;++i) if (x[i]<0) return;
		memset(F,0,sizeof(F));
		for (i=0;i<n;++i)
		{
				for (j=0;j<n;++j) F[(i+j)%n]+=x[i]*x[j];
		}
		for (i=0;i<n;++i) if (F[i]!=amount[i]) return;
		for (i=1;i<n;++i) if (x[i]!=x[n-i]) return;
		if (ans[0]==-1||bi())
		for (i=0;i<n;++i) ans[i]=x[i];
}
class SplittingFoxes2{
	public:
	vector <int> getPattern(vector <int> amount)
	{
			n=(int)amount.size();
			for (i=0;i<n;++i)
			{
				W[i][0]=polar(1.0,2*pi*i/n);
				W[i][1]=polar(1.0,-2*pi*i/n);
			}
			for (i=0;i<n;++i)
			{
					for (j=0;j<n;++j)
						B[i]+=W[(i*j)%n][0]*(double)amount[j];
					B[i]=sqrt(B[i]);
			}
			int lim=(n+2)>>1;
			memset(ans,-1,sizeof(ans));
			for (i=0;i<1<<lim;++i)
			{
					for (j=0;j<n;++j) C[j]=B[j]; 
					for (j=0;j<lim;++j)
						if (i&(1<<j))	C[j]=C[(n-j)%n]=-C[j];
					IDFT();
					check(amount);
			}
			vector<int> Ans;
			if (ans[0]==-1)
			{
				 Ans.pb(-1);
				 return Ans;
			}
			for (i=0;i<n;++i) Ans.pb(ans[i]);
			return Ans; 
		}
}MRT;

int main()
{
	 MRT.getPattern({0, 2, 1, 0, 3, 0, 1, 2});
}

