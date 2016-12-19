#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

const int mod = 1e9 + 7;
unsigned f[1000010][2];

class TrafficCongestion
{
public:
	int theMinCars(int N)
	{
		f[0][0] = f[0][1] = 1;
		f[1][0] = 1;
		f[1][1] = 2;
		for(int i = 2; i <= N; ++i)
		{
			f[i][0] = (f[i - 1][1] + f[i - 1][1] - 1) % mod;
			f[i][1] = (f[i - 1][0] + f[i - 1][1]) % mod;
		}
		return (f[N][0] + mod) % mod;
		
	}
}	user;
