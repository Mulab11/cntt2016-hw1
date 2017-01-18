#line 2 "TeamContest.cpp"
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
int n, b[maxn]; // n是剩余人数，b存放剩余的人的strength
bool used[maxn]; // used[i]标记第i个人是否已经被分组
class TeamContest {
	public:
		int worstRank(vector <int> a) {
			int x = max(a[0], max(a[1], a[2])) + min(a[0], min(a[1], a[2])); // 我方的strength
			cl(used);
			n = a.size() - 3;
			for (int i = 3; i < n + 3; ++i)
				b[i - 2] = a[i];
			sort(b + 1, b + n + 1);
			reverse(b + 1, b + n + 1); // 将剩下的人从大到小排序
			int ret = 1;
			for (int i = 1; i <= n; ++i) {
				if (used[i]) continue; 
				for (int j = n; j > i; --j) {
					if (used[j]) continue;
					if (b[i] + b[j] > x) { // 找到strength尽量小的，可以和i组成实力大于x的组的j
						bool flag = 0;
						for (int k = j - 1; k > i; --k)
							if (!used[k]) {
								used[k] = 1; flag = 1; break; // 找一个strength尽量小的中间值k
							}
						if (!flag) return ret; // 此时。把strength最大的三个人凑起来都无法比x大
						used[j] = 1; // 否则，就把i, j, k组成大于x的一个组
						++ret;
						break;
					}
				}
			}
			return ret;
		}
};
