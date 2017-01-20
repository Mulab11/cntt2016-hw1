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

const int maxn = 11;
const int maxm = 55;

int n, m;
int Ans;//答案
string Ansval;//如果答案只有一个，记录他
int del[maxn][maxn] = {0};//del[i][j]>0表示第i位不能选择j
int mst[maxn][maxn] = {0};//mst[i][j]>0表示第i为必须选择j
int gs[maxm][maxn], cor[maxm], nc[maxm];//gs与cor为输入的数组，nc[i]表示第i次猜测已经满足了几个
int tt[maxn];//但前搜索出的答案数组
pair<int, int> sta_add[maxn][maxn * maxn], sta_mst[maxn][maxn * maxn];//记录Dfs没一层的改变，用于回溯
int sta_add_top[maxn], sta_mst_top[maxn];

int Dfs(int p)
{
	bool ok;//是否可行
	int cnt, za = 0;
	int nr = -1;//对于每一个在当前位未在任何猜测数组中出现的元素是等价的，所以只要使用一个为代表用来搜索即可，这是它搜索出来的结果
	bool isnone;//对于每一个在当前位未在任何猜测数组中出现的元素是等价的，所以只要使用一个为代表用来搜索即可，这是这个数字是否属于这个等价类
	static int mmst[maxn];//检查之后的每一位是否有两个必须出现的数字的冲突
	if (p == n + 1) {//搜索的终点
		for (int i = 1; i <= n; ++i) Ansval += (char)('0' + tt[i]);
		++Ans;
		return 1;
	}
	int must = -1;//看这一位是否有必须放的元素
	for (int i = 0; i <= 9; ++i) {
		if (mst[p][i]) {
			if (must != -1) {
				return 0;
			}
			must = i;
		}
	}
	for (int i = 0; i <= 9; ++i) {//枚举这一位的数字
		if (del[p][i]) continue;
		if (must != -1 && must != i) continue;
		sta_add_top[p] = sta_mst_top[p] = 0;
		tt[p] = i;
		isnone = 1;
		for (int j = 1; j <= m; ++j) {//检查他是否属于“从未出现”这一等价类
			if (tt[p] == gs[j][p]) {
				isnone = 0;
				break;
			}
		}
		if (isnone == 1 && nr != -1) {//如果属于等价类，则可用之间在这一等价类中的搜索结果判断
			if (nr == 0) continue;
			else if (nr == 1) {
				Ans = 2;
				return 1;
			}
		}
		for (int j = 1; j <= m; ++j) {//更新每个猜测数组中满足的位数
			if (tt[p] == gs[j][p]) {
				++nc[j];
			}
		}
		for (int j = 1; j <= m; ++j) {
			if (tt[p] == gs[j][p]) {
				if (nc[j] == cor[j]) {//对于满足位数一定达到要求的，之后的每一位一定不能再满足了
					for (int k = p + 1; k <= n; ++k) {
						++del[k][gs[j][k]];
						sta_add[p][++sta_add_top[p]] = make_pair(k, gs[j][k]);
					}
				}
			}
			else {
				if (n - p == cor[j] - nc[j]) {//对于如果之后必须每一位都满足才能达到要求，则后面每一位都必须确定为一个数
					for (int k = p + 1; k <= n; ++k) {
						++mst[k][gs[j][k]];
						sta_mst[p][++sta_mst_top[p]] = make_pair(k, gs[j][k]);
					}
				}
			}
		}
		ok = 1;
		for (int j = p + 1; j <= n; ++j) {//检查之后的位置是否有冲突，是否一个位置会确定两个数
			cnt = 0;
			mmst[j] = -1;
			for (int k = 0; k <= 9; ++k) {
				if (mst[j][k]) {
					++cnt;
					mmst[j] = k;
				}
			}
			if (cnt > 1) {
				ok = 0;
				break;
			}
		}
		if (ok) {
			for (int j = 1; j <= m; ++j) {//检查之后的位置是否冲突，是否在尽量满足的情况下仍然不满足
				cnt = 0;
				for (int k = p + 1; k <= n; ++k) {
					cnt += (del[k][gs[j][k]] == 0 && (mmst[k] == -1 || mmst[k] == gs[j][k]));
				}
				if (cnt + nc[j] < cor[j]) {
					ok = 0;
					break;
				}
			}
		}
		if (ok) {//如果一切可行，继续向后搜索
			if (isnone == 1) {
				za += nr = Dfs(p + 1);//对于一个“从未出现”等价类的答案，需要记录下来
			}
			else {
				za += Dfs(p + 1);//否则不用记录
			}
		}
		if (Ans >= 2) return 1;
		for (int j = 1; j <= m; ++j) {//回溯过程
			if (tt[p] == gs[j][p]) {
				--nc[j];
			}
		}
		for (int j = 1; j <= sta_add_top[p]; ++j) {
			--del[sta_add[p][j].first][sta_add[p][j].second];
		}
		for (int j = 1; j <= sta_mst_top[p]; ++j) {
			--mst[sta_mst[p][j].first][sta_mst[p][j].second];
		}
	}
	return za;
}

class EllysBulls {
    public:
    string getNumber(vector<string> guesses, vector<int> bulls) {
		vector<string> copy = guesses;
		m = guesses.size();
		n = guesses[0].length();
		sort(guesses.begin(), guesses.end());
		m = unique(guesses.begin(), guesses.end()) - guesses.begin();//将重复的条件去重
		for (int i = 0; i < (int)copy.size(); ++i) {//如果猜测数组相同，而结果不同，则一定不会有答案
			for (int j = i + 1; j < (int)copy.size(); ++j) {
				if (copy[i] == copy[j] && bulls[i] != bulls[j]) {
					return "Liar";
				}
			}
		}
		for (int i = 1; i <= m; ++i) {//从新分配结果数组
			for (int j = 0; j < (int)copy.size(); ++j) {
				if (copy[j] == guesses[i - 1]) {
					cor[i] = bulls[j];
					break;
				}
			}
		}
		for (int i = 1; i <= m; ++i) {//赋值到全局变量
			for (int j = 1; j <= n; ++j) {
				gs[i][j] = guesses[i - 1][j - 1] - '0';
			}
		}
		memset(del, 0, sizeof(del));
		memset(nc, 0, sizeof(nc));
		memset(mst, 0, sizeof(mst));
		Ans = 0;
		Ansval.resize(0);
		for (int i = 1; i <= m; ++i) {//对于结果为0的数组处理
			if (cor[i] == 0) {
				for (int j = 1; j <= n; ++j) {
					++del[j][gs[i][j]];
				}
			}
		}
		Dfs(1);//搜索
		if (Ans >= 2) return "Ambiguity";//返回答案
		else if (Ans == 1) return Ansval;
		else return "Liar";
    }
};

