#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

int cnt[100000];

class TheSquareRootDilemma
{
public:
	int countPairs(int N, int M)
	{
		for(int i = 1; i <= N; ++i)
		{
			int x = i, v = 1;
			for(int k = 2; k * k <= x && x != 1; ++k) if(x % k == 0)
			{
				bool c = 0;
				while(x % k == 0) x /= k, c = !c;
				if(c) v *= k;
			}
			++cnt[v * x];
		}
		int ans = 0;
		for(int i = 1; i <= M; ++i)
		{
			int x = i, v = 1;
			for(int k = 2; k * k <= x && x != 1; ++k) if(x % k == 0)
			{
				bool c = 0;
				while(x % k == 0) x /= k, c = !c;
				if(c) v *= k;
			}
			ans += cnt[v * x];
		}
		return ans;
	}
}	user;
