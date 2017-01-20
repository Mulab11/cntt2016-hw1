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

const int maxn = 15;

int n;
bool mat[maxn][maxn];//mat[i][j]表示是否存在由第i个与第j个字母组成的一项

void Init(vector<string> expr)//将读入的字符串转变为mat数组
{
	int p1, p2;
	memset(mat, 0, sizeof(mat));
	p1 = p2 = -1;
	for (int i = 0; i < expr.size(); ++i) {
		for (int j = 0; j < expr[i].length(); ++j) {
			if (expr[i][j] != '+') {
				if (p1 == -1) p1 = expr[i][j] - 'a' + 1;
				else {
					p2 = expr[i][j] - 'a' + 1;
					if (p1 < p2) swap(p1, p2);
					mat[p1][p2] = 1;
					p1 = p2 = -1;
				}
			}
		}
	}
}

double Upsum(vector<int> up, int maxSum)//对于所有数的上界加起来达不到总和上界的情况
{
	int s = 0;
	double ans = 0;
	for (int i = 0; i < n; ++i) s += up[i];
	if (s > maxSum) return -1e9;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j < i; ++j) {
			ans += mat[i][j] * up[i - 1] * up[j - 1];
		}
	}
	return ans;
}

int Pow(int x, int y)//快速幂
{
	int s = 1;
	while (y) {
		if (y & 1) s *= x;
		x *= x;
		y >>= 1;
	}
	return s;
}

double Solve(vector<int> up, vector<int> down, int maxSum)
{
	int N = Pow(3, n);//0:up 1:down 2:middle
	int stat[maxn], sum[maxn], tmp, first, res, cnt;
	double val[maxn];
	double ans = 0, S;
	for (int i = 0; i < N; ++i) {//枚举每个未知数是处于上界，下界，还是在中间
		tmp = i;
		for (int j = 1; j <= n; ++j) {
			stat[j] = tmp % 3;
			tmp /= 3;
		}
		bool ok = 1;
		for (int j = 1; j <= n; ++j) {//可以证明，如果两个在中间的数的mat[i][j]为0,由于是一次函数，一定可以调整到边界
			for (int k = 1; k < j; ++k) {
				if (mat[j][k] == 0 && stat[j] == 2 && stat[k] == 2) {
					ok = 0;
					break;
				}
			}
			if (!ok) break;
		}
		if (!ok) continue;
		for (int j = 1; j <= n; ++j) {//找到第一个在中间的数
			if (stat[j] == 2) {
				first = j;
				break;
			}
		}
		memset(sum, 0, sizeof(sum));
		for (int j = 1; j <= n; ++j) {//求出对于每一个在中间的数，已经确定的数对他系数的贡献（由于上一个步骤保证在中间的数互为系数，所以他们的系数之差都已确定）
			if (stat[j] == 2) {
				for (int k = 1; k <= n; ++k) {
					if (stat[k] != 2 && (mat[j][k] || mat[k][j])) {
						sum[j] += ((stat[k] == 0) ? up[k - 1] : down[k - 1]);
					}
				}
			}
		}
		cnt = 0;
		for (int j = n; j >= 1; --j) {//求出相对于第一个中间数系数差
			if (stat[j] == 2) {
				sum[j] -= sum[first];
				++cnt;
			}
		}
		res = maxSum;
		for (int j = 1; j <= n; ++j) {
			if (stat[j] != 2) {
				res -= ((stat[j] == 0) ? up[j - 1] : down[j - 1]);
			}
		}//res为除去已确定数的剩余可用的和
		if (res < 0) continue;//已超过maxSum
		for (int j = 1; j <= n; ++j) {
			if (stat[j] == 2) {
				res -= sum[j];
			}
		}//res为每个中间数除去系数差以外的总和
		ok = 1;
		for (int j = 1; j <= n; ++j) {
			if (stat[j] == 2) {
				val[j] = res * 1.0 / cnt;//cnt为中间数的个数
				val[j] += sum[j];
				if (val[j] > up[j - 1] || val[j] < down[j - 1]) {//如果不合要求，则舍去
					ok = 0;
					break;
				}
			}
			else {
				val[j] = ((stat[j] == 0) ? up[j - 1] : down[j - 1]);
			}
		}
		if (!ok) continue;
		S = 0;
		for (int j = 1; j <= n; ++j) {//求出最终的和
			for (int k = 1; k < j; ++k) {
				if (mat[j][k]) {
					S += val[j] * val[k];
				}
			}
		}
		Ckmax(ans, S);//更新答案
	}
	return ans;
}

class BoundedOptimization {
    public:
    double maxValue(vector<string> expr, vector<int> lowerBound, vector<int> upperBound, int maxSum) {
		Init(expr);
		n = upperBound.size();
		double tmp = Upsum(upperBound, maxSum);
		return ((tmp > 0) ? tmp : Solve(upperBound, lowerBound, maxSum));//如果上界之和不超过一maxSum则取上界，否则和一定为maxSum最优
    }
};

