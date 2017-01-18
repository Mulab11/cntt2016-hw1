#line 2 "Egalitarianism.cpp"
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
class Egalitarianism {
	public:
		int maxDifference(vector <string> G, int d) {
			memset(dis, 0x3f, sizeof(dis));
			int inf = dis[0][0];
			n = G.size();
			for (int i = 0; i < n; ++i) 
				for (int j = i + 1; j < n; ++j)
					if (G[i][j] == 'Y')
						dis[i][j] = dis[j][i] = d;
			for (int k = 0; k < n; ++k)
				for (int i = 0; i < n; ++i)
					for (int j = 0; j < n; ++j)
						if (k != i && k != j && i != j)
							dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			int ans = 0;
			for (int i = 0; i < n; ++i)
				for (int j = i + 1; j < n; ++j)
					ans = max(ans, dis[i][j]);
			if (ans == inf)
				return -1;
			else
				return ans;
		}
		

};



// Powered by FileEdit
// Powered by TZTester 1.01 [25-Feb-2003]
// Powered by CodeProcessor
