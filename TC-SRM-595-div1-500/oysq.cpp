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

const int N = 2500;

bool ok[N + 9][N + 9];// ok[i][j] = true表示区间[i, j]是nice的
int s1[N + 9];// s1表示区间左端点 >= i的nice区间数
int s2[N + 9][N + 9];// s2[i][j]表示区间左端点 >= i且区间前缀有 >= j个G的非nice区间
int suf[N + 9];// suf[i]表示从i往前最长连续的G的数量

class LittleElephantAndRGB {
public:
	ll getNumber(std::vector <std::string> l, int g) {
		memset(ok, false, sizeof ok);
		memset(s1, 0, sizeof s1);
		memset(s2, 0, sizeof s2);
		memset(suf, 0, sizeof suf);
		std::string s;
		for(auto i : l) s += i;
		int n = SZ(s);
		for(int i = 0; i < n; ++i)
			for(int j = i; j < n; ++j)
				if(s[j] == 'G') {
					int k = j;
					while(k < n - 1 && s[k + 1] == 'G') ++k;
					if(k - j + 1 >= g) {// 有长度 >= g的连续G
						s1[i] += n - (j + g - 1);// 更新s1
						for(int p = j + g - 1; p < n; ++p)// 更新ok
							ok[i][p] = true;
						break;
					}
					j = k;
				}
		for(int i = n - 2; i >= 0; --i) s1[i] += s1[i + 1];//求前缀和
		for(int i = 0; i < n; ++i) {
			int j = i - 1;
			while(j < n - 1 && s[j + 1] == 'G') ++j;
			for(int k = i; k <= j; ++k) s2[i][k - i + 1] += 1 - ok[i][k];// 前缀k - i + 1个G
			for(int k = j + 1; k < n; ++k) s2[i][j - i + 1] += 1 - ok[i][k];// 前缀j - i + 1个G
			// -ok[i][k]是为了去掉nice的区间
			if(s[i] == 'G') suf[i] = suf[i - 1] + 1;// 更新suf
		}
		for(int i = n - 1; i >= 0; --i) {// 求s2的前缀和
			for(int j = n - i; j >= 0; --j)
				s2[i][j] += s2[i][j + 1];
			for(int j = 0; j <= n - i; ++j)
				s2[i][j] += s2[i + 1][j];
		}
		ll ans = 0;
		for(int i = 0; i < n; ++i)
			for(int j = i; j < n; ++j)
				// 对于[a, b], [c, d]，要么[a, b]就是nice的，后面随便选
				// 要么[a, b]和[c, d]中间合成了一个且[c, d]非nice，要么[c, d]nice
				if(ok[i][j]) ans += (n - j) * (n - j - 1) / 2;
				else ans += s2[j + 1][g - std::min(j - i + 1, suf[j])] + s1[j + 1];
		return ans;
	}
};
