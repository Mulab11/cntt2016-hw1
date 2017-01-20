#include <bits/stdc++.h>
using namespace std;

#define dig(...) fprintf(stderr, __VA_ARGS__)

template <class TAT>
void Ckmin(TAT &a, const TAT &b)
{
	if (a > b) a = b;
}
template <class TAT>

void Ckmax(TAT &a, const TAT &b)
{
	if (a < b) a = b;
}

typedef long long LL;

using namespace std;

const int maxn = 2555;

int n, m;
bool S[maxn];

long long Solve()
{
	static int psum[maxn];//前缀和，psum[i]表示在当前扫描到的位置之前，结尾‘G’个数大于等于i的字串的个数，如果包含的连续的G已经符合要求，则加在psum[minGreen]
	static int ps[maxn];//ps[i]表示以当前扫描位置结束结尾‘G’个数大于等于i的字串的个数,如果包含的连续的G已经符合要求，则加在ps[minGreen]
	LL Ans = 0;
	int last, cur;
	memset(psum, 0, sizeof(psum));
	for (int i = 1; i <= n; ++i) {
		last = -1;
		cur = 0;
		for (int j = i; j <= n; ++j) {//扫描以当前位置开头的串，更新答案
			if (S[j]) {
				++cur;
				if (cur >= m) last = m;
			}
			else {
				if (last == -1) last = cur;
				cur = 0;
			}
			if (last == -1) {
				Ans += psum[m - cur];
			}
			else {
				Ans += psum[m - last];
			}
		}
		memset(ps, 0, sizeof(ps));
		last = -1;
		cur = 0;
		for (int j = i; j >= 1; --j) {//扫描以当前位置结尾的串，更新前缀和
			if (S[j]) {
				++cur;
				if (cur >= m) last = m;
			}
			else {
				if (last == -1) last = cur;
				cur = 0;
			}
			if (last == -1) {
				++ps[cur];
			}
			else {
				++ps[last];
			}
		}
		for (int j = n - 1; j >= 0; --j) ps[j] += ps[j + 1];
		for (int j = n; j >= 0; --j) psum[j] += ps[j];
	}
	return Ans;//返回答案
}

class LittleElephantAndRGB {
    public:
    long long getNumber(vector<string> list, int minGreen) {
		n = 0;
		m = minGreen;
		for (int i = 0; i < (int)list.size(); ++i) {
			for (int j = 0; j < (int)list[i].length(); ++j) {
				S[++n] = (list[i][j] == 'G');
			}
		}
        return Solve();
    }
};
