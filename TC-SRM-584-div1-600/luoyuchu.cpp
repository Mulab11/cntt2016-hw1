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
int dl[maxn], dt = 0;
bool fd[maxn];
LL f[maxn][2][maxn][maxn];
LL C[maxn][maxn];
pair<int, int> Data[maxn];

void Prepare()//预处理组合数
{
	for (int i = 0; i <= 50; ++i) {
		C[i][0] = 1;
		for (int j = 1; j <= i; ++j) {
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
	}
}

bool cmp(const pair<int, int> &a, const pair<int, int> &b)//比较函数
{
	return a.first < b.first || (a.first == b.first && fd[a.second] < fd[b.second]);
}

class Excavations {
    public:
    long long count(vector<int> kind, vector<int> depth, vector<int> found, int K) {
		LL Ans = 0;//答案
		n = kind.size();
		Prepare();
		memset(f, 0, sizeof(f));//先将建筑按照kind排序，先考虑将最终要挖掘出来的建筑选择，f[i][0/1][j][k]表示当前考虑到了第i个建筑，当前这一类的建筑有没有至少选择一个，已经选择了j个建筑，选择的建筑最大深度是k的方案数
		memset(fd, 0, sizeof(fd));
		for (int i = 0; i < n; ++i) {//将每个建筑的深度离散化
			dl[i] = depth[i];
		}
		dl[n] = -2e9;
		sort(dl, dl + n + 1);
		dt = unique(dl, dl + n + 1) - dl;
		for (int i = 0; i < n; ++i) {
			depth[i] = lower_bound(dl, dl + dt, depth[i]) - dl;
		}
		for (int i = 0; i < n; ++i) {
			Data[i + 1] = make_pair(kind[i], depth[i]);
		}
		sort(Data + 1, Data + n + 1);//将建筑排序
		for (int i = 0; i < found.size(); ++i) {
			fd[found[i]] = 1;
		}
		Data[0] = make_pair(55, 0);
		f[0][1][0][0] = 1;
		for (int i = 1; i <= n; ++i) {//动态规划
			if (fd[Data[i].first] == 0) {//如果这个建筑不能被选择
				memcpy(f[i][1], f[i - 1][1], sizeof(f[i - 1][1]));
			}
			else {
				if (Data[i - 1].first == Data[i].first) {//如果上一个建筑与这一个建筑是同一类建筑
					memcpy(f[i], f[i - 1], sizeof(f[i]));
					for (int a = 0; a <= K; ++a) {
						for (int b = 0; b < dt; ++b) {
							for (int c = 0; c < 2; ++c) {
								f[i][c | 1][a + 1][max(b, Data[i].second)] += f[i - 1][c][a][b];
							}
						}
					}
				}
				else {//不同类
					memcpy(f[i][0], f[i - 1][1], sizeof(f[i - 1][1]));
					for (int a = 0; a <= K; ++a) {
						for (int b = 0; b < dt; ++b) {
							f[i][1][a + 1][max(b, Data[i].second)] += f[i - 1][1][a][b];
						}
					}
				}
			}
		}
		pair<int, int> res[maxn];
		int rt;
		for (int i = 0; i <= n; ++i) {//统计答案
			for (int j = 0; j < dt; ++j) {
				if (f[n][1][i][j] == 0) continue;
				rt = 0;
				for (int k = 1; k <= n; ++k) {
					if (Data[k].second > j) {//筛选出深度在j之上的建筑，在其中选择挖不出来的建筑
						res[rt++] = make_pair(Data[k].second, Data[k].first);
					}
				}
				sort(res, res + rt, cmp);
				if (i == K) {//如果全挖出来了
					Ans += f[n][1][i][j];
				}
				for (int k = 0; k < rt; ++k) {//挖不出的深度最小的建筑一定不能是found中有的建筑，否则会有另一种方案将其重复计算
					if (fd[res[k].second] == 0) {
						if (rt - k - 1 >= 0 && K - i - 1 >= 0) {
							Ans += C[rt - k - 1][K - i - 1] * f[n][1][i][j];
						}
					}
				}
			}
		}
        return Ans;//返回答案
    }
};
