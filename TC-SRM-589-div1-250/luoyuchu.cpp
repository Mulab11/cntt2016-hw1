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

int n;
int cnt[27];
int fa[27];

int Getfa(int p)
{
	if (fa[p] == p) return p;
	fa[p] = Getfa(fa[p]);
	Ckmax(cnt[fa[p]], cnt[p]);
	return fa[p];
}

class GooseTattarrattatDiv1 {
    public:
    int getmin(string S) {
		n = S.length();
		memset(cnt, 0, sizeof(cnt));
		for (int i = 0; i < 26; ++i) fa[i] = i;
		for (int i = 0; i < n; ++i) {//统计每种字符的个数
			++cnt[S[i] - 'a'];
		}
		for (int i = 0; i <= n - i - 1; ++i) {//如果对应位置字符不同，则这两种字符一定要最后变为1种
			if (S[i] != S[n - i - 1]) {
				fa[S[i] - 'a'] = Getfa(S[i] - 'a');
				fa[S[n - i - 1] - 'a'] = Getfa(S[n - i - 1] - 'a');
				Ckmax(cnt[fa[S[n - i - 1] - 'a']], cnt[fa[S[i] - 'a']]);
				fa[Getfa(S[i] - 'a')] = fa[S[n - i - 1] - 'a'];
			}
		}
		int Ans = n;
		for (int i = 0; i < 26; ++i) {//最后在每个联通块中选择最多的一种字符，使其它字符变为他即可
			if (Getfa(i) == i) {
				Ans -= cnt[i];
			}
		}
        return Ans;
    }
};
