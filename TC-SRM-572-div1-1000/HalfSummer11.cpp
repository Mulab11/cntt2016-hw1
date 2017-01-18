#line 2 "NextAndPrev.cpp"
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
int n, dest[maxn], N, P; // n表示字符串长度，dest[i]表示第i个字母需要变成第dest[i]个字母,N,P分别是向后/向前移动的代价。
class NextAndPrev {
	public:
		int getMinimum(int Cn, int Cp, string start, string goal) {
			N = Cn; P = Cp;
			if (start == goal) return 0;
			n = start.size();
			for (int c = 0; c < 26; ++c) { // 枚举start中的每一种字符，找到它们的出现位置
				dest[c] = -1;
				for (int i = 0; i < n; ++i)
					if (start[i] == 'a' + c) {
						if (dest[c] == -1 || dest[c] == goal[i] - 'a')
							dest[c] = goal[i] - 'a';
						else // 若在start中相同的字符在goal中不同，则不存在合法的方案
							return -1;
					}
			}
			bool flag = 1;
			for (int i = 0; i < 26; ++i) {
				bool exist = 0; // 表示第i个字母是否在goal中出现过
				for (int j = 0; j < 26; ++j)
					exist |= (dest[j] == i);
				flag &= exist;
			}
			if (flag) return -1; // 若每个字母都在goal中出现过，start中的字母无论如何移动，都会发生合并，从而没有合法的方案
			bool exist = 0;
			int ans = oo, sum = 0;
			for (int i = 0; i < 26; ++i) // 把dest[i]排在一个小圆上，i排在一个大圆上，合法方案中，所有dest[i]与i之间的连线不相交。现在要把圆切开变成直线，小圆以a为起始点，大圆以这里枚举的i为起始点
				if (dest[i] != -1) {
					int lst = dest[i]; bool ok = 1;
					for (int j = (i + 1) % 26; j != i; j = (j + 1) % 26) {
						if (dest[j] == -1) continue;
						if (dest[j] < lst) ok = 0; // 出现了交叉的情况，不合法
						lst = dest[j];
					}
					exist |= ok;
					if (!ok) continue;
					for (int del = -52; del <= 26; del += 26) { // 拆成两条直线后，还需要考虑在连线时绕的方向与圈数。考虑与dest[i]距离最近的i，它们的距离不会超过26.于是对于任意的i，dest[i]与它的距离不会超过52。因此在这个范围内枚举绕圈情况即可。
						sum = 0;
						for (int j = i + del; j < i + del + 26; ++j) {
							if (dest[(j + 52) % 26] == -1) continue;
							int L = j, R, d = dest[(j + 52) % 26]; // 找到dest[i] = d的一段[L, R]
							for (int k = j; k < i + del + 26; ++k) {
								if (dest[(k + 52) % 26] == d)
									R = k;
								else {
									if (dest[(k + 52) % 26] != -1)
										break;
								}
							}
							if (L <= d && d <= R) // 贪心计算出[L, R]移动到d的代价
								sum += (d - L) * N + (R - d) * P;
							if (d < L) 
								sum += (R - d) * P;
							if (d > R)
								sum += (d - L) * N;
							j = R;
						}
						ans = min(ans, sum);
					}
				}
			return exist ? ans : -1;
		}
};
