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
vector<int> s1, t1, l1, s2, t2, l2;
struct edge
{
	int to, next, xi;
	LL val;
	edge() {}
	edge(int _t, int _n, LL _v, int _x):to(_t), next(_n), val(_v), xi(_x) {}
}e[maxn * 5];//边，设总长度为length，val表示边的权值，xi表示这条边包含的length的系数
int head[maxn], et = -1;//边的头指针
int cnt[maxn];//这个点在spfa中进入队列多少次
int last[maxn], cir[maxn];//一个负环的length的系数
pair<LL, int> dist[maxn];//点到0点的距离，first是最短距离，second是最短距离下的length的系数

void Addedge(int fr, int to, LL va, int x)//加边
{
	e[++et] = edge(to, head[fr], va, x), head[fr] = et;
}

void Reset()//重置所有的边
{
	memset(head, -1, sizeof(head));
	et = -1;
}

void Spfa()//最短路
{
	static int line[maxn + 3];
	static bool ever[maxn];
	int h = 0, t = 0, cur;
	memset(ever, 0, sizeof(ever));
	memset(cnt, 0, sizeof(cnt));
	memset(cir, 0, sizeof(cir));
	for (int i = 0; i <= n; ++i) {
		dist[i].first = 1e18;
		dist[i].second = 0;
	}
	dist[0].first = 0;
	++cnt[0];
	ever[h] = 0;
	line[h] = 0;
	h = (h == maxn) ? 0 : (h + 1);
	while (h != t) {
		cur = line[t];
		t = (t == maxn) ? 0 : (t + 1);
		ever[cur] = 0;
		for (int i = head[cur]; i != -1; i = e[i].next) {
			if (dist[e[i].to].first > dist[cur].first + e[i].val) {
				dist[e[i].to].first = dist[cur].first + e[i].val;
				dist[e[i].to].second = dist[cur].second + e[i].xi;
				if (ever[e[i].to] == 0) {
					++cnt[e[i].to];
					if (cnt[e[i].to] == n) {//如果入队n次，说明有负环
						last[e[i].to] = dist[e[i].to].second;
					}
					if (cnt[e[i].to] == n * 2) {//再入队若干次，得到负环上的length的系数是正是负
						cir[e[i].to] = dist[e[i].to].second - last[e[i].to];
						return;
					}
					ever[e[i].to] = 1;
					line[h] = e[i].to;
					h = (h == maxn) ? 0 : (h + 1);
				}
			}
		}
	}
}

bool Check(LL length, bool flag)//检查length是否是上（下）边界，flag=0为检查下边界
{
	Reset();
	for (int i = 1; i <= n; ++i) {
		Addedge(i, i - 1, -1, 0);
	}
	for (int i = 0; i < s1.size(); ++i) {
		if (s1[i] <= t1[i]) {
			Addedge(t1[i], s1[i], -l1[i], 0);
		}
		else {
			Addedge(t1[i], s1[i], length - l1[i], 1);
		}
	}
	for (int i = 0; i < s2.size(); ++i) {
		if (s2[i] <= t2[i]) {
			Addedge(s2[i], t2[i], l2[i], 0);
		}
		else {
			Addedge(s2[i], t2[i], l2[i] - length, -1);
		}
	}
	Addedge(0, n, length, 1);
	Addedge(n, 0, -length, 1);//差分约束建边
	Spfa();
	if (flag == 0) {//根据最短路是一个凸的分段函数，一个上凸壳来判断他在边界的那一边
		for (int i = 0; i <= n; ++i) {
			if (cnt[i] >= n * 2) {
				if (cir[i] >= 0) {
					return 0;
				}
				else {
					return 1;
				}
			}
			else if (dist[i].first < 0) {
				if (dist[i].second >= 0) {
					return 0;
				}
				else {
					return 1;
				}
			}
		}
		return 1;
	}
	else {
		for (int i = 0; i <= n; ++i) {
			if (cnt[i] >= n * 2) {
				if (cir[i] <= 0) {
					return 0;
				}
				else {
					return 1;
				}
			}
			else if (dist[i].first < 0) {
				if (dist[i].second <= 0) {
					return 0;
				}
				else {
					return 1;
				}
			}
		}
		return 1;
	}
}

class YamanoteLine {
    public:
    long long howMany(int _n, vector<int> _s1, vector<int> _t1, vector<int> _l1, vector<int> _s2, vector<int> _t2, vector<int> _l2) {
		n = _n;
		s1 = _s1, t1 = _t1, l1 = _l1;
		s2 = _s2, t2 = _t2, l2 = _l2;
		LL Lowbound, Upbound;
		LL l, r, mid;
		l = 0, r = 1e11;
		while (l != r) {//二分下边界
			mid = (l + r) / 2;
			if (Check(mid, 0)) r = mid;
			else l = mid + 1;
		}
		Lowbound = l;
		l = 0, r = 1e11;
		while (l != r) {//二分上边界
			mid = (l + r + 1) / 2;
			if (Check(mid, 1)) l = mid;
			else r = mid - 1;
		}
		Upbound = l;
		//dig("%lld %lld\n", Lowbound, Upbound);
		if (Upbound >= 1e11-5) return -1;//如果上边界超出可能的最大值，则length可以无穷大
		else if (Lowbound > Upbound) return 0;
        else if (Lowbound == Upbound) {//如果下边界等于上边界则可能是正好凸壳中没有斜率为0的一段
			if (Check(Lowbound, 0)) return 1;
			else return 0;
		}
		else {
			return Upbound - Lowbound + 1;
		}
    }
};
