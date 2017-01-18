#line 2 "CandyOnDisk.cpp"
#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<sstream>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<cstring>
#define cl(x) memset(x, 0, sizeof(x));
#define pii pair<int, int>
#define fr first
#define sc second
#define mp make_pair
#define pb push_back
#define oo 0x3f3f3f3f
#define maxn 60
#define eps 1e-40
typedef long long ll;
using namespace std;
int n, q[maxn], qh, qt; // n是圆的个数，q是spfa的队列
long double L[maxn], R[maxn]; // 对于圆i，可达区域是半径为L[i], R[i]的两个圆形成的圆环
bool inq[maxn]; // 记录某个点是否在队列里
long double mul(long double x) { // x ^ 2
	return x * x;
}
long double dis(long double x1, long double y1, long double x2, long double y2) {
	return sqrt(mul(x1 - x2) + mul(y1 - y2));
}
int dcmp(long double x) {
	return fabs(x) < eps ? 0 : x > 0 ? 1 : -1;
}
bool gmin(long double &a, long double b) {
	if (dcmp(b - a) < 0)
		return a = b, 1;
	return 0;
}
bool gmax(long double &a, long double b) {
	if (dcmp(b - a) > 0)
		return a = b, 1;
	return 0;
}
class CandyOnDisk {
	public:
		string ableToAchieve(vector <int> x, vector <int> y, vector <int> r, int sx, int sy, int tx, int ty) {
			if (sx == tx && sy == ty) return "YES";
			n = x.size();
			for (int i = 0; i < n; ++i) L[i] = 1e20, R[i] = -1e20;
			qh = qt = 0;
			for (int i = 0; i < n; ++i) {
				long double tmp = dis(x[i], y[i], sx, sy);
				if (dcmp(r[i] - tmp) >= 0) {
					q[qt++] = i;  L[i] = R[i] = tmp; inq[i] = 1; // 将从起点直接可达的圆加入队列，更新它们的L和R
				}
			}
			int now;
			while (qh != qt) {
				now = q[qh++]; if (qh == maxn) qh = 0;
				bool ref = 0; // 记录now这个圆本身在过程中是否被更新
				for (int j = 0; j < n; ++j) {
					if (j == now) continue;
					long double tmp = dis(x[now], y[now], x[j], y[j]);
					if (dcmp(tmp) == 0) { // 特殊处理同心圆的情况
						if (r[j] <= r[now]) continue;
						bool flag = 0;
						flag |= gmin(L[j], L[now]);
						flag |= gmax(R[j], R[now]);
						if (flag && !inq[j]) {
							q[qt++] = j; if (qt == maxn) qt = 0;
						}
						continue;
					}
					if (dcmp(L[now] - (tmp + r[j])) > 0 || dcmp(tmp - r[j] - R[now]) > 0) // 圆now的圆环与圆j不交，不更新
						continue;
					bool flag = 0;
					ref |= gmin(L[now], max(tmp - r[j], (long double)0.0)); // 否则，可以发现经过几轮相互更新后，两个圆的L,R会分别进行以下的更新
					ref |= gmax(R[now], min(tmp + r[j], (long double)r[now]));
					flag |= gmin(L[j], max(tmp - r[now], (long double)0.0));
					flag |= gmax(R[j], min(tmp + r[now], (long double)r[j]));
					if (!flag) continue; 
					if (!inq[j]) { // 若这一轮成功更新了第j个圆的可达范围，将它加入队列
						inq[j] = 1; q[qt++] = j; if (qt == maxn) qt = 0;
					}
				}
				inq[now] = 0;
				if (ref) { // now本身的可达范围也已经被更新，加入队列
					inq[now] = 1; 
					q[qt++] = now; if (qt == maxn) qt = 0;
				}
			}
			for (int i = 0; i < n; ++i)
				if (dcmp(R[i] - L[i]) >= 0) {
					long double tmp = dis(x[i], y[i], tx, ty);
					if (dcmp(tmp - L[i]) >= 0 && dcmp(R[i] - tmp) >= 0) // 若位于该圆的可达区域内，则t可达
						return "YES";
				}
			return "NO";
		}
};
