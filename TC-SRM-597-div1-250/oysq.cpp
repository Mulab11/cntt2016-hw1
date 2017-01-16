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

class LittleElephantAndString {
public:
	int getNumber(std::string A, std::string B) {
		int cnt[26] = {0};
		for(auto c : A) cnt[c - 'A']++;
		for(auto c : B) cnt[c - 'A']--;
		for(int i = 0; i < 26; ++i)
			if(cnt[i]) return -1;// 判断两个串的每种字符数量是否相等
		int n = SZ(B);
		for(int i = n - 1, j = n - 1; i >= 0; --i, --j) {// 求一个最长的B的后缀使得是A的一个子序列
			while(j >= 0 && A[j] != B[i]) --j;
			if(j < 0) return i + 1;
		}
		return 0;
	}
};
