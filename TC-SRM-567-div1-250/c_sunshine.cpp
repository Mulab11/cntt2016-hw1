#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;

class TheSquareRootDilemma
{
	public:
	int f[88888];
	int rms(int x)
	{
		for(int i=2;i*i<=x;i++)
			while(x%(i*i)==0)x/=i*i;
		return x;
	}
	int countPairs(int N,int M)
	{
		//After removing all square factor from the number a and b,
		//SSR(a,b) is integer if and only if a=b.
		for(int i=1;i<=N;i++)
			f[rms(i)]++;
		int ans=0;
		for(int i=1;i<=M;i++)
			ans+=f[rms(i)];
		return ans;
	}
	
};

