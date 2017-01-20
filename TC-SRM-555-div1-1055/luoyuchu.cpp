#include <bits/stdc++.h>

#define dig(...) fprintf(stderr, __VA_ARGS__)

using namespace std;

void begin()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
}
void end()
{
 	fclose(stdin);
	fclose(stdout);
}

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

const int maxn = 41;

int n;
LL C[maxn][maxn];//组合数

LL Execution(string goal, vector<string> code, int st)//模拟将x作为起始节点能得到的可变的集合
{
	int x = st;
	int wrong = 0;//当前错误的位置的个数
	LL S = 0, Max = 0;
	static char status[maxn];
	for (int i = 0; i < n; ++i) status[i] = goal[i];
	for (int i = 0; i < code.size(); ++i) {
		for (int j = 0; j < code[i].length(); ++j) {
			if (code[i][j] == '<') --x;
			else if (code[i][j] == '>') ++x;
			else {
				S |= (1LL << x);//当前改动集合
				wrong += (code[i][j] != goal[x]) - (status[x] != goal[x]);
				status[x] = code[i][j];
			}
			if (x < 0 || x >= n) return -1;
			if (wrong == 0) Ckmax(Max, S);//取出没有错误的最大的集合
		}
	}
	return Max;
}

int GetLen(vector<string> code)//得到这一系列操作所走过的宽度
{
	int Max = 0, Min = 0;
	int x = 0;
	for (int i = 0; i < code.size(); ++i) {
		for (int j = 0; j < code[i].length(); ++j) {
			if (code[i][j] == '<') --x;
			if (code[i][j] == '>') ++x;
			Ckmin(Min, x);
			Ckmax(Max, x);
		}
	}
	return (Max - Min + 1);
}

int Countone(LL x)//计算x的二进制中有多少个1
{
	int cnt = 0;
	while (x) {
		x -= ((x) & (-x));
		++cnt;
	}
	return cnt;
}

void Prepare()//预处理组合数
{
	for (int i = 0; i < maxn; ++i) {
		C[i][0] = 1;
		for (int j = 1; j < i; ++j) {
			C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
		}
	}
}

class MapGuessing {
    public:
    long long countPatterns(string goal, vector<string> code) {
		int L;
		LL tmp, Ans = 0;
		vector<LL> Set;
		n = goal.length();
		Prepare();
		L = GetLen(code);
		for (int i = 0; i < n; ++i) {//枚举起点
			tmp = Execution(goal, code, i);
			if (tmp > 0) {
				Set.push_back(tmp);
			}
		}
		if (Set.size() <= 20) {//如果集合个数较少，则暴力容斥
			int total = Set.size();
			int N = (1 << total);
			int tp, cnt;
			for (int i = 1; i < N; ++i) {
				tp = i;
				cnt = 0;
				tmp = (1LL << 40) - 1;
				for (int j = 0; j < total; ++j) {
					if (tp & 1) {
						tmp &= Set[j];
						++cnt;
					}
					tp >>= 1;
				}
				if (cnt & 1) Ans += (1LL << Countone(tmp));
				else Ans -= (1LL << Countone(tmp));
			}
		}
		else {//如果集合较多，则每一个集合的宽度L一定较小，所以只有相邻的L个集合可能有交
			LL res[maxn];
			for (int i = 1; i <= Set.size(); ++i) res[i] = C[Set.size()][i];
			for (int st = 0; st < Set.size(); ++st) {
				int total = min((int)(Set.size() - st), L);
				int ed = st + total - 1;
				int N = (1 << (total - 1));
				int tp, cnt;
				for (int i = 0; i < N; ++i) {
					tp = i;
					cnt = 1;
					tmp = Set[st];
					for (int j = st + 1; j <= ed; ++j) {
						if (tp & 1) {
							tmp &= Set[j];
							++cnt;
						}
						tp >>= 1;
					}
					--res[cnt];
					if (cnt & 1) Ans += (1LL << Countone(tmp));
					else Ans -= (1LL << Countone(tmp));
				}
			}
			for (int i = 1; i <= Set.size(); ++i) {//对于其他不可能有交的集合，注意2^0=1，计算答案
				if (i & 1) Ans += res[i];
				else Ans -= res[i];
			}
		}
		if (L <= n && Set.size() == 0) ++Ans;//如果有合法操作，但没有可改变位置，空集要算入答案
        return Ans;//返回答案
    }
};
