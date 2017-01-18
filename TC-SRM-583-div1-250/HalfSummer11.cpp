#line 2 "TravelOnMars.cpp"
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
typedef long long ll;
using namespace std;
int n, dis[maxn][maxn];
void gmin(int &a, int b) {
	if (b < a) a = b;
}
class TravelOnMars {
	public:
		int minTimes(vector <int> range, int s, int t) {
			n = range.size();
			memset(dis, 0x3f, sizeof(dis));
			for (int i = 0; i < n; ++i) dis[i][i] = 0;
			for (int i = 0; i < n; ++i)
				for (int j = 0; j < n; ++j)
					if (((i < j) && ((j - i <= range[i]) || (n + i - j) <= range[i])) || ((i > j) && ((i - j <= range[i]) || (n + j - i) <= range[i])))
						gmin(dis[i][j], 1);
			for (int k = 0; k < n; ++k)
				for (int i = 0; i < n; ++i)
					for (int j = 0; j < n; ++j)
						if (k != i && k != j && i != j)
							gmin(dis[i][j], dis[i][k] + dis[k][j]);
			return dis[s][t];
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
