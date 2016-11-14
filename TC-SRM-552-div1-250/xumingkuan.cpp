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
#include <cctype>
#include <queue>
#include <map>
using namespace std;

class FoxPaintingBalls
{
	public:
	long long theMax(long long R, long long G, long long B, int N)
	{
		if(N == 1)
			return R + G + B;//num = 0, avoid "/ num"
		long long ans = 0;
		const long long tot = (long long)N * (N + 1) / 2;
		const long long num = tot / 3;
		long long a[3] = {R, G, B};
		sort(a, a + 3);
		if(tot % 3 == 0)
			return a[0] / num;
		long long tmp;
		if(tot % 3 == 1)//e.g. 3, 3, 4
		{
			tmp = min(a[2] - a[1], a[0] / num);//while(a[2] > a[1])paint(3, 3, 4);
			ans += tmp;
			a[0] -= tmp * num;
			a[1] -= tmp * num;
			a[2] -= tmp * (num + 1);
			tmp = min((a[1] - a[0]) * 2, a[0] / num);//while(a[1] > a[0])paint(3, 3, 4), paint(3, 4, 3);
			ans += tmp;
			a[0] -= tmp * num;
			a[1] -= tmp * num + tmp / 2;
			a[2] -= tmp * num + tmp / 2;
			ans += a[0] * 3 / tot;//paint(3, 3, 4), paint(3, 4, 3), paint(4, 3, 3);
		}
		else//e.g. 4, 5, 5 //actually impossible...
		{
			tmp = min(a[1] - a[0], a[0] / num);//while(a[1] > a[0])paint(4, 5, 5);
			ans += tmp;
			a[0] -= tmp * num;
			a[1] -= tmp * (num + 1);
			a[2] -= tmp * (num + 1);
			tmp = min((a[2] - a[1]) * 2, a[0] * 2 / (2 * num + 1));//while(a[2] > a[1])paint(4, 5, 5), paint(5, 4, 5);
			ans += tmp;
			a[0] -= tmp * num + tmp / 2;
			a[1] -= tmp * num + tmp / 2;
			a[2] -= tmp * (num + 1);
			ans += a[0] * 3 / tot;//paint(4, 5, 5), paint(5, 4, 5), paint(5, 5, 4);
		}
		return ans;
	}
};

