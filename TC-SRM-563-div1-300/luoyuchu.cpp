#include <bits/stdc++.h>

#define dig(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

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

int n;
int cnt[257] = {0}, sc[257];
string Ans, S;

void Dfs(int p, int x)//p表示这是答案的第p位，x表示对应原串的前x位
{
	bool ok;
	if (p == n / 2) {
		return;
	}
	for (int i = 'a'; i <= 'z'; ++i) {//从小的字母开始枚举
		if (cnt[i] > 0) {
			--cnt[i];
			for (int j = x; j < n; ++j) {
				if (S[j] == i) {
					memset(sc, 0, sizeof(sc));
					for (int k = j + 1; k < n; ++k) {//统计之后的个数
						++sc[S[k]];
					}
					ok = 1;
					for (int k = 'a'; k <= 'z'; ++k) {//如果大于等于则可行
						if (sc[k] < cnt[k]) {
							ok = 0;
							break;
						}
					}
					if (ok) {
						Ans[p] = i;
						Dfs(p + 1, j + 1);
						return;
					}
				}
			}
			++cnt[i];
		}
	}
}

class FoxAndHandle {
    public:
    string lexSmallestName(string _S) {
		S = _S;
		n = _S.length();
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < n; ++i) ++cnt[S[i]];
		for (int i = 'a'; i <= 'z'; ++i) cnt[i] /= 2;//统计每种字母的个数
		Ans.resize(n / 2);
		Dfs(0, 0);//Dfs搜索，从前往后，从小的字母开始，如果可行就选择
        return Ans;
    }
};

