#line 2 "RobotHerb.cpp"
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
#define maxn 10
typedef long long ll;
using namespace std;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};
int disx[maxn], disy[maxn]; // disx[i], disy[i]分别表示经过i次操作后机器人的横纵坐标
class RobotHerb {
	public:
		long long getdist(int T, vector <int> a) {
			int n = a.size();
			int x, y, dir;
			x = 0; y = 0; dir = 0; // (x, y)为坐标，dir为朝向
			for (int t = 1; t <= 4; ++t) { // 计算经过t次操作后机器人的位置
				for (int i = 0; i < n; ++i) {
					x += dx[dir] * a[i];
					y += dy[dir] * a[i];
					dir = (dir + a[i]) % 4;
				}
				disx[t] = x; disy[t] = y; 
			}
			// 由于4次操作后，机器人的朝向必然与开始时刻相同，因此可以把T按四个划成一段，4次操作后的坐标直接乘上段数,最后一段使用预处理好的dis[T % 4]即可。
			return labs(1ll * (T / 4) * disx[4] + disx[T % 4]) + labs(1ll * (T / 4) * disy[4] + disy[T % 4]);
		}
};
