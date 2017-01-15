#include<string>
#include<algorithm>
#include<vector>
using namespace std;long long a[11111]={};
int ta=0,tb=0;int n;long long c[11111]={},tc=0;
long long b[11111]={};int top[11111]={};
long long calc(int tt)
{
	int rank=0;
	for(int i=0;i<n;i++)b[i]=a[i];
	long long gug=(1LL<<tt)-1;
	long long d=0;
	for(int i=0;i<tc;i++)gug+=(1LL<<c[i]);
	for(int i=50;i>=tt;i--)
	{
		int f=0;
		for(int j=rank;j<n;j++)
			if(b[j]&(1LL<<i))
			{
				swap(b[rank],b[j]);
				f=1;top[rank]=i;break;
			}
		if(f)
		{
			for(int j=0;j<n;j++)
				if(j!=rank&&(b[j]&(1LL<<i)))
					b[j]^=b[rank];
			rank++;
		}
	}
	for(int i=0;i<rank;i++)
		if(gug&(1LL<<top[i]))d^=b[i];
	if((gug>>tt)!=(d>>tt))return 0;
		return 1LL<<n-rank;
}
class XorCards
{
public:
	long long numberOfWays(vector<long long> number, long long limit)
	{
		long long codeforces=0;n=number.size();
		for(int i=0;i<n;i++)
			a[i]=number[i];
		for(int i=50;i>=0;i--)
			if(limit&(1LL<<i))codeforces+=calc(i),c[tc++]=i;
		codeforces+=calc(0);
		return codeforces;
	}
};
