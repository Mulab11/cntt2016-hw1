#line 2 "ColorfulWolves.cpp"
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
int n, f[maxn][maxn]; // f[i][j] 存i到j的最短路
class ColorfulWolves {
	public:
		int getmin(vector <string> cmap) {
			n = cmap.size();
			memset(f, 0x3f, sizeof(f));
			for (int i = 0; i < n; ++i) {
				int sum = 0; // 存i点出发，目前已经有几条边
				for (int j = 0; j < n; ++j)
					if (cmap[i][j] == 'Y') 
						f[i][j] = sum++; // 为了走这条边，需要砍掉之前的sum条边，相当于这条边的边权
			}
			for (int k = 0; k < n; ++k) // Floyd求最短路
				for (int i = 0; i < n; ++i)
					for (int j = 0; j < n; ++j)
						if (i != j && i != k && j != k)
							f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
			if (f[0][n - 1] == oo) return -1; 
			return f[0][n - 1]; // 求出的最短路，就是从0走到n - 1最少需要砍掉的边数
		}
		
};
