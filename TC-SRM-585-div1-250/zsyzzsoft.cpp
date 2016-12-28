#include <algorithm>
using namespace std;
const int p = 1000000007;
class TrafficCongestion
{
public:
	int f[1000001];
	int theMinCars(int h)
	{
		h++;
		f[0] = 0, f[1] = 1;
		for(int i = 2, j = 0; i <= h; i++) //递推，前缀和 
			f[i] = (j * 2 + 1) % p, j = (j + f[i - 1]) % p;
		return f[h];
	}
};