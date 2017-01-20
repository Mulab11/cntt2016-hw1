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

const int maxn = 55;

int n, total, Cs, Ct;
struct Item
{
	int cost, val;
	Item() {}
	Item(int _c, int _v):cost(_c), val(_v) {}
}A[maxn * maxn];
bitset<2555> f[maxn];//使用bitset加速

void AddItem(int cost, int val)//对于每个物品可以使用多次的背包，采用二进制拆分
{
	int S = 1;
	while (S <= cost) {
		A[++total] = Item(S, val * S);
		cost -= S;
		S <<= 1;
	}
	if (cost) {
		A[++total] = Item(cost, val * cost);
	}
}

void Dp()//背包Dp
{
	for (int i = 0; i <= n; ++i) f[i].reset();
	f[Ct][Cs] = 1;
	for (int i = 1; i <= total; ++i) {
		for (int j = n; j >= A[i].cost; --j) {
			f[j] = f[j] | (f[j - A[i].cost] << A[i].val);
		}
	}
}

class KingdomAndDice {
    public:
    double newFairness(vector<int> firstDie, vector<int> secondDie, int X) {
		total = 0;
		Cs = 0;
		Ct = 0;
		n = secondDie.size();
		sort(secondDie.begin(), secondDie.end());//统计题目背包以使用的容量的为Ct，已获得价值为Cs
		for (int i = 0; i < n; ++i) {
			if (firstDie[i]) {
				++Ct;
				Cs += lower_bound(secondDie.begin(), secondDie.end(), firstDie[i]) - secondDie.begin();
			}
		}
		AddItem(n, 0);
		secondDie.push_back(X + 1);
		for (int i = 1; i <= n; ++i) {//统计每个物品，并是一年个二进制拆分
			int Cnt = secondDie[i] - secondDie[i - 1] - 1;
			for (int j = 0; j < n; ++j) {
				if (firstDie[j] >= secondDie[i - 1] && firstDie[j] <= secondDie[i]) {
					--Cnt;
				}
			}
			AddItem(Cnt, i);
		}
		Dp();//背包Dp
		int Min = 2e9, mt = -1, Cri = n * n;
		for (int i = 0; i <= n * n; ++i) {//统计所以可以得到的价值中最优的一个
			if (f[n][i]) {
				if (abs(Cri - i * 2) < Min) {
					Min = abs(Cri - i * 2);
					mt = i;
				}
			}
		}
        return mt / (double)Cri;//返回答案
    }
};
