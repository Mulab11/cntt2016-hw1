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

vector<string> ans;//答案数组
int Ub;//数字的上界

void Dfs(int p, int num, string tt)//dfs按照顺序搜索
{
	if (p > 1) ans.push_back(tt + ".mp3");//得到一个合法答案
	if (ans.size() == 50) return;
	for (int i = 0; i <= 9; ++i) {
		if (p == 1 && i == 0) continue;//不能有前导0
		if (num * 10 + i > Ub) return;//超出上界
		Dfs(p + 1, num * 10 + i, tt + (char)('0' + i));
		if (ans.size() == 50) return;//已经搜出50个答案则停止
	}
}

class FoxAndMp3 {
    public:
    vector<string> playList(int n) {
		Ub = n;
		ans.clear();
		Dfs(1, 0, "");
		return ans;
    }
};
