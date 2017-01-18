#line 2 "TheBrickTowerEasyDivOne.cpp"
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
#define maxn 
typedef long long ll;
using namespace std;
class TheBrickTowerEasyDivOne {
	public:
		int find(int rC, int rH, int bC, int bH) {
			if (rH == bH) { // 若两种积木一样高，那么方案数 = 塔中积木最多块数
				if (rC == bC) return rC + bC;
				return min(rC, bC) * 2 + 1;
			} else {
				int ans = min(rC, bC); // 若两种积木不一样高，塔的高度有三种情况：n(rH + bH), n(rH + bH) - rH, n(rH + bH) - bH, 其中n >= 1, 因为rH != bH, 所以不会有一种高度同时属于多种情况，直接把三种情况加起来就可以了。
				ans += min(rC - 1, bC) + 1;
				ans += min(rC, bC - 1) + 1;
				return ans;
			}
		}
};

