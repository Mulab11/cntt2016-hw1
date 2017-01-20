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

const int maxn = 1e3+115;
const int maxm = 55;

int n;
int A[maxn];

class LittleElephantAndIntervalsDiv1 {
    public:
    long long getNumber(int M, vector<int> L, vector<int> R) {
		n = L.size();
		memset(A, 0, sizeof(A));
		for (int i = 0; i < n; ++i) {
			for (int j = L[i]; j <= R[i]; ++j) {
				A[j] = i + 1;
			}
		}
		int cnt = 0;
		bool vis[maxm] = {0};
		for (int i = 1; i <= M; ++i) {//求出可以不同颜色的段数，答案即为二的这么多次幂
			if (A[i] != 0 && vis[A[i]] == 0) {
				vis[A[i]] = 1;
				++cnt;
			}
		}
        return (1LL << cnt);
    }
};
