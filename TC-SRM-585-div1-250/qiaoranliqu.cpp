#include<cstdio>
#include<algorithm>
#include<cstring>

#define N 1000005

using namespace std;

const int Mo=(int)1e9+7;

int f[N],sum[N],i;

class TrafficCongestion{
   public:
     int theMinCars(int n)
	 {
	     f[0]=f[1]=1;
		 sum[0]=1; sum[1]=2;
		 for (i=2;i<=n;++i)
		 {
		    f[i]=(sum[i-2]*2%Mo+1)%Mo;
			sum[i]=(sum[i-1]+f[i])%Mo;
		 }
		 return f[n];
	 }
};
