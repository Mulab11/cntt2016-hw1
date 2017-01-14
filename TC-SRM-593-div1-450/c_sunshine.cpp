#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
using namespace std;

class MayTheBestPetWin
{
	public:
	int n;
	bool f[1000005],g[1000005];
	int calc(vector<int> A,vector<int> B)
	{
		n=A.size();
		int sA=0,sB=0;
		for(int i=0;i<n;i++)
			sA+=A[i],sB+=B[i];
		//sA is the sum of all elements in A, and sB is the sum of all elements in B.
		//Let tA be the sum of all elements' A in team 1, and tB is similar.
		//The maxdiff is max(tA-(sB-tB),(sA-tA)-tB)=max((tA+tB)-sB,sA-(ta+tB)), and it only depends on (tA+tB)/
		//So we can record the sum of A and B in team 1 only, which is enough.
		f[0]=1;
		//f[k]: if it is possible to pick some player in first i players and the sum of A+B is k.
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<=sA+sB;j++)
				if(f[j])
				{
					g[j]=1;
					g[j+A[i]+B[i]]=1;
				}
			memcpy(f,g,sA+sB+1);
			memset(g,0,sA+sB+1);
		}
		int ans=1<<30;
		//Pick all possible tA+tB to get the answer. 
		for(int k=0;k<=sA+sB;k++)
			if(f[k])
				ans=min(ans,max(k-sA,sB-k));
		return ans;
	}
};

