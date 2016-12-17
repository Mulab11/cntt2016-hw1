#include<bits/stdc++.h>
using namespace std;
int f[1000001],P=1e9+7,i=2;
class TrafficCongestion
{
	public:
		int theMinCars(int n)//递推		
		{
			for(f[0]=f[1]=1;i<=n;i++)f[i]=(2ll*f[i-2]+f[i-1])%P;
			return f[n];
		}
};
