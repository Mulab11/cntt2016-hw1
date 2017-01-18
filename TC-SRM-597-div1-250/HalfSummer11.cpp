#line 2 "LittleElephantAndString.cpp"
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
int cnt[30];
class LittleElephantAndString {
	public:
		int getNumber(string A, string B) {
			int n = A.size(), ans = -1;
			cl(cnt);
			for (int i = 0; i < n; ++i)
				++cnt[A[i] - 'A'], --cnt[B[i] - 'A'];
			for (int i = 0; i < 26; ++i)
				if (cnt[i]) return -1;
			for (int i = n - 1; i >= 0; --i) {
				int k = 0; bool flag = 1;
				for (int j = i; j < n; ++j) {
					while (k < n && A[k] != B[j]) ++k;
					if (k >= n) {
						flag = 0; break;
					} 
					++k;
				}
				if (!flag) break;
				ans = i;
			}
			return ans;
		}
};
