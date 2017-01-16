#line 2 "YetAnotherBoardGame.cpp"  
#include <bits/stdc++.h> 

using namespace std;  

#define ui unsigned
#define ll long long

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

#define SZ(x) (int)(x).size()
#define pb push_back

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

const int N = 13;

int n, m;
int g[N + 9], tg[N + 9];

int opt1(int s, int T) {// 假设都是type1
	return (s ^ (T >> 1) ^ (T << 1)) & ((1 << m) - 1);
}

int opt2(int s, int T, int f) {// 然后把type2的影响加上去
	return s ^ (T & f);
}

void opt(int i, int T, int f) {// 对第i行，集合T进行操作，f表示每一列的type
	if(i) g[i - 1] ^= T;
	g[i] = opt2(opt1(g[i], T), T, f);
	if(i < n - 1) g[i + 1] ^= T;
}

class YetAnotherBoardGame {  
public:  
	int minimumMoves(vector <string> board) {
		n = SZ(board), m = SZ(board[0]);
		for(int i = 0; i < n; ++i) {
			g[i] = 0;
			for(int j = 0; j < m; ++j)
				g[i] += (ll)(board[i][j] == 'W') << j;
			tg[i] = g[i];
		}
		int ret = 1e9;
		for(int s = 0; s < (1 << m); ++s) {// 枚举第一行操作的集合
			int res = (1 << m) - 1 - s;
			for(int c = 0; c < 2; ++c) {// 枚举操作的type
				for(int h = res; ; h = (h - 1) & res) {// 枚举剩下列的type
					int cur = 0, f = h + s * c;
					for(int i = 0; i < n; ++i) g[i] = tg[i];
					bool flag = true;
					cur += __builtin_popcount(s), opt(0, s, f);
					for(int i = 1; i < n; ++i) {
						int t = g[i - 1];
						if(!((t & f) == t || (t & ((1 << m) - 1 - f)) == t)) {// 每一行的type要相同
							flag = false;
							break;
						}
						cur += __builtin_popcount(t);
						opt(i, t, f);
					}
					if(!g[n - 1] && flag) chkmin(ret, cur);// 要能化成全0
					if(!h) break;
				}
			}
		}
		return ret == (int)1e9 ? -1 : ret;
	}  
};  
  
