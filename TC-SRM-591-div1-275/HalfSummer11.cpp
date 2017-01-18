#line 2 "TheTree.cpp"
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
int a[maxn], b[maxn], D;
class TheTree {
	public:
		int maximumDiameter(vector <int> cnt) {
			D = cnt.size(); 
			for (int i = 0; i < D; ++i) a[i + 1] = cnt[i];
			a[0] = 1; int ans = 0;
			for (int x = 0; x <= D; ++x)
				for (int y = 0; y <= D; ++y) {
					memcpy(b, a, sizeof(a));
					bool flag = 1;
					for (int i = 0; i <= x; ++i)
						if (!b[i]) flag = 0;
					for (int i = 0; i <= y; ++i)
						if (!b[i]) flag = 0;
					if (!flag) continue;
					for (int i = 0; i <= x; ++i) --b[i];
					for (int i = y; i >= 0; --i) {
						if (!b[i]) {
							ans = max(ans, x + y - 2 * i);
							break;
						}
					}
				}
			return ans;
		}
};
