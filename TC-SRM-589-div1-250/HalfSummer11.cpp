#line 2 "GooseTattarrattatDiv1.cpp"
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
int n, fa[maxn], cnt[maxn];
int find(int x) {
	return fa[x] == x ? x : fa[x] = find(fa[x]);
}
void merge(int x, int y) {
	x = find(x); y = find(y);
	fa[x] = y;
}
class GooseTattarrattatDiv1 {
	public:
		int getmin(string S) {
			n = S.size();
			for (int i = 0; i < n; ++i) fa[i] = i;
			for (int i = 0; i < n; ++i)
				for (int j = i + 1; j < n; ++j)
					if (i + j == n - 1 || S[i] == S[j])
						merge(i, j);
			int ans = 0;
			for (int i = 0; i < n; ++i)
				if (find(i) == i) {
					cl(cnt); int sum = 0;
					for (int j = 0; j < n; ++j)
						if (find(j) == i) {
							++sum; ++cnt[S[j] - 'a'];
						}
					int mx = 0;
					for (int i = 0; i < 26; ++i)
						mx = max(mx, cnt[i]);
					ans += sum - mx;
				}
			return ans;
		}
};
