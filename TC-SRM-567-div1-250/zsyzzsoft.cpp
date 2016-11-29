#include <algorithm>
#include <math.h>
using namespace std;
bool flag[100000];
class TheSquareRootDilemma
{
public:
	int countPairs(int n, int m)
	{
		int ans = 0;
		for(int i = 2; i * i <= n; i++)
		{
			for(int j = i * i; j <= n; j += i * i)
				flag[j] = true;
		}
		for(int i = 1; i <= n && i <= m; i++) //枚举公共约数 
			ans += !flag[i] * (int)sqrt(n / i) * (int)sqrt(m / i);
		return ans;
	}
};