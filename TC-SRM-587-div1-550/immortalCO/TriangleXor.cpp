#include <cmath>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

class TriangleXor
{
public:
	int theArea(int N)
	{
		double ans = N + 1;
		// 枚举重叠次数进行暴力容斥
		// 后面每个系数的绝对值多加上 1，这样才是异或和
		// 然后每个面积均是底为 N、高可以算的
		for(int i = 1; i <= N; ++i)
		{
			const double h = (double) N / (N + i);
			(i % 2 == 0)
			? ans += 2 * h * (N - i + 1)
			: ans -= 2 * h * (N - i + 1);
		}
		return (int) (N * ans / 2);
	}
}	user;
