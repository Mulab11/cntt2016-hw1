#line 2 "KingdomAndTrees.cpp"
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
#define maxn 60
typedef long long ll;
using namespace std;
int n, a[maxn];
bool check(int L) {
	int last = 0;
	// 答案确定后，每个数都可以在一个区间中任取，贪心地选择在序列上升的前提下尽量小的数字。若无法使得序列保持上升，返回0
	for (int i = 0; i < n; ++ i){
		if (last + 1 > a[i] + L) return 0; 
		last = max(last + 1, max(1, a[i] - L));
	}
	return 1;
}
class KingdomAndTrees {
	public:
		int minLevel(vector <int> h) {
			n = h.size();
			for (int i = 0; i < n; ++ i) a[i] = h[i];
			int L = 0, R = 1000000001, mid, ans = -1;
			while (L <= R) { // 二分答案，验证可行性
				mid = (L + R) >> 1;
				if (check(mid)) {
					ans = mid; R = mid - 1;
				} else {
					L = mid + 1;
				}
			}
			return ans;
		}
};

