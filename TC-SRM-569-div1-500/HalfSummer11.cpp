#line 2 "TheJediTest.cpp"
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
#define maxn 30
typedef long long ll;
using namespace std;
int n, b[maxn]; // n是楼层数量，b[i]表示第i层目前的学生数量
class TheJediTest {
	public:
		int minimumSupervisors(vector <int> a, int K) {
			n = a.size();
			for (int i = 0; i < n; ++i) b[i] = a[i];
			for (int i = 0; i < n - 1; ++i) {
				if (b[i] % K > a[i]) { // 此时，无法通过把多出的学生丢到下一层来使得这一层的人数可以被K整除
					b[i + 1] -= min(a[i + 1], K - b[i] % K); // 或者正好把这一层补成能被K整除，或者，下一层的人数不够，一定也是都丢过来比较合算
					b[i] += min(a[i + 1], K - b[i] % K);
				} else { // 否则就把多出的学生丢下去
					b[i + 1] += b[i] % K;
					b[i] -= b[i] % K;
				}
			}
			int ret = 0;
			for (int i = 0; i < n; ++i)
				ret += (b[i] + K - 1) / K;
			return ret;
		}
};
