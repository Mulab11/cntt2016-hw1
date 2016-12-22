#include <algorithm>
using namespace std;
class FoxPaintingBalls
{
public:
	long long theMax(long long r, long long g, long long b, int n)
	{
		long long sum=r+g+b;
		if(r>g)swap(r,g);
		if(r>b)swap(r,b);
		if(g>b)swap(g,b);
		long long tgt=1LL*n*(n+1)/6;
		if(n==1)
			return r+g+b;
		if(n%3==1)
		{
			long long zuo=0,you=r/tgt+1,zhong;
			while(zuo+1<you)
			{
				zhong=(zuo+you)/2;
				if(zhong<=sum-tgt*zhong*3)
					zuo=zhong;
				else
					you=zhong;
			}
			return zuo;
		}
		return r/tgt;
	}
};
