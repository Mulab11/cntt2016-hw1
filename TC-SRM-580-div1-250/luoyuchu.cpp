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
int L[maxn], R[maxn];
int lst[maxn * 2], lt;

class EelAndRabbit {
    public:
    int getmax(vector<int> l, vector<int> t) {
		int Ans = 0;
		n = l.size();
		lt = 0;
		for (int i = 1; i <= n; ++i) {
			L[i] = t[i - 1];
			R[i] = t[i - 1] + l[i - 1];
			lst[++lt] = L[i];
			lst[++lt] = R[i];
		}
		sort(lst + 1, lst + 1 + lt);//将坐标离散化
		lt = unique(lst + 1, lst + 1 + lt) - lst - 1;
		for (int i = 1; i <= lt; ++i) {
			for (int j = i + 1; j <= lt; ++j) {//枚举抓泥鳅的两个坐标
				int sum = 0;
				for (int k = 1; k <= n; ++k) {//统计答案
					if ((L[k] <= lst[i] && R[k] >= lst[i]) || (L[k] <= lst[j] && R[k] >= lst[j])) {
						++sum;
					}
				}
				Ckmax(Ans, sum);//更新答案
			}
		}
        return Ans;
    }
};

