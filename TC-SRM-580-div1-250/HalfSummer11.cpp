#line 2 "EelAndRabbit.cpp"
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
/*
   一定是在某条eel的头/尾处下手比较优，枚举这些位置即可。
*/
int n, val[maxn * 2], vt; // n是eel的条数，val[], vt存放所有出现过的eel头尾坐标
class EelAndRabbit {
	public:
		int getmax(vector <int> l, vector <int> t) {
			n = l.size(); vt = 0;
			for (int i = 0; i < n; ++i) 
				val[++vt] = t[i], val[++vt] = t[i] + l[i];  // 记录头尾位置
			sort(val + 1, val + vt + 1);
			vt = unique(val + 1, val + vt + 1) - val - 1;
			int ans = 0;
			for (int i = 1; i <= vt; ++i) 
				for (int j = i + 1; j <= vt; ++j) { // 枚举两次抓的位置val[i]与val[j]
					int sum = 0;
					for (int k = 0; k < n; ++k) // 判断第k条eel是否被抓住了
						sum += ((t[k] <= val[i] && l[k] + t[k] >= val[i]) || (t[k] <= val[j] && val[j] <= l[k] + t[k]));
					ans = max(ans, sum);
				}
			return ans;
		}
};
