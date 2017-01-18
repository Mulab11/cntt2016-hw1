#line 2 "DrawingPointsDivOne.cpp"
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
#define maxn 600
typedef long long ll;
using namespace std;
const int size = 580;
const int dx[] = {1, 1, -1, -1};
const int dy[] = {1, -1, 1, -1};
int n;
vector <int> x, y; // 存放目前点的坐标
bool ori[maxn][maxn];　// 目前board的情况
bool lst[maxn][maxn], now[maxn][maxn];　// lst是step - 1步前，board的情况，now是step步前，board的情况
int sum[maxn][maxn]; // 目前board的二维前缀和
class DrawingPointsDivOne {
	public:
		int maxSteps(vector <int> X, vector <int> Y) {
			cl(ori); cl(lst); cl(now); x = X; y = Y; n = x.size();
			for (int i = 0; i < n; ++i)
				(x[i] += 141) *= 2, (y[i] += 141) *= 2; // 坐标变换
			for (int i = 0; i < n; ++i)
				ori[x[i]][y[i]] = now[x[i]][y[i]] = 1;
			for (int step = 1; step <= size / 4; ++step) {
				memcpy(lst, now, sizeof(lst)); cl(now);
				for (int i = 1; i <= size; ++i)
					for (int j = 1; j <= size; ++j)
						if (lst[i][j]) { // 在step - 1步前存在的点，在step步前，其四个角上都必须有点
							for (int d = 0; d < 4; ++d) {
								int nx = i + dx[d], ny = j + dy[d];
								if (nx < 1 || ny < 1 || nx > size || ny > size) continue;
								now[nx][ny] = 1;
							}
						}
				cl(sum);
				for (int i = 1; i <= size; ++i)
					for (int j = 1; j <= size; ++j)
						sum[i][j] = now[i][j] + sum[i][j - 1];
				for (int i = 1; i <= size; ++i)
					for (int j = 1; j <= size; ++j)
						sum[i][j] += sum[i - 1][j]; // 计算二维前缀和
				for (int i = 1; i + 2 * step <= size; ++i)
					for (int j = 1; j + 2 * step <= size; ++j)
						if (sum[i + 2 * step][j + 2 * step] - sum[i - 1][j + 2 * step] - sum[i + 2 * step][j - 1] + sum[i - 1][j - 1] == (step + 1) * (step + 1) && !ori[i + step][j + step])
							return step - 1; // 若这个(1 + 2 * step) ^ 2的正方形内，间隔2地放满了点，推到目前状态时，位置i + step, j + step上也必须有点，若出现了矛盾，就不能推到step步前
			}
			return -1;
		}
};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
