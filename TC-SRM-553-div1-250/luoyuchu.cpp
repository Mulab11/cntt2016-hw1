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

int n, Ans;
int pro[maxn];
pair<LL, int> sta[maxn];
int st = 0;

pair<LL, int> operator + (const pair<LL, int> &a, const pair<LL, int> &b)//first表示常数项的和，second表示是否包含未知数
{
	return make_pair(a.first + b.first, a.second + b.second);
}

pair<LL, int> Getone()//取出栈顶
{
	if (st == 0) return make_pair(0LL, 0);
	else return sta[st--];
}

bool Check0()//检查如果将-1变为0是否合法
{
	st = 0;
	pair<LL, int> tmp;
	for (int i = 1; i <= n; ++i) {
		if (pro[i] == 0 || pro[i] == -1) {
			tmp = Getone() + Getone();
			sta[++st] = tmp;
		}
		else {
			sta[++st] = make_pair(pro[i], 0);
		}
	}
	return (Getone().first == Ans);
}

int Check()//检查将-1当作未知数带入的结果
{
	st = 0;
	pair<LL, int> tmp;
	for (int i = 1; i <= n; ++i) {
		if (pro[i] == 0) {
			tmp = Getone() + Getone();
			sta[++st] = tmp;
		}
		else if (pro[i] == -1) {
			sta[++st] = make_pair(0, 1);
		}
		else {
			sta[++st] = make_pair(pro[i], 0);
		}
	}
	tmp = Getone();
	if (tmp.first == Ans && tmp.second == 1) return -1;
	else if (tmp.first == Ans && tmp.second == 0) return 1;
	else if (tmp.first != Ans && tmp.second == 0) return -1;
	else return (Ans - tmp.first > 0) ? (Ans - tmp.first) : -1;
}

class Suminator { 
    public:
    int findMissing(vector<int> program, int wantedResult) {
		n = program.size();
		Ans = wantedResult;
		for (int i = 1; i <= n; ++i) {
			pro[i] = program[i - 1];
		}
		if (Check0()) return 0;//检查如果将-1变为0是否合法
		else return Check();//检查将-1当作未知数带入的结果
    }
};
