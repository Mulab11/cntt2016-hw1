#line 2 "TheNumberGameDivOne.cpp"
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
typedef long long ll;
using namespace std;
/*
   打表找规律得到，后手必胜 <==> n为奇数 || n = 2 ^ k且k为奇数
*/
class TheNumberGameDivOne {
	public:
		string find(long long n) {
			int cnt = 0;
			if (n & 1ll) return "Brus";
			while (n % 2ll == 0)
				n /= 2ll, ++cnt;
			if (n == 1ll && (cnt & 1)) return "Brus";
			return "John";
		}
};
