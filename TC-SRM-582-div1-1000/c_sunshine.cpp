#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<bitset> 
using namespace std;
typedef long long LL;

int gcd(const int &a,const int &b){return b?gcd(b,a%b):a;}

const LL maxn=80000000000000000ll;
const int maxn2=282842712;
const int maxn3=430886;
const int maxn4=16817;
bitset<maxn3+5> P2;
bitset<maxn4+5> P3;
int fp[maxn3+5];
vector<int> fc;
int *S[maxn3+5];

class SemiPerfectPower
{
	public:
	LL N;
	
	
	int Sqrt(LL n)
	{
		int low=0,high=maxn2+1,mid;
		while(low+1<high)
		{
			mid=(low+high)>>1;
			if((LL)mid*mid<=n)low=mid;
			else high=mid;
		}
		return low;
	}
	
	int Cbrt(LL n)
	{
		int low=0,high=maxn3+1,mid;
		while(low+1<high)
		{
			mid=(low+high)>>1;
			if((LL)mid*mid*mid<=n)low=mid;
			else high=mid;
		}
		return low;
	}
	
	void makefactor(int n)//get n's prime factors
	{
		fc.clear();
		while(n>1)
		{
			int t=fp[n];
			fc.push_back(t);
			while(n%t==0)n/=t;
		}
	}
	
	LL count_work(LL N)//Calculate the expression
	{
		this->N=N;
		if(N<1)return 0;
		LL ans=0;
		for(int a=1;(LL)a*a*a<N;a++)
			if(P2[a])
				ans+=Sqrt(N/a)-a;
		for(int b=1;(LL)b*b*b*b<N;b++)
			if(P3[b])
			{
				for(int k=1;k*k*k<=b;k++)
				{
					int g=gcd(b,k*k);
					int bb=b/g,kk=k*k/g,yl,yr;
					if(P2[bb])
					{
						yl=b/kk,yr=Cbrt(N/b)/kk;
						makefactor(bb);
						//Enumerate all factor of bb which can't be divided by any square number.
						for(int s=0,d,mu;s<1<<fc.size();s++)
						{
							d=mu=1;
							for(int i=0;i<fc.size();i++)
								if(s>>i&1)
									d*=fc[i],mu=-mu;
							ans+=mu*(S[d][yr/d]-S[d][yl/d]);
						}
					}
				}
			}
		return ans;
	}
	
	void init()
	{
		//Get p2,p3.
		for(int i=0;i<=maxn3;i++)P2[i]=1;
		for(int i=0;i<=maxn4;i++)P3[i]=1;
		for(int i=2;i*i<=maxn3;i++)
			for(int j=i*i;j<=maxn3;j+=i*i)
				P2[j]=0;
		for(int i=2;i*i*i<=maxn4;i++)
			for(int j=i*i*i;j<=maxn4;j+=i*i*i)
				P3[j]=0;
		//Find each number's minimum prime factor, so that we can do factorization fast. 
		for(int i=2;i<=maxn3;i++)
			if(!fp[i])
			{
				fp[i]=i;
				for(int j=i;j<=maxn3;j+=i)
					if(!fp[j])
						fp[j]=i;
			}
		//We can determine S[d][m] to optimize.
		//S[d][m] = \sum[1<=k<=m] p2(dk)
		//Total size of S is O(maxn3 log maxn3)
		for(int i=1;i<=maxn3;i++)
		{
			int m=maxn3/i;
			S[i]=(int*)malloc(sizeof(int)*(m+1));
			S[i][0]=0;
			for(int j=1;j<=m;j++)
				S[i][j]=S[i][j-1]+P2[i*j];
		}
	}
	
	LL count(LL L,LL R)
	{
		//After some calculation, we can get the expression of the answer
		//ans = \sum[1<=a^3<=n] p2(a)floor(sqrt(n/a)-a) - \sum[1 <=b<=n^(1/4)] p3(b) \sum[1<=k<=b^(1/3)] T
		//Let b'=b/gcd(b,k^2),k'=k^2/gcd(b,k^2)
		//and T = p2(b') \sum[d|b'] \mu(d) \sum[b/k' <y' <=(n/b)^(1/3)/k'] [d|y'] p2(y')
		//p2(x) = [There doesn't exist k \in Z satisfying k^2|x]
		//p3(x) = [There doesn't exist k \in Z satisfying k^3|x]
		N=R;
		init();
		return count_work(R)-count_work(L-1);
	}
};

