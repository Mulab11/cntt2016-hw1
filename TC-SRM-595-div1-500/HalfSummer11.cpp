#line 2 "LittleElephantAndRGB.cpp"
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
#define maxn 2600
typedef long long ll;
using namespace std;
int Lm[maxn], L[maxn], Rm[maxn], R[maxn];
class LittleElephantAndRGB {
	public:
		long long getNumber(vector <string> list, int mG) {
			ll ans = 0;
			string S = "";
			for (int i = 0; i < list.size(); ++i)
				S = S + list[i];
			int n = S.size();
			for (int i = 0; i < n; ++i) {
				if (S[i] != 'G') 
					L[i] = i + 1;
				else {
					if (i) 
						L[i] = L[i - 1];
					else
						L[i] = i;
				}
			}
			for (int i = n - 1; i >= 0; --i) {
				if (S[i] != 'G') 
					R[i] = i - 1;
				else {
					if (i < n - 1)
						R[i] = R[i + 1];
					else
						R[i] = i;
				}
			}
			for (int i = 0; i < n; ++i) {
				int now = (S[i] == 'G');
				Lm[i] = -1;
				if (now && mG == 1) 
					Lm[i] = i;
				else {
					for (int j = i - 1; j >= 0; --j) {
						if (S[j] == 'G') {
							++now;
							if (now == mG) {
								Lm[i] = j; break;
							}
						} else {
							now = 0;
						}
					}
				}
				Rm[i] = -1;
				now = (S[i] == 'G');
				if (now && mG == 1) 
					Rm[i] = i;
				else {
					for (int j = i + 1; j < n; ++j)
						if (S[j] == 'G') {
							++now;
							if (now == mG) {
								Rm[i] = j; break;
							}
						} else {
							now = 0;
						}
				}
			}
			for (int x = 0; x < n; ++x) 
				for (int y = x + 1; y < n; ++y) {
					if (Lm[x] != -1) 
						ans += 1ll * (Lm[x] + 1) * (n - y);
					if (Rm[y] != -1) 
						ans += 1ll * (x + 1) * (n - Rm[y]);
					if (Lm[x] != -1 && Rm[y] != -1)
						ans -= 1ll * (Lm[x] + 1) * (n - Rm[y]);
					int a = min(x - L[x] + 1, mG - 1), ua = x + 1;
					if (Lm[x] != -1) ua = x - Lm[x];
					if (a <= 0) continue;
					int b = min(R[y] - y + 1, mG - 1), ub = n - y;
					if (Rm[y] != -1) ub = Rm[y] - y;
					if (b <= 0) continue;
					if (a + b < mG) continue;
					int beg = ub - (mG - max(1, mG - b)) + 1, end = ub - (mG - a) + 1;
					if (beg <= end)
						ans += 1ll * (beg + end) * (end - beg + 1) / 2;
					beg = ua - a;
					if (beg <= 0) continue;
					ans += 1ll * beg * (ub - (mG - a) + 1);
				}
			return ans;
		}
};
