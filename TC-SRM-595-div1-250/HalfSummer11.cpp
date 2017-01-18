#line 2 "LittleElephantAndIntervalsDiv1.cpp"
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
bool vis[maxn];
class LittleElephantAndIntervalsDiv1 {
	public:
		long long getNumber(int M, vector <int> L, vector <int> R) {
			cl(vis);
			int n = L.size(); ll ans = 1ll;
			for (int i = n - 1; i >= 0; --i) {
				bool flag = 0;
				for (int j = L[i]; j <= R[i]; ++j)
					if (!vis[j]) {
						flag = 1; vis[j] = 1;
					}
				if (flag) ans *= 2ll;
			}
			return ans;
		}
};
