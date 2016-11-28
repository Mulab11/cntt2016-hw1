#include <algorithm>
using namespace std;
class FoxPaintingBalls
{
public:
	long long theMax(long long r, long long g, long long b, int n)
	{
		if(g > b)
			swap(g, b);
		if(r > g)
			swap(r, g);
		if(g > b)
			swap(g, b);
		long long base = (long long)n * (n + 1) / 6;
		if(n == 1)
			return r + g + b;
		if(n % 3 == 1)
			return min(r / base, (r + g + b) / (base * 3 + 1));
		return r / base;
	}
};
