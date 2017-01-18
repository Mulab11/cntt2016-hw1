#line 2 "JumpFurther.cpp"
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
class JumpFurther {
	public:
		int furthest(int N, int badStep) {
			for (int i = 1; i <= N; ++i)
				if (i * (i + 1) / 2 == badStep) { // 如果每次都往上跳，会经过badStep，第一次就留在原地，这样在损失最小的情况下避开了badStep
					return N * (N + 1) / 2 - 1;
				}
			return N * (N + 1) / 2; // 否则直接跳
		}
};
