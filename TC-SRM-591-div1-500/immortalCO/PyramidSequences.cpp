#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using namespace std;
typedef long long ll;
typedef long double ld;

class PyramidSequences
{
	int gcd(int a, int b) {return b ? gcd(b, a % b) : a;}
public:
	ll distinctPairs(int N, int M)
	{
		ll G = gcd(2 * N - 2, 2 * M - 2);
		// 考虑对于每个 fir 求出其 sec 有多少个
		// 显然是和自己关于 G 同余才行，有 M / G 个
		// 本来每个数都是 2M/G 个，现在 1 和 N 只出现了一次，扣除掉
		return (ll) ((N + G - 1) / G) * ((M + G - 1) / G)
		+ (ll) ((N + G - 2) / G) * ((M + G - 2) / G)
		+ (ll) ((2 * N - 2) / G) * ((2 * M - 2) / G) * ((G - 2) / 2);
	}
}	user;
