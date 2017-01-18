#line 2 "CheckerFreeness.cpp"
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
#define maxn 250
typedef long long ll;
using namespace std;
int wx[maxn], wy[maxn], n, bx[maxn], by[maxn], m; // n是白点的数量，wx/wy是白点的坐标；m是黑点的数量，bx/by是黑点的坐标
struct poi {
	int x, y, id;
	poi() {}
	poi(int _x, int _y) { x = _x; y = _y; }
	poi operator + (const poi &b) { return poi(x + b.x, y + b.y); }
	poi operator - (const poi &b) { return poi(x - b.x, y - b.y); }
	ll operator * (const poi &b) { return 1ll * x * b.y - 1ll * y * b.x; } // 叉积
};
bool operator < (poi a, poi b) {
	return a * b < 0; 
}
poi W[maxn], B[maxn];
void read(vector <string> tmp, int a[maxn], int &n) { // 把tmp里的内容读到a中去，n是读到的数的个数
	string s = "";
	for (int i = 0; i < tmp.size(); ++i) s = s + tmp[i];
	int len = s.length(); n = 0;
	for (int pos = 0; pos < len; ++pos) {
		if (s[pos] == ' ') continue;
		int x = 0;
		while (pos < len && s[pos] >= '0' && s[pos] <= '9')
			x = x * 10 + s[pos] - '0', ++pos;
		a[++n] = x;
	}
}
poi tmp[maxn]; // 存白点相对于被选中的两个黑点的坐标
bool side[maxn]; // side[i] = 1,表示第i个点在线段l -> r的左侧
pii pos[maxn], lim[maxn]; // pos表示在线段l -> r左侧的点，其相对于l，相对于r，分别是顺时针第pos[i].fr, pos[i].sc的。lim表示在l -> r右侧的点，与它，选中的l/r，能形成凸多边形的左侧点，需要满足fr  >= lim[i].fr, sc <= lim[i].sc
bool cmp(const pii &a, const pii &b) {
	return a.fr == b.fr ? a.sc < b.sc : a.fr > b.fr; 
}
int c[maxn]; // 树状数组
void add(int x) { // 单点加
	for (int i = x; i <= n; i += (i & (-i))) ++c[i];
}
int get(int x) { // 前缀和
	int ret = 0;
	for (int i = x; i; i -= (i & (-i))) ret += c[i];
	return ret;
}
bool check(poi l, poi r) { // 选择l,r两个黑点为对角上的黑点
	cl(side); int k = 0, p = 0;
	for (int i = 1; i <= n; ++i)
		if ((W[i] - r) * (l - r) > 0ll) side[i] = 1; // 判断白点在两个黑点的哪一侧
	for (int i = 1; i <= n; ++i)
		if (side[i]) tmp[++k] = W[i] - l, tmp[k].id = k; // 计算相对l的极角
	sort(tmp + 1, tmp + k + 1); // 因为都在pi的范围内，所以可以直接用叉积来排序
	for (int i = 1; i <= k; ++i) pos[tmp[i].id].fr = i; // 确定下相对l极角序的排名
	for (int i = 1; i <= n; ++i)
		if (!side[i]) 
			lim[++p].fr = upper_bound(tmp + 1, tmp + k + 1, l - W[i]) - tmp; // 确定下对应的左侧点，相对l的极角序至少要排在第几位
	k = 0; p = 0; // 同理计算相对r的极角序
	for (int i = 1; i <= n; ++i)
		if (side[i]) tmp[++k] = W[i] - r, tmp[k].id = k;
	sort(tmp + 1, tmp + k + 1);
	for (int i = 1; i <= k; ++i) pos[tmp[i].id].sc = i;
	for (int i = 1; i <= n; ++i)
		if (!side[i])
			lim[++p].sc = lower_bound(tmp + 1, tmp + k + 1, r - W[i]) - tmp - 1;
	cl(c);
	sort(pos + 1, pos + k + 1, cmp); int tp = 1;  
	sort(lim + 1, lim + p + 1, cmp); // 都根据两维关键字排序
	for (int i = 1; i <= p; ++i) {
		while (tp <= k && pos[tp].fr >= lim[i].fr) // 把fr这维满足条件的左侧点加入树状数组的sc位置
			add(pos[tp++].sc);
		if (get(lim[i].sc)) return 1; // 存在满足条件的点，形成了一个checker
	}
	return 0;
}
class CheckerFreeness {
	public:
		string isFree(vector <string> whiteX, vector <string> whiteY, vector <string> blackX, vector <string> blackY) {
			read(whiteX, wx, n); read(whiteY, wy, n);
			read(blackX, bx, m); read(blackY, by, m);
			for (int i = 1; i <= n; ++i) W[i] = poi(wx[i], wy[i]); 
			for (int i = 1; i <= m; ++i) B[i] = poi(bx[i], by[i]); // 把黑点和白点的坐标搞出来
			for (int i = 1; i <= m; ++i)
				for (int j = i + 1; j <= m; ++j) // 枚举对角线上的黑点
					if (check(B[i], B[j])) return "NO";
			return "YES";
		}
};
