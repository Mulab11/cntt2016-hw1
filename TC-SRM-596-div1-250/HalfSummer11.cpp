#line 2 "IncrementAndDoubling.cpp"
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
class IncrementAndDoubling {
	public:
		int getMin(vector <int> a) {
			int ans = 0, n = a.size();
			bool flag = 0;
			while (1) {
				for (int i = 0; i < n; ++i) 
					if (a[i] & 1) {
						++ans; --a[i];
					}
				flag = 1;
				for (int i = 0; i < n; ++i)
					if (a[i]) 
						flag = 0, a[i] /= 2; 
				if (flag) break;
				++ans;
			}
			return ans;
		}
};
