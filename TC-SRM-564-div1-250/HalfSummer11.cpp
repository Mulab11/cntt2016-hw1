#line 2 "KnightCircuit2.cpp"
#include<vector>
#include<list>
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
#define maxn 110
typedef long long ll;
using namespace std;
class KnightCircuit2 {
	public:
		int maxSize(int n, int m) {
			if (n > m) swap(n, m);
			// 打表发现：
			if (n == 1) return 1;
			if (n == 2) return (m + 1) / 2;
			if (n == 3) return m == 3 ? 8 : n * m;
			return n * m;
		}
};

