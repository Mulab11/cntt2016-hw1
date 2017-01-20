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

const int maxn = 27;

int ANS = 2e9;
int cost[2];
int cor[maxn], some[maxn];

bool Check()//判断是否有解
{
	int p = -1;
	int reach[maxn] = {0};
	for (int i = 0; i < 26; ++i) {//如果有解，那么他在环上的相对顺序一定是对的
		if (cor[i] == -1) {
			continue;
		}
		if (p == -1) {
			p = cor[i];
		}
		else {
			if (cor[i] == p) continue;
			p = (p + 1) % 26;
			while (some[p] == 0) p = (p + 1) % 26;
			++reach[p];
			if (reach[p] > 1) return 0;
			if (cor[i] != p) return 0;
		}
	}
	int cnt = 0;
	for (int i = 0; i < 26; ++i) {//并且在goal中不能出现啊26种字母
		if (some[i]) {
			++cnt;
		}
	}
	if (cnt == 26) return 0;
	return 1;
}

void Solve()
{
	static pair<int, int> thing[maxn];
	int total = 0;
	for (int i = 0; i < 26; ++i) {
		if (cor[i] != -1) {
			thing[++total] = make_pair(i, i);
		}
	}
	int Ti = 0;
	while (Ti < total) {//枚举一个字母，将环变为链
		int pos[maxn];
		int Ans = 2e9;
		bool all = 1;
		for (int i = 2; i <= total; ++i) {
			if (cor[thing[i].second] != cor[thing[1].second]) {
				all = 0;
				break;
			}
		}
		if (!all) {
			while (cor[thing[1].second] == cor[thing[total].second]) {
				thing[1].first += 26;
				++Ti;
				sort(thing + 1, thing + 1 + total);
			}
		}
		pos[0] = 0;
		for (int i = 1; i <= total; ++i) {//将对应同一个字母的字母调整到一起
			int p = cor[thing[i].second];
			while (p < pos[i - 1]) p += 26;
			pos[i] = p;
		}
		for (int i = -5; i <= 5; ++i) {//枚举他们的移动方式
			int S, T;
			int det = i * 26;
			int Sum = 0;
			S = 1;
			while (S <= total) {
				T = S;
				while (T < total && cor[thing[T + 1].second] == cor[thing[S].second]) ++T;
				if (thing[S].first <= (pos[S] + det) && thing[T].first >= (pos[S] + det)) {
					Sum += ((pos[S] + det) - thing[S].first) * cost[1] + (thing[T].first - (pos[S] + det)) * cost[0];
				}
				else if (pos[S] + det >= thing[T].first){
					Sum += (pos[S] + det - thing[S].first) * cost[1];
				}
				else {
					Sum += (thing[T].first - (pos[S] + det)) * cost[0];
				}
				S = T + 1;
			}
			Ckmin(Ans, Sum);
		}
		Ckmin(ANS, Ans);//更新答案
		++Ti;
		thing[1].first += 26;
		sort(thing + 1, thing + 1 + total);
	}
}

class NextAndPrev {
    public:
    int getMinimum(int nextCost, int prevCost, string start, string goal) {
		int n = start.length();
		ANS = 2e9;
		cost[1] = nextCost;
		cost[0] = prevCost;
		memset(cor, -1, sizeof(cor));
		if (start == goal) return 0;//如果相等要特判
		for (int i = 0; i < n; ++i) {//求出对应关系
			if (cor[start[i] - 'a'] == -1) {
				cor[start[i] - 'a'] = goal[i] - 'a';
			}
			else {
				if (cor[start[i] - 'a'] != goal[i] - 'a') {
					return -1;
				}
			}
		}
		memset(some, 0, sizeof(some));
		for (int i = 0; i < 26; ++i) {
			if (cor[i] != -1) {
				some[cor[i]] = 1;
			}
		}
		if (!Check()) return -1;//检查合法性
		Solve();//求解
		return ANS;
    }
};

