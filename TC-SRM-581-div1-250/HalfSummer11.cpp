#line 2 "SurveillanceSystem.cpp"
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
bool t[maxn], f[maxn]; // t[i] = 1表示第i个格子必可见，f[i] = 1表示第i个格子必不可见
int n, m, num[maxn], cnt[maxn]; // n是格子个数，m是监视器个数，num[i]表示从i开始的监视器能看到num[i]个container，cnt[i]表示每轮中第i个格子被cnt[i]个合法的监视器看到。
class SurveillanceSystem {
	public:
		string getContainerInfo(string con, vector <int> rep, int L) {
			cl(t); cl(f); cl(num);
			n = con.size();
			m = rep.size();
			for (int i = 0; i < n; ++i) f[i] = 1; 
			for (int l = 0; l + L - 1 < n; ++l) 
				for (int j = l; j < l + L; ++j) // 计算范围为[l, l + L - 1]的监视器能看到几个container
					num[l] += (con[j] == 'X');
			for (int c = 0; c <= L; ++c) { // 枚举监视器看到的container的个数
				cl(cnt);
				int crep = 0, cpos = 0; // crep是能看到c个container的监视器个数，cpos是合法的位置个数
				for (int i = 0; i < m; ++i)
					if (rep[i] == c) ++crep;
				if (!crep) continue;
				for (int l = 0; l + L - 1 < n; ++l)
					if (num[l] == c) {
						++cpos;
						for (int j = l; j < l + L; ++j)
							++cnt[j]; // 这些位置能被一个合法的监视器看到
					}
				for (int i = 0; i < n; ++i) {
					if (cnt[i]) f[i] = 0; // 存在选中看到它的那个监视器的可能性，所以第i个格子就不是“一定不可见”的了
					if (cnt[i] + crep > cpos) t[i] = 1; // 根据抽屉原理，此时从cpos个合法位置中拿出crep个，必然拿到至少一个看得到i的，所以i必然可见。
				}
			}
			string ans = "";
			for (int i = 0; i < n; ++i) {
				if (f[i]) ans = ans + "-";
				if (t[i]) ans = ans + "+";
				if (!f[i] && !t[i]) ans = ans + "?";
			}
			return ans;
		}
};
