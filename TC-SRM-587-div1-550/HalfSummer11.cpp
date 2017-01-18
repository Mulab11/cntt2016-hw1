#line 2 "TriangleXor.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
typedef long long ll;
using namespace std;
/*
   考虑第(i + 1)个三角形加入时，对答案的影响。第(i + 1)个三角形被前i个三角形划成了(i + 1)份，根据相似三角形，可以计算出这些分割点分别位于W / (W + i), W / (W + i - 1) ... W / (W + 1)处。
   一些三角形的面积被加上，一些三角形的面积被减去，整理得到：对于第(i + 1)个三角形，它对答案的贡献 = S * (W / W - 2W / (W + 1) + 2W / (W + 2) ... 其中S是大三角形的面积，S = W / 2
   对于W / W, -2W / (W + 1), +2W / (W + 2) ..分别计算个数，计入答案。
*/
class TriangleXor {
	public:
		int theArea(int W) {
			double ans = W + 1, S = W / 2.0; // S是一个大三角形的面积
			for (int i = 1; i <= W; ++i)
				if (i & 1)
					ans -= 2.0 * W * (W - i + 1) / (W + i); 
				else
					ans += 2.0 * W * (W - i + 1) / (W + i);
			ans *= S;
			return int(floor(ans));
		}
};
