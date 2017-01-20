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

const int maxn = 55;

class TeamContest {
    public:
    int worstRank(vector<int> st) {
		int n = st.size();
		int Ans = 0;
		int me = max(st[0], max(st[1], st[2])) + min(st[0], min(st[1], st[2]));//求出本队能力
		static int A[maxn];
		for (int i = 3; i < n; ++i) {
			A[i - 3] = st[i];
		}
		n -= 3;
		sort(A, A + n);//排序
		int p = 0;
		for (int i = n - 1; i >= 1 && i > p + 1; --i) {//贪心选择其他队伍能力，最大的带尽可能最小的
			while (p + 2 != i && A[p] + A[i] <= me) {
				++p;
			}
			if (A[p] + A[i] > me) {
				++Ans;
				p += 2;
			}
			else break;
		}
		return Ans + 1;//返回答案
    }
};
