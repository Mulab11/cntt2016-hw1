#line 2 "UndoHistory.cpp"
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
class UndoHistory {
	public:
		int minPresses(vector <string> lines) {
			int n = lines.size(); // 串的个数
			int ans = lines[0].size() + 1; // 第一个串的代价
			for (int i = 1; i < n; ++i) {
				int mi = oo;
				if (lines[i - 1].length() <= lines[i].length()) { 
					bool flag = 1;
					for (int j = 0; j < lines[i - 1].length(); ++j)
						if (lines[i - 1][j] != lines[i][j]) {
							flag = 0; break;
						}
					if (flag) // 若上一个字符串是当前字符串的前缀，则可以选择接着打下去
						mi = min(mi, int(lines[i].length() - lines[i - 1].length() + 1));
				}
				int mx = 0;
				for (int j = 0; j < i; ++j) // 另一种选择是，找到某个前面的串与自己的公共前缀，顺着它往下打
					for (int k = 0; k < min(lines[j].length(), lines[i].length()); ++k) {
						if (lines[j][k] != lines[i][k]) break;
						mx = max(mx, k + 1);
					}
				mi = min(int(lines[i].length()) - mx + 3, mi);
				ans += mi;
			}
			return ans;
		}
};
