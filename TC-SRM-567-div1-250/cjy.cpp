#include<bits/stdc++.h>
using namespace std;
int i,j,d[99999],s;
class TheSquareRootDilemma//考虑平方因子
{
	public:
		int countPairs(int n,int m)
		{
			for(i=2;i*i<=n;i++)for(j=i*i;j<=n;j+=i*i)d[j]=1;
			for(i=1;i<=min(n,m);i++)s+=!d[i]*(int)sqrt(n/i)*(int)sqrt(m/i);
			return s;
		}
};
