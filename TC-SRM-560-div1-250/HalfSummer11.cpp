#line 2 "TomekPhone.cpp"
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
int a[maxn * maxn], tot; // tot是可以提供的键位数量，a存这些键位所需要的击键次数
class TomekPhone {
	public:
		int minKeystrokes(vector <int> w, vector <int> room) {
			tot = 0;
			for (int i = 0; i < room.size(); ++i)
				for (int j = 1; j <= room[i]; ++j)
					a[++tot] = j; // 可以提供一个需要击键j次的位置
			if (tot < w.size()) return -1;
			sort(w.begin(), w.end());
			reverse(w.begin(), w.end()); // 从大到小排序
			sort(a + 1, a + tot + 1); // 从小到大排序
			int ans = 0;
			for (int i = 0; i < w.size(); ++i) // 给较大出现次数的字母安排击键次数少的键位 
				ans += w[i] * a[i + 1];
			return ans;
		}
};

