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

const int maxn = 49;

int n;////要保证距离和最小，塔的高度一定是先单调下降再单调上升的
pair<int, int> A[maxn], B[maxn], C[maxn];
vector<int> Ans;

bool cmp_2(const pair<int, int> &a, const pair<int, int> &b)//单调下降部分的排序
{
	return (a.first > b.first || (a.first == b.first && a.second < b.second));
}

class TheBrickTowerMediumDivOne {
    public:
    vector<int> find(vector<int> heights) {
		int bt = 0, ct = 0;
		n = heights.size();
		Ans.clear();
		for (int i = 0; i < n; ++i) {
			A[i + 1] = make_pair(heights[i], i);
		}
		sort(A + 1, A + 1 + n);
		if (A[1].second == 0) {//如果第一个塔是最小的，那么就只能单调上升排列了
			for (int i = 1; i <= n; ++i) {
				Ans.push_back(A[i].second);
			}
			return Ans;
		}
		else {
			int last = 2e9;
			for (int i = 0; i < n; ++i) {
				if (i == A[1].second) continue;//以最小的塔作为分割点
				else if (heights[i] <= last && i < A[1].second) {//之前的塔按字典序能放就放
					B[++bt] = make_pair(heights[i], i);
					last = heights[i];
				}
				else {//其他的塔放在后面
					C[++ct] = make_pair(heights[i], i);
				}
			}
			//将两部分塔组合起来
			sort(B + 1, B + 1 + bt, cmp_2);
			sort(C + 1, C + 1 + ct);
			for (int i = 1; i <= bt; ++i) Ans.push_back(B[i].second);
			Ans.push_back(A[1].second);
			for (int i = 1; i <= ct; ++i) Ans.push_back(C[i].second);
			return Ans;
		}
    }
};
