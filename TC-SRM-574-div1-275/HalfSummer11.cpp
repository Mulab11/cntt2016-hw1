#line 2 "TheNumberGame.cpp"
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
#define maxn 20
typedef long long ll;
using namespace std;
/*
   Manao 获胜当且仅当B或B翻转后是A的子串
*/
int n, m, a[maxn], b[maxn]; // n, a[], m, b[]分别存放A和B的每个位
class TheNumberGame {
	public:
		string determineOutcome(int A, int B) {
			for (n = 0; A; ++n) { 
				a[n] = A % 10; A /= 10;
			}
			for (m = 0; B; ++m)
				b[m] = B % 10, B /= 10;
			for (int o = 0; o <= 1; ++o) { // 判断B/B的翻转是否是A的子串
				for (int i = 0; i + m <= n; ++i) { // 暴力枚举起始点
					bool flag = 1;
					for (int j = 0; j < m; ++j) 
						if (b[j] != a[i + j]) {
							flag = 0; break;
						}
					if (flag) return "Manao wins";
				}
				reverse(b + 0, b + m);
			}
			return "Manao loses";
		}
};
