#line 2 "ShoutterDiv1.cpp"
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
#define maxn 2510
typedef long long ll;
using namespace std;
/*
   题目要求相当于是要选出一些连通的区间，覆盖所有的区间，并且强制选择一个区间。
   如果没有强制选择区间，就从左往右选区间，每次选一个能被覆盖且t最大的区间，作为下一个选中的区间，这样一定是最优的。
   强制选择区间，碰到它的时候把它强行选上就行了。
*/
int n, s[maxn], t[maxn], tmp[maxn]; // n是区间个数，s[i], t[i]分别为第i个区间开始/结束的位置。tmp[i]存s[x]第i小的x
bool cmp(const int &a, const int &b) { // 按照s的大小排序
	return s[a] < s[b];
}
class ShoutterDiv1 {
	public:
		int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1) {
			string S1000 = "";
			for (int i = 0; i < s1000.size(); ++i)
				S1000 = S1000 + s1000[i];
			string S100 = "";
			for (int i = 0; i < s100.size(); ++i)
				S100 = S100 + s100[i];
			string S10 = "";
			for (int i = 0; i < s10.size(); ++i)
				S10 = S10 + s10[i];
			string S1 = "";
			for (int i = 0; i < s1.size(); ++i)
				S1 = S1 + s1[i];
			string T1000 = "";
			for (int i = 0; i < t1000.size(); ++i)
				T1000 = T1000 + t1000[i];
			string T100 = "";
			for (int i = 0; i < t100.size(); ++i)
				T100 = T100 + t100[i];
			string T10 = "";
			for (int i = 0; i < t10.size(); ++i)
				T10 = T10 + t10[i];
			string T1 = "";
			for (int i = 0; i < t1.size(); ++i)
				T1 = T1 + t1[i];
			n = S1000.size();
			for (int i = 0; i < n; ++i) {
				s[i] = (S1000[i] - '0') * 1000 + (S100[i] - '0') * 100 + (S10[i] - '0') * 10 + S1[i] - '0';
				t[i] = (T1000[i] - '0') * 1000 + (T100[i] - '0') * 100 + (T10[i] - '0') * 10 + T1[i] - '0';
				tmp[i] = i;
			}
			sort(tmp + 0, tmp + n, cmp); // 把区间按照开始位置排序，这样当前能被覆盖的区间就是连续的一段前缀
			int L = 10000, lim = 0;
			for (int i = 0; i < n; ++i)
				L = min(L, t[i]), lim = max(lim, s[i]); // 至少要覆盖[L, lim]这个区间
			int ans = 0;
			for (int x = 0; x < n; ++x) {
				int R = L, j = 0, mx = 0; bool used = 0;
				while (R < lim) {
					if (!used && s[x] <= R) { // 能选上第x个区间，把它强行选上
						used = 1; R = max(R, t[x]);
						continue;
					}
					++ans; 
					while (j < n && s[tmp[j]] <= R) // 否则，找到能选的区间里t最大的一个
						mx = max(mx, t[tmp[j]]), ++j;
					if (mx <= R && R < lim) return -1; // 没有希望再扩展
					R = max(R, mx);
				}
			}
			return ans;
		}
};
