#line 2 "EllysBulls.cpp"
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
#define maxn 20
typedef long long ll;
using namespace std;
map <string, int> M; // M[sta] = x，表示前half长度的串确定为x时，n次guess余下的猜中情况为sta
int n, len; // n是guess的个数，len是数字的长度
class EllysBulls {
	public:
		string getNumber(vector <string> s, vector <int> bulls) {
			len = s[0].size(); n = s.size();
			M.clear();
			int half = len / 2; 
			int up = 1; for (int i = 1; i <= half; ++i) up *= 10;
			for (int x = 0; x < up; ++x) { // mim,先枚举前一半数字串的值
				int tmp = x, now;
				string sta = ""; // sta[i]表示第i次guess目前猜中了几个
				for (int i = 0; i < n; ++i) sta = sta + "0";
				for (int j = half; j >= 1; --j) { // 枚举数字串的位
					now = tmp % 10; tmp /= 10; 
					for (int i = 0; i < n; ++i) // 更新每个guess的猜中次数
						if (s[i][j - 1] == '0' + now) 
							++sta[i];
				}
				bool flag = 1;
				for (int i = 0; i < n; ++i) {
					int y = sta[i] - '0';
					if (y > bulls[i]) {
						flag = 0; break;
					}
					sta[i] = '0' + bulls[i] - y; // 根据bulls计算出后半个数字串中，每个guess的猜中次数
				}
				if (flag) {
					if (M.count(sta)) 
						M[sta] = -1; // 如果两种不同的数字串造成了一样的sta，用-1标记，便于判断多解的情况。
					else
						M[sta] = x;
				}
			}
			if (len - half > half) up *= 10;
			int ans = -1;
			for (int x = 0; x < up; ++x) { // 枚举后半个数字串的值
				int tmp = x, now;
				string sta = ""; // sta[i]记录第i个guess的猜中次数
				for (int i = 0; i < n; ++i) sta = sta + "0";
				for (int i = len - 1; i >= half; --i) {
					now = tmp % 10; tmp /= 10;
					for (int j = 0; j < n; ++j)
						if (s[j][i] == '0' + now)
							++sta[j];
				}
				if (M.count(sta)) { // 有对应的前半段
					if (M[sta] == -1) return "Ambiguity"; // 多种合法的后半段
					if (ans != -1) return "Ambiguity"; // 此前已有合法的数字串
					ans = M[sta] * up + x;
				}
			}
			if (ans == -1) return "Liar";
			string ret = "";
			for (int i = 0; i < len; ++i, ans /= 10)
				ret = char('0' + (ans % 10)) + ret;
			return ret;
		}
};
