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

const int maxn = 55;

int n;
int cnt[maxn];

class LittleElephantAndString {
    public:
    int getNumber(string A, string B) {
		n = A.size();
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; ++i) {
			++cnt[A[i] - 'A' + 1];
		}
		for (int i = 0; i < n; ++i) {
			--cnt[B[i] - 'A' + 1];
		}
		for (int i = 1; i <= 26; ++i) {//通过每种字符个数来判断是否合法
			if (cnt[i] != 0) {
				return -1;
			}
		}
		int p = n - 1;
		int ans = 0;
		for (int i = n - 1; i >= 0; --i) {//B串的连续后缀能在A中匹配的最长后缀序列可以保留，其他每个元素必须花费一次操作
			while (p >= 0 && A[p] != B[i]) --p;
			if (p < 0) break;
			--p;
			++ans;
		}
        return n - ans;
    }
};
