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

const int N = 1000;

int col[N + 9];

class LittleElephantAndIntervalsDiv1 {
public:
	ll getNumber(int n, std::vector <int> l, std::vector <int> r) {
		// col[i]表示位置i最后被覆盖的区间编号
		memset(col, -1, sizeof col);
		for(int i = 0; i < SZ(l); ++i)
			for(int j = l[i]; j <= r[i]; ++j)
				col[j] = i;
		// col相同的位置颜色相同
		std::set<int> s;
		for(int i = 1; i <= n; ++i) s.insert(col[i]);
		s.erase(-1);// 去掉没被覆盖的
		return 1ll << SZ(s);// 每个集合都有两种选择
	}
};
