#line 2 "FoxAndMountainEasy.cpp"
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
class FoxAndMountainEasy {
	public:
		string possible(int n, int h0, int hn, string history) {
			int m = history.size();
			if (m > n) return "NO";
			int B = 0, H = 0; // B为history一段中，最低点距离起始点的距离，H为结束点海拔 - 起时点海拔
			for (int i = 0; i < m; ++i) {
				if (history[i] == 'U') ++H; else --H;
				B = max(B, -H);
			}
			if (abs(hn - h0 - H - (n - m)) % 2) return "NO"; // 需要用n - m步走出hn - h0 - H的海拔差，因为每步都必须往上/往下，所以n - m与hn - h0 - H的奇偶性必须相同
			for (int H1 = B - h0; H1 <= n - m; ++H1) { // 枚举history前，走的净海拔高度H1，为了使得history一段中的最低点h0 + H1 - B不小于0，H1至少为B - h0
				int H2 = hn - h0 - H - H1; // 则history后，走的净海拔高度为H2
				if (abs(H1) + abs(H2) <= n - m) // H1与H2需要在n - m步内完成
					return "YES";
			}
			return "NO";
		}
};
