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

int n, N;
LL sub[maxn];
vector<int> ha[maxn], be;
vector<long long> NoAns;

bool Check()
{
	for (int i = 1; i <= n; ++i) {//检查是否有公共部分
		for (int j = i + 1; j <= n; ++j) {
			if ((sub[i] & sub[j]) == 0) {
				return 0;
			}
		}
	}
	be.clear();
	for (int i = 1; i <= n; ++i) {
		ha[i].clear();
	}
	for (int i = 0; i < 60; ++i) {//一个位置的二进制最多只能出现在两个数中
		int cnt = 0, bel;
		for (int j = 1; j <= n; ++j) {
			if ((sub[j] >> i) & 1) {
				++cnt;
				bel = j;
			}
		}
		if (cnt > 2) return 0;
		if (cnt == 1) {//记录下出现过一次的
			ha[bel].push_back(i);
		}
		if (cnt == 0) {
			be.push_back(i);//一次都未出现的
		}
	}
	int Min = 2e9;
	for (int i = 1; i <= n; ++i) {
		Ckmin(Min, (int)ha[i].size());
	}
	if (Min + n < N) return 0;//检查已经确定的数是否可以和未出现的数有公共部分
	if ((N - n) * (N - n - 1) / 2 > (int)be.size()) return 0;//检查未出现的数互相之间是否可以合法
	return 1;
}

vector<long long> Solve()
{
	long long ans[maxn] = {0};
	vector<long long> Ans;
	sort(be.begin(), be.end());//如果之前检查合法，那么只要贪心的将小的二进制位置给靠前的数就可以了
	for (int i = 1; i <= n; ++i) {
		sort(ha[i].begin(), ha[i].end());
	}
	int p = min((int)be.size() - 1, (N - n) * (N - n - 1) / 2 - 1);
	for (int i = N - n; i >= 1; --i) {
		for (int j = N - n; j > i; --j) {
			ans[i] |= (1LL << be[p]);
			ans[j] |= (1LL << be[p]);
			--p;
		}
	}
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= N - n; ++j) {
			ans[j] |= (1LL << ha[i][j - 1]);
		}
	}
	Ans.clear();
	for (int i = 1; i <= n; ++i) Ans.push_back(sub[i]);	
	for (int i = 1; i <= N - n; ++i) Ans.push_back(ans[i]);
	sort(Ans.begin(), Ans.end());
	return Ans;//返回答案
}

class BitwiseAnd {
    public:
    vector<long long> lexSmallest(vector<long long> subset, int _N) {
		n = subset.size();
		N = _N;
		NoAns.clear();
		for (int i = 1; i <= n; ++i) sub[i] = subset[i - 1];
		if (!Check()) return NoAns;//判断是否有解
        return Solve();
    }
};
