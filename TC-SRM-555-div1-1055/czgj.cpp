#include <bits/stdc++.h>
#define rep(i, l, r) for(int _r = r, i = l; i <= _r; ++i)
#define red(i, r, l) for(int _l = l, i = r; i >= _l; --i)
#define debug(x) cerr << #x << " = " << x << endl
#define MEM(x, y) memset(x, y, sizeof(x))
#define X first
#define Y second

using namespace std;
typedef long long LL;
typedef pair<int, int> PI;
const LL MOD = 1e9 + 7;
class MapGuessing{
public:
	int n;
	LL f[55];
	LL dfs(int d, LL msk, int flag){
		if (!msk){
			bool cnt = 0;
			rep(i, d, n - 1) if (f[i] != -1) cnt = 1;
			return cnt ? 0 : flag;
		}
		if (d >= n) return flag * (1ll << __builtin_popcountll(msk));
		return dfs(d + 1, msk, flag) + (f[d] != -1 ? dfs(d + 1, msk & f[d], -flag) : 0);
	}
	LL countPatterns(string _goal, vector<string> code){
		string st; LL goal = 0;
		rep(i, 0, (int)code.size() - 1) st += code[i];
		n = _goal.size();
		rep(i, 0, n - 1) if (_goal[i] == '1') goal |= 1ll << i;
		int len = st.size();
		rep(i, 0, n - 1){
			int ptr = i; LL m1 = 0, m2 = 0;
			rep(j, 0, len - 1){
				if (st[j] == '<') --ptr;
				if (st[j] == '>') ++ptr;
				if (ptr < 0 || ptr >= n){
					f[i] = -1; break;
				}
				if (st[j] == '0' || st[j] == '1'){
					m1 |= 1ll << ptr;
					if ((m2 >> ptr & 1) ^ (st[j] & 1)) m2 ^= 1ll << ptr;
					if (!(m1 & (m2 ^ goal))) f[i] = m1;
				}
			}
		}
		return dfs(0, (1ll << n) - 1, -1) + (1ll << n);
	}
};

