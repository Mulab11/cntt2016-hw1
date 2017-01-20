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

int n;
int digit[maxn];
int lb[maxn];
struct Data
{
	int len;
	int t[maxn];
	Data() {
		len = 0;
		memset(t, 0, sizeof(t));
	}
}f[maxn][maxn][3];//f[i][j][0-3]表示将前r-l+1个数填入l到r这一段，且这一段数对于lowerbound是小于，等于，大于的最小填法
bool exist[maxn][maxn][3] = {0};//表示对应的f[i][j][0-3]的状态是否存在

int Sign(int det)//返回两数差值所代表是大于小于还是等于
{
	if (det == 0) return 1;
	return (det > 0) ? 2 : 0;
}

Data Getmin(const Data &a, const Data &b)//返回a和b中更小的一个
{
	for (int i = 1; i <= a.len; ++i) {
		if (a.t[i] < b.t[i]) return a;
		if (a.t[i] > b.t[i]) return b;
	}
	return a;
}

Data Add(Data a, int x, bool flag)//在a的前/后加入一个数字x
{
	if (flag == 0) {
		for (int i = a.len; i >= 1; --i) a.t[i + 1] = a.t[i];
		a.t[1] = x;
		++a.len;
	}
	else {
		a.t[++a.len] = x;
	}
	return a;
}

string Trans(const Data &a)//将int数组转为string
{
	string ans;
	ans.resize(a.len);
	for (int i = 0; i < a.len; ++i) ans[i] = a.t[i + 1] + '0';
	return ans;
}	

int Compare(int l, int r, const Data &a)//如果将a放在l~r这一段，与lowerbound对应位置的大小关系
{
	for (int i = l, j = 1; i <= r; ++i, ++j) {
		if (a.t[j] < lb[i]) return 0;
		if (a.t[j] > lb[i]) return 2;
	}
	return 1;
}

void Solve()//动态规划，f[i][j][0-3]表示将前r-l+1个数填入l到r这一段，且这一段数对于lowerbound是小于，等于，大于的最小填法
{
	int sg;
	Data tmp;
	memset(exist, 0, sizeof(exist));
	for (int i = 1; i <= n; ++i) {
		exist[i][i][Sign(digit[1] - lb[i])] = 1;
		f[i][i][Sign(digit[1] - lb[i])].len = 1;
		f[i][i][Sign(digit[1] - lb[i])].t[1] = digit[1];
	}
	for (int L = 2; L <= n; ++L) {//区间从小到大
		for (int l = 1; l <= n - L + 1; ++l) {
			int r = l + L - 1;
			for (int i = 0; i < 3; ++i) {//枚举之前的状态
				if (exist[l + 1][r][i]) {//放在前面
					tmp = Add(f[l + 1][r][i], digit[L], 0);
					sg = Compare(l, r, tmp);
					if (exist[l][r][sg] == 0) {
						exist[l][r][sg] = 1;
						f[l][r][sg] = tmp;
					}
					else {
						f[l][r][sg] = Getmin(f[l][r][sg], tmp);
					}
				}
				if (exist[l][r - 1][i]) {//放在后面
					tmp = Add(f[l][r - 1][i], digit[L], 1);
					sg = Compare(l, r, tmp);
					if (exist[l][r][sg] == 0) {
						exist[l][r][sg] = 1;
						f[l][r][sg] = tmp;
					}
					else {
						f[l][r][sg] = Getmin(f[l][r][sg], tmp);
					}
				}
			}
		}			
	}
}

class LeftRightDigitsGame2 {
    public:
    string minNumber(string digits, string lowerBound) {
		n = digits.size();
		for (int i = 1; i <= n; ++i) {
			digit[i] = digits[i - 1] - '0';
			lb[i] = lowerBound[i - 1] - '0';
		}
		Solve();//动态规划解决问题
		if (exist[1][n][1] == 0 && exist[1][n][2] == 0) return "";//无解
		else if (exist[1][n][1]) return Trans(f[1][n][1]);//如果能等于就等于
		else return Trans(f[1][n][2]);//否则大于
    }
};
