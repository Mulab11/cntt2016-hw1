#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
 
class SpaceWarDiv1
{
	public:
	vector<int> A,B;
	vector<LL> C;
	int n,m;
	
	bool check(LL s)
	{
		LL r[55];
		memset(r,0,sizeof(r));
		for(int i=0;i<n;i++)
			r[i]=s;
		//Use girls with in increasing strength order.
		for(int i=m-1;i>=0;i--)
		{
			LL t=C[i],w;
			for(int j=0;j<n;j++)
				if(r[j]>0&&B[i]<=A[j])
				{
					w=min(t,r[j]);
					t-=w;
					r[j]-=w;
				}
			if(t>0)return 0;
		}
		return 1;
	}
	
	LL minimalFatigue(vector <int> magicalGirlStrength, vector <int> enemyStrength, vector<LL> enemyCount)
	{
		A=magicalGirlStrength,B=enemyStrength;
		C=enemyCount;
		n=A.size(),m=B.size();
		//Sort enemies be strength. 
		for(int i=m;i>0;i--)
			for(int j=0;j+1<i;j++)
				if(B[j]>B[j+1])
					swap(B[j],B[j+1]),swap(C[j],C[j+1]);
		sort(A.begin(),A.end());
		LL low=0,high=1LL<<60,mid;
		//Use dichotomy to get minimum F.
		while(low+1<high)
		{
			mid=low+high>>1;
			if(check(mid))high=mid;
			else low=mid;
		}
		return high<1LL<<59?high:-1;
	}
};

