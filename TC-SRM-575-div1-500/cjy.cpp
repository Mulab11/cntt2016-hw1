#include <algorithm>
using namespace std;
int n,s,a[2333],i;
double t=1,r;
class TheSwapsDivOne
{
	public:
		double find(vector<string> S,int K)
		{
			for(auto x : S)for(auto y : x)a[++n]=y-48,s+=a[n];
			for(;i<K;i++)t=t*(n-3)/(n-1);
			for(i=n;i;i--)r+=(t*a[i]+(1-t)*s/n)*i*(n-i+1);
			return r*2/n/(n+1);
		}
};
