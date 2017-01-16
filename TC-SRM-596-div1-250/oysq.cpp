#include <bits/stdc++.h>

#define ll long long
#define uint unsigned

#define debug(...) fprintf(stderr, __VA_ARGS__)

#define SZ(x) ((int)(x).size())
#define pb push_back

#define pii std::pair<int,int>
#define mp std::make_pair
#define fi first
#define se second

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(y < x) x = y;}

template<class T>
inline void read(T &x) {
	char c;int f = 1;x = 0;
	while(((c = getchar()) < '0' || c > '9') && c != '-');
	if(c == '-') f = -1;else x = c - '0';
	while((c = getchar()) >= '0' && c <= '9') x = x * 10 + c - '0';
	x *= f;
}

const int V = 1000;
const int LOG = 10;
const int INF = 0x3f3f3f3f;

int f[V + 9][LOG + 9];// f[i][j]表示用了至多j次倍增操作，为了得到i，最少+1操作次数

class IncrementAndDoubling {
public:
	int getMin(std::vector <int> aim) {
		memset(f, INF, sizeof f);
		// dp，先dp出 = j的，然后求个前缀最小值
		for(int i = 0; i <= LOG; ++i) f[0][i] = i;
		for(int i = 1; i <= V; ++i)
			for(int j = 0; j <= LOG; ++j) {
				f[i][j] = f[i - 1][j] + 1;// +1操作
				if(j && !(i & 1)) chkmin(f[i][j], f[i >> 1][j - 1]);// 倍增操作
			}
		for(int i = 0; i <= V; ++i)
			for(int j = 1; j <= LOG; ++j)
				chkmin(f[i][j], f[i][j - 1]);
		int ans = INF;
		for(int i = 0; i <= LOG; ++i) {// 枚举倍增次数
			int cnt = i;
			for(auto x : aim) cnt += f[x][i];// 对每个元素计算代价
			chkmin(ans, cnt);
		}
		return ans;
	}
};
