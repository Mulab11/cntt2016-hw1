#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define N 1000010
using namespace std;
struct MayTheBestPetWin
{
	bool f[N];
	int calc(vector <int> A, vector <int> B)
	{
		int n=A.size();
		int totb=0,tota=0;
		int i,j,x,y;
		f[0]=true;
		for(i=0;i<n;i++)
		{
			totb+=B[i],tota+=A[i];
			for(j=tota+totb;j>=A[i]+B[i];j--)
			f[j]|=f[j-A[i]-B[i]];
		}
		int ans=707185547;
		for(i=0;i<=tota+totb;i++)
		if(f[i])
		ans=min(ans,max(totb-i,i-tota));
		return ans;
	} 
};