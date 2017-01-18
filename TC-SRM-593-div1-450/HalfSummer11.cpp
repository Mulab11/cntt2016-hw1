#line 2 "MayTheBestPetWin.cpp"
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
#define maxv 10010
typedef long long ll;
using namespace std;
bool f[2][maxn * maxv], O;
#define now f[O]
#define lst f[O ^ 1]
class MayTheBestPetWin {
	public:
		int calc(vector <int> A, vector <int> B) {
			cl(f); 
			now[0] = 1;
			int n = A.size(), sum = 0, suma = 0;
			for (int i = 0; i < n; ++i) {
				O ^= 1; cl(now);
				sum += A[i] + B[i];
				suma += A[i];
				for (int v = 0; v <= 500000; ++v)
					if (lst[v]) {
						now[v + A[i] + B[i]] = 1;
						now[v] = 1;
					}
			}
			int ans = oo;
			for (int v = 0; v <= 500000; ++v)
				if (now[v])
					ans = min(ans, max(v - suma, (sum - v) - suma));
			return ans;
		}
};
