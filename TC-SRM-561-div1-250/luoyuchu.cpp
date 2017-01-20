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

int n, m;
int ball[2][maxn], bt[2], sum[2];
int pro[maxn];

int Solve()
{
	int ans = 2e9;
	int N = (1 << m), tmp;
	int lst[2][maxn], lt[2], total[2], S;
	sort(pro + 1, pro + 1 + m);
	reverse(pro + 1, pro + 1 + m);
	sort(ball[0] + 1, ball[0] + 1 + bt[0]);
	reverse(ball[0] + 1, ball[0] + 1 + bt[0]);
	sort(ball[1] + 1, ball[1] + 1 + bt[1]);
	reverse(ball[1] + 1, ball[1] + 1 + bt[1]);//每一类中都从大到小排序
	for (int i = 0; i < N; ++i) {//枚举每个题目所用的气球的大小
		tmp = i;
		lt[0] = lt[1] = total[0] = total[1] = 0;
		for (int j = 1; j <= m; ++j) {
			lst[tmp & 1][++lt[tmp & 1]] = pro[j];
			total[tmp & 1] += pro[j];
			tmp >>= 1;
		}
		if (total[0] > sum[0] || total[1] > sum[1]) continue;//总数首先要满足
		S = 0;
		for (int j = 0; j < 2; ++j) {
			for (int k = 1; k <= lt[j]; ++k) {//从大到小一个一个安排，如果不够则增加答案
				if (bt[j] < k) S += lst[j][k];
				else S += max(0, lst[j][k] - ball[j][k]);
			}
		}
		Ckmin(ans, S);//更新答案
	}
	if (ans > 1e9) return -1;
	else return ans;
}

class ICPCBalloons {
    public:
    int minRepaintings(vector<int> balloonCount, string balloonSize, vector<int> maxAccepted) {
		n = balloonCount.size();
		sum[0] = sum[1] = bt[0] = bt[1] = 0;
		for (int i = 0; i < n; ++i) {//将气球分为大小两类
			if (balloonSize[i] == 'M') {
				ball[0][++bt[0]] = balloonCount[i];
				sum[0] += balloonCount[i];
			}
			else {
				ball[1][++bt[1]] = balloonCount[i];
				sum[1] += balloonCount[i];
			}
		}
		m = maxAccepted.size();
		for (int i = 0; i < m; ++i) {
			pro[i + 1] = maxAccepted[i];
		}
		return Solve();
    }
};

