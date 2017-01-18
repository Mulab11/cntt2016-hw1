#line 2 "FoxAndChess.cpp"
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
int pos[2][maxn], type[2][maxn];
int calc(string s, int pos[maxn], int type[maxn]) {
	int n = 0;
	for (int i = 0; i < s.size(); ++i) {
		if (s[i] == '.') continue;
		type[++n] = (s[i] == 'L') ? -1 : 1;
		pos[n] = i;
	}
	return n;
}
class FoxAndChess {
	public:
		string ableToMove(string begin, string target) {
			int n = calc(begin, pos[0], type[0]);
			int m = calc(target, pos[1], type[1]);
			if (n != m) return "Impossible";
			for (int i = 1; i <= n; ++i) {
				if (type[0][i] != type[1][i]) return "Impossible";
				if ((pos[1][i] - pos[0][i]) * type[0][i] < 0) return "Impossible";
			}
			return "Possible";
		}
};
