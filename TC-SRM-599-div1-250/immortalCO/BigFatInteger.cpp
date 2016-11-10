#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

class BigFatInteger
{
public:
	int minOperations(int A, int B)
	{
		// 对 A 进行因数分解
		int ans = 0, cnt = 0;
		for(int p = 2; A != 1; ++p) if(A % p == 0)
		{
			int c = 0;
			++cnt;
			while(A % p == 0) A /= p, c += B;
			int k = 31 - __builtin_clz(c);
			k += (c != (1 << k));
			if(k > ans) ans = k;
		}
		return ans + cnt;
	}
}	user;
