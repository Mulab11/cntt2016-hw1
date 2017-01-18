#line 2 "CuttingBitString.cpp"
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
int n, f[maxn]; // f[i]表示把前i位合法分割最少能割成几段
string s;
void upd(int &a, int b) {
	if (b < a) a = b;
}
bool check(int l, int r) { // [l, r]能否合法分成一段
	if (s[l] == '0') return 0; // 不能有前导0
	ll now = 0;
	for (int i = l; i <= r; ++i)
		now = (now << 1ll) | (s[i] - '0');
	while (now != 1ll) { // 需要是5的幂
		if (now % 5ll) return 0;
		now /= 5ll;
	}
	return 1;
}
class CuttingBitString {
	public:
		int getmin(string S) {
			memset(f, 0x3f, sizeof(f));
			n = S.size(); s = S;
			f[0] = 0;
			for (int i = 1; i <= n; ++i)
				for (int j = 0; j < i; ++j) // 枚举上一个分割位置转移
					if (check(j, i - 1)) upd(f[i], f[j] + 1);
			if (f[n] > n) return -1;
			return f[n];
		}
};

