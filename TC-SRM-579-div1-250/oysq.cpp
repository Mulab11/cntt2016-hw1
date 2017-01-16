// BEGIN CUT HERE

// END CUT HERE
#line 5 "UndoHistory.cpp"
#include <bits/stdc++.h>

using namespace std;

#define SZ(x) (int)(x).size()
#define pb push_back
#define mp make_pair
#define fi first
#define se second

typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef long long ll;
typedef pair<int,int> pii;

template<class T>inline void chkmax(T &x, const T &y) {if(x < y) x = y;}
template<class T>inline void chkmin(T &x, const T &y) {if(x > y) x = y;}

struct UndoHistory {
    int minPresses(vector <string> lines) {
		int ans = 0;
		for(int i = 0; i < SZ(lines); ++i) {
			int maxl = 0, minv = 1e9;
			// maxl 表示lines[i]和lines[0 ~ i - 1]的最长前缀
			for(int j = 0; j < i; ++j) {
				int cur = 0;
				while(cur < SZ(lines[i]) && cur < SZ(lines[j]) && lines[i][cur] == lines[j][cur])
					++cur;
				chkmax(maxl, cur);
			}
			// 接着上一个type
			if(i && SZ(lines[i - 1]) <= SZ(lines[i]) && lines[i - 1] == lines[i].substr(0, SZ(lines[i - 1]))) minv = SZ(lines[i]) - SZ(lines[i - 1]);
			else if(!i) minv = SZ(lines[i]);
			// 重置后type
			chkmin(minv, SZ(lines[i]) - maxl + 2);
			ans += minv + 1/* enter */;
		}
		return ans;
    }
};
