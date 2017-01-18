#line 2 "EllysRoomAssignmentsDiv1.cpp"
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
#define maxn 600
typedef long long ll;
using namespace std;
string s; // 存rating的字符串
int len; // s的长度
int n, a[maxn], elly; // n是人数，a[]存rating，elly是Elly的rating
int read(int &pos) { // 从s的pos处开始读数字
	while (pos < len && (s[pos] < '0' || s[pos] > '9')) ++pos;
	int x = 0;
	while (pos < len && s[pos] >= '0' && s[pos] <= '9')
		x = x * 10 + s[pos] - '0', ++pos;
	return x;
}
class EllysRoomAssignmentsDiv1 {
	public:
		double getAverage(vector <string> ratings) {
			s = "";
			for (int i = 0; i < ratings.size(); ++i)
				s = s + ratings[i];
			len = s.length();
			n = 0; int pos = 0;
			while (pos < len) a[++n] = read(pos); // 读rating
			elly = a[1];
			sort(a + 1, a + n + 1);
			reverse(a + 1, a + n + 1); // 从大到小排
			int R = (n + 19) / 20;
			double ans = 0;
			for (int i = 1; i <= n; i += R) { // 模拟分配room的过程，每次拿出R个人来进行分配
				double sum = 0; // 当前轮所有人的rating之和
				bool flag = 0; // 当前轮是否包含Elly
				for (int j = i; j <= min(i + R - 1, n); ++j)
					flag |= (a[j] == elly), sum += a[j];
				if (flag) { // 当前轮包含Elly
					if (i + R - 1 > n) 
						return (ans + elly) / (int(n / R) + 1); // 这是最后一轮，且人数不足R。由于是Elly所在的room，所以人数为(n / R) + 1, 这一轮的贡献也可以确定是elly，直接得到答案。
					ans += elly; continue; // 否则，这一轮的贡献是elly，计入ans
				}
				if (i + R - 1 <= n) {
					ans += sum / R; // 这一轮的贡献期望为sum / R
				} else {
					int cnt = n / R; // 人数较少的房间有cnt人，较多的有cnt + 1人
					return ans * (R - (n - i + 1)) / R / cnt + (ans + sum / (n - i + 1)) * (n - i + 1) / R / (cnt + 1);
					// 有(R - (n - i + 1)) / R的概率，Elly所在房间只有cnt人，和的期望就是之前的ans，有(n - i + 1) / R的概率，Elly所在房间有(cnt + 1)人，当前轮的期望贡献为sum / (n - i + 1)
				}
			}
			int cnt = n / R; 
			return ans / cnt; // 否则，n可以被R整除，Elly所在房间有cnt人
		}
};
