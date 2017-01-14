#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;
const int M=1000000007;
class TrafficCongestion
{
	public:
	int f[1000005],s[1000005];
	int theMinCars(int treeHeight)
	{
		int n=treeHeight;
		f[0]=f[1]=1;
		s[0]=1;s[1]=2;
		for(int i=2;i<=n;i++)//We can prove that a best way exists if we choose a diameter first
		{//After the diameter is deleted, there remains some easier case
			//f_0=f_1=1; f_n=1+2*\sum_{i=0}^{n-2} f_i
			f[i]=(s[i-2]*2+1)%M;
			s[i]=(s[i-1]+f[i])%M;
		}
		return f[n];
	}
};

