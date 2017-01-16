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

const int N = 1e6;
const int MOD = 1000000007;

int f[N + 9];

class TrafficCongestion {
public:
	int theMinCars(int h) {
		//f[i] 表示 h = i 的答案
		// f[i] = 1 + 2 * sigma{f[j], j <= i - 2}
		f[0] = f[1] = 1;
		for(int i = 2, pre = 0; i <= h; ++i) {
			(pre += f[i - 2]) %= MOD;
			f[i] = (1 + 2 * pre) % MOD;
		}
		return f[h];
	}
};
