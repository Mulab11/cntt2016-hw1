#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>
#include <queue>
using namespace std;
class AlternateColors2
{
	private:
	long long sum_of_arithmetic_sequence(int st, int ed, int d)//st, st + d, ..., ed
	{
		if(st > ed)
			return 0;
		return (long long)(st + ed) * ((ed - st) / d + 1) / 2;
	}
	public:
	long long countWays(int n, int k)
	{
		long long ans = 0;
		if(k % 3 == 1)
			ans += (long long)(n - k + 1) * (n - k + 2) / 2;//>= k / 3 + 1 red, >= k / 3 green, >= k / 3 blue, there are totally C(n - k + 2, 2) tuples of (r, g, b) such that r + g + b == n - k.
		ans += (k / 3 + (k % 3 != 1)) / 2 * (n - k + 1) * 2;//== k / 3 - (k % 3 == 1) - 1 - 2 * x(so "/2") green/blue(so "*2"), where x is a non-negative integer; >= (red - 1) blue/green.
		//for(int numRed = k / 3 + 2; numRed <= k; numRed++)//<= (red - 2) green, <= (red - 2) blue. or, it's all red after the k-th ball. this is O(n). (numRed is number of red in the first k balls)
		//	ans += max(0, min(k - numRed, numRed - 2) - max(0, (k - numRed) - (numRed - 2)) + 1);//min(...) and max(...) here are the maximum and minimum value of green.
		ans += sum_of_arithmetic_sequence(k / 3, (k - 2) / 2, 1);//add max(green)
		ans += sum_of_arithmetic_sequence(0, (k - 3) / 2, 1);//add max(green)
		ans -= sum_of_arithmetic_sequence(k % 2, k - 2 - k / 3 * 2, 2);//minus min(green)
		ans += k - k / 3 - 1;//add 1
		return ans;
	}
};

