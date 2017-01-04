#include<algorithm>
#include<vector>
using namespace std;
bool prime[55555]={};int n;
int num[1111111]={},sg[1111111]={},gg[333]={};
bool check(int a)
{
	for(int i=2;i*i<=a;i++)
		if(a%i==0)return false;
	return true;
}
class TheDivisionGame
{
public:
	long long countWinningIntervals(int l, int r)
	{
		for(int i=1;i<=50000;i++)
			prime[i]=check(i);
		n=r-l+1;
		for(int i=0;i<n;i++)
			num[i]=i+l;
		for(int i=2;i<50000;i++)
		{
			if(!prime[i])
				continue;
			for(long long codeforces=i;codeforces<=r;codeforces*=i)
				for(int j=((codeforces-l)%codeforces+codeforces)%codeforces;j<n;j+=codeforces)
					sg[j]++,num[j]/=i;
		}
		long long ans=0;
		for(int i=0;i<n;i++)
			if(num[i]>1)
				sg[i]++;
		gg[0]=1;
		for(int i=0,j=0;i<n;i++)
			ans+=gg[j^=sg[i]]++;
		return 1LL*n*(n+1)/2-ans;
	}
};
