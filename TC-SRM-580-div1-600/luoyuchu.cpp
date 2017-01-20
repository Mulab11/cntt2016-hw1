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
int L[maxn], R[maxn];
int boundary_R[maxn], boundary_L[maxn];
pair<int, int> A[maxn];
int fl[maxn], fr[maxn];

bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
	return a.first < b.first || (a.first == b.first && a.second > b.second);
}
bool cmp_L(const pair<int, int> &a, const pair<int, int> &b)
{
	return a.first < b.first;
}
bool cmp_R(const pair<int, int> &a, const pair<int, int> &b)
{
	return a.second < b.second;
}
bool CheckL(int x)
{
	return ((lower_bound(boundary_R + 1, boundary_R + 1 + n, x) - boundary_R) == 1);
}
bool CheckR(int x)
{
	return ((upper_bound(boundary_L + 1, boundary_L + 1 + n, x) - boundary_L) > n);
}

void Prepare()
{
	for (int i = 1; i <= m; ++i) {//计算从一个区间开始向左的答案
		if (CheckL(A[i].first)) {
			fl[i] = 1;
		}
		else {
			fl[i] = fl[(lower_bound(A + 1, A + 1 + m, make_pair(0, A[i].first), cmp_R) - A)] + 1;
		}
	}
	for (int i = m; i >= 1; --i) {//计算从一个区间开始向右的答案
		if (CheckR(A[i].second)) {
			fr[i] = 1;
		}
		else {
			fr[i] = fr[(upper_bound(A + 1, A + 1 + m, make_pair(A[i].second, 0), cmp_L) - A - 1)] + 1;
		}
	}
}

int Solve()
{
	int Sum = 0;
	int ans, la, ra;
	for (int i = 1; i <= n; ++i) {//枚举一个开始区间
		ans = 2e9;
		if (CheckL(L[i])) la = 0;
		else la = fl[lower_bound(A + 1, A + 1 + m, make_pair(0, L[i]), cmp_R) - A];
		if (CheckR(R[i])) ra = 0;
		else ra = fr[(upper_bound(A + 1, A + 1 + m, make_pair(R[i], 0), cmp_L) - A - 1)];
		Ckmin(ans, la + ra);//如果选择他能触及的最左的和最右的区间的答案
		ra = upper_bound(A + 1, A + 1 + m, make_pair(L[i], 0), cmp_L) - A - 1;
		la = lower_bound(A + 1, A + 1 + m, make_pair(0, R[i]), cmp_R) - A;
		if (la <= ra) {//如果选择一个包含他的区间的答案
			for (int j = la; j <= ra; ++j) {
				Ckmin(ans, fl[j] + fr[j] - 1);
			}
		}
		Sum += ans;
	}
	return Sum;
}

class ShoutterDiv1 {
    public:
    int count(vector<string> s1000, vector<string> s100, vector<string> s10, vector<string> s1, vector<string> t1000, vector<string> t100, vector<string> t10, vector<string> t1) {
		n = 0;
		for (int i = 0; i < (int)s1.size(); ++i) {
			for (int j = 0; j < (int)s1[i].length(); ++j) {
				++n;
				L[n] = (s1000[i][j] - '0') * 1000 + (s100[i][j] - '0') * 100 + (s10[i][j] - '0') * 10 + s1[i][j] - '0';
				R[n] = (t1000[i][j] - '0') * 1000 + (t100[i][j] - '0') * 100 + (t10[i][j] - '0') * 10 + t1[i][j] - '0';
				boundary_L[n] = L[n];
				boundary_R[n] = R[n];
				A[n] = make_pair(L[n], R[n]);
			}
		}
		int last = -1, det = 0;
		sort(A + 1, A + 1 + n, cmp);
		sort(boundary_L + 1, boundary_L + 1 + n);
		sort(boundary_R + 1, boundary_R + 1 + n);
		for (int i = 1; i <= n; ++i) {//将所有被包含的区间去掉，显然转发的区间不可能是他们
			if (A[i].second <= last) {
				A[i].first = 2e9;
				++det;
			}
			else {
				last = A[i].second;
			}
		}
		sort(A + 1, A + 1 + n);
		m = n - det;
		for (int i = 1; i < m; ++i) {
			if (A[i + 1].first > A[i].second) {
				return -1;
			}
		}
		Prepare();//预处理左右端点都递增的区间集合的答案
        return Solve();//对于每一区间作为开始，求出答案
    }
};

