#include<cstdio>
#include<algorithm>
bool prime[1111111]={};
int ans=0;int n,m;
bool check(int a)
{
	for(int i=2;i*i<=a;i++)
		if(a%(i*i)==0)
			return false;
	return true;
}
int uu(int a)
{return (int)(sqrt(1.0*a));}
int getsum(int a,int b,int c)
{return uu(a/c)*uu(b/c);}
class TheSquareRootDilemma
{
public:
	int countPairs(int N, int M)
	{
		n=N,m=M;
		for(int i=1;i<=100000;i++)
			prime[i]=check(i);
		for(int i=1;i<=77777;i++)
			if(prime[i])
				ans+=getsum(n,m,i);
		return ans;
	}
};
