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
int px[maxn], py[maxn];
struct Rec
{
	int x1, y1, x2, y2;
	Rec() {}
	Rec(int _x1, int _y1, int _x2, int _y2):x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}
}R[maxn];//每个点扩展出的正方形
int lst[maxn * 2], lt, et;//离散化
struct Event
{
	int x, y1, y2;
	bool flag;
	Event() {}
	Event(int _x, int _y1, int _y2, bool _f):x(_x), y1(_y1), y2(_y2), flag(_f) {}
	bool operator < (const Event &b) const
	{
		return x < b.x || (x == b.x && flag > b.flag);
	}
}E[maxn * 2];//扫描线事件
map<pair<int, int>, bool> Hash;//Hash用于判断是否是已经存在的点

void Build(int ti)//将每个正方形建出，并离散化y坐标，求出对x轴扫描线的加入与删除事件，并将已有的点加入map
{
	if (ti & 1) {
		ti /= 2;
		for (int i = 1; i <= n; ++i) {
			R[i].x1 = px[i] - ti;
			R[i].y1 = py[i] - ti;
			R[i].x2 = px[i] + ti + 1 + 1;
			R[i].y2 = py[i] + ti + 1 + 1;
		}
	}
	else {
		ti /= 2;
		for (int i = 1; i <= n; ++i) {
			R[i].x1 = px[i] - ti;
			R[i].y1 = py[i] - ti;
			R[i].x2 = px[i] + ti + 1;
			R[i].y2 = py[i] + ti + 1;
		}
	}
	lt = 0;
	for (int i = 1; i <= n; ++i) {
		lst[++lt] = R[i].y1;
		lst[++lt] = R[i].y2;
	}
	sort(lst + 1, lst + 1 + lt);
	lt = unique(lst + 1, lst + 1 + lt) - lst - 1;
	et = 0;
	for (int i = 1; i <= n; ++i) {
		E[++et] = Event(R[i].x1, lower_bound(lst + 1, lst + 1 + lt, R[i].y1) - lst, lower_bound(lst + 1, lst + 1 + lt, R[i].y2) - lst, 1);
		++et;
		E[et] = E[et - 1];
		E[et].x = R[i].x2;
		E[et].flag = 0;
	}
	sort(E + 1, E + 1 + et);
	Hash.clear();
	for (int i = 1; i <= n; ++i) {
		Hash[make_pair(px[i], py[i])] = 1;
	}
}

bool Find(int x, int y, int ti)//查看这个的点是否是在最后已经存在的点
{
	return !(Hash.count(make_pair(x + ti / 2, y + ti / 2)));
}

bool Check(int ti)//检查如果进行ti步，是否合法
{
	int cnt[maxn * 2] = {0};
	int last[maxn * 2] = {0};
	int l, r, S, T, lastCheck = -2e9;
	E[0].x = E[1].x;
	memset(last, -0x3f, sizeof(last));
	for (int i = 1; i <= et; ++i) {
		for (int j = 1; j < lt; ++j) {//last表示从当前扫描线向前最长连续的被覆盖的长度
			if (cnt[j] == 0) {
				last[j] = 0;
			}
			else {
				last[j] += E[i].x - E[i - 1].x;
			}
		}
		if (lastCheck != E[i].x) {
			for (int L = ti + 1; L < ti + 1 + E[i].x - lastCheck; ++L) {//暴力检查每个合法的正方形是否是一个新点
				bool ok = 0;
				S = 1;
				while (S < lt) {
					T = S;
					while (T < lt && last[T] >= L) ++T;
					for (int j = lst[S]; j <= lst[T] - ti - 1; ++j) {
						ok = 1;
						if (Find(E[i].x - L, j, ti)) {
							return 0;
						}
					}
					S = T + 1;
				}
				if (!ok) break;
			}
			lastCheck = E[i].x;
		}
		for (int j = E[i].y1; j < E[i].y2; ++j) {//cnt[i]表示第i条线段被覆盖次数
			cnt[j] += ((E[i].flag) ? 1 : -1);
		}
	}
	return 1;
}

class DrawingPointsDivOne {
    public:
    int maxSteps(vector<int> x, vector<int> y) {
		n = x.size();
		for (int i = 0; i < n; ++i) {
			px[i + 1] = x[i];
			py[i + 1] = y[i];
		}
		int l, r, mid;
		l = 0, r = 155;
		while (l != r) {//二分游戏步数
			mid = (l + r + 1) / 2;
			Build(mid);
			if (Check(mid)) l = mid;
			else r = mid - 1;
		}
		if (r > 145) return -1;//如果超过坐标差的最大值，则可以无限大
        else return l;
    }
};

