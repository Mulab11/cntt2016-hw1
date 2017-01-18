#line 2 "LittleElephantAndBalls.cpp"
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
class LittleElephantAndBalls {
	public:
		int getNumber(string S) {
			int R = 0, G = 0, B = 0;
			int n = S.size(), ans = 0;
			for (int i = 0; i < n; ++i) {
				ans += min(R, 2);
				ans += min(G, 2);
				ans += min(B, 2);
				if (S[i] == 'R') ++R;
				if (S[i] == 'G') ++G;
				if (S[i] == 'B') ++B;
			}
			return ans;
		}
};
