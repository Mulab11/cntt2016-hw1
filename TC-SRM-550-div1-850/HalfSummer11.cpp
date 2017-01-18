#line 2 "ConversionMachine.cpp"
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
#define maxs 80
#define maxn 12
#define mo 1000000007
typedef long long ll;
using namespace std;
// 扣除必须的花费后，字符串某时的状态可以用其中距离word2有0/1/2个字符的字符的个数来表示，个数最多有C(11 + 2, 2) = 78 种
int n, tot, num[maxn][maxn]; // tot 存储不同状态的个数， num[i][j] 存储有i个字符与word2中对应位置相同，j个字符与对应位置距离为1的状态所对应的编号
void add(int &a, int b) {
	a += b; a %= mo;
}
struct mat { // 下面是矩阵和矩阵的加法乘法
	int x[maxs][maxs];
}I, trans;
mat operator + (const mat &a, const mat &b) {
	mat c; cl(c.x);
	for (int i = 0; i < tot; ++i)
		for (int j = 0; j < tot; ++j)
			add(c.x[i][j], (a.x[i][j] + b.x[i][j]) % mo);
	return c;
}
mat operator * (const mat &a, const mat &b) {
	mat c; cl(c.x);
	for (int k = 0; k < tot; ++k)
		for (int i = 0; i < tot; ++i)
			for (int j = 0; j < tot; ++j)
				add(c.x[i][j], 1ll * a.x[i][k] * b.x[k][j] % mo);
	return c;
}
mat calc(mat a, int b) { // 计算a ^ 0 + a ^ 1 + ... + a ^ b
	mat c, d, e;
	cl(c.x); cl(d.x); cl(e.x);
	if (b < 0) return d;
	c = I; e = a; d = I;
	for (; b; b >>= 1, e = e * a + e, a = a * a) 
		if (b & 1) {
			d = e * c + d;
			c = c * a;
		}
	return d;
}
class ConversionMachine {
	public:
		int countAll(string word1, string word2, vector <int> costs, int maxCost) {
			n = word1.size(); 
			tot = 0;
			for (int i = 0; i <= n; ++i)
				for (int j = 0; i + j <= n; ++j)
					num[i][j] = tot++; // 枚举所有可能的状态，分配编号
			cl(I.x); for (int i = 0; i < tot; ++i) I.x[i][i] = 1; // 做一个I
			int need = 0, tmp, cnt0 = 0, cnt1 = 0; // need是word1 -> word2最少需要的步数，tmp存每个位置字符离目标字符的距离，cnt0/cnt1分别记录距离为0/1的位置个数
			for (int i = 0; i < n; ++i) {
				tmp = (word2[i] - word1[i] + 3) % 3;
				if (tmp == 0) ++cnt0;
				if (tmp == 1) 
					maxCost -= costs[word1[i] - 'a'], ++cnt1; // 根据距离，先扣除必须支出的花费
				if (tmp == 2)
					maxCost -= costs[word1[i] - 'a'] + costs[(word1[i] - 'a' + 1) % 3];
				if (maxCost < 0) return 0; // ! 必须在这里及时判断，放到最后的话，可能会爆int
				need += tmp; 
			}
			if (maxCost < 0) return 0;
			int extra = maxCost / (costs[0] + costs[1] + costs[2]); // 扣除必要的花费后，剩下的花费可供完成至多extra个循环
			extra *= 3; // 也就是3 * extra个操作
			cl(trans.x);
			for (int i = 0; i <= n; ++i)
				for (int j = 0; i + j <= n; ++j) {
					int k = n - i - j; // 给转移矩阵赋值，每次可以选择一个与目标距离为0/1/2的，将其距离变成2/0/1
					if (i) trans.x[num[i][j]][num[i - 1][j]] = i;
					if (j) trans.x[num[i][j]][num[i + 1][j - 1]] = j;
					if (k) trans.x[num[i][j]][num[i][j + 1]] = k;
				}
			return calc(trans, need + extra).x[num[cnt0][cnt1]][num[n][0]]; // 所有步数在extra + need之内，且从(cnt0, cnt1)出发，到(n, 0)终止的操作序列个数，就是所求的答案
		}

		// BEGIN CUT HERE
	public:
		void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
		template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
		void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
		void test_case_0() { string Arg0 = "a"; string Arg1 = "b"; int Arr2[] = {100,2,3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 205; int Arg4 = 2; verify_case(0, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }
		void test_case_1() { string Arg0 = "abcba"; string Arg1 = "abcba"; int Arr2[] = {67,23,43}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; int Arg4 = 1; verify_case(1, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }
		void test_case_2() { string Arg0 = "cccccccc"; string Arg1 = "aaaaaaaa"; int Arr2[] = {10000000,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 100; int Arg4 = 40320; verify_case(2, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }
		void test_case_3() { string Arg0 = "aa"; string Arg1 = "cc"; int Arr2[] = {1,10,100}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1787; int Arg4 = 123611681; verify_case(3, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }

		// END CUT HERE

};

// BEGIN CUT HERE
int main() {
	int x;
	ConversionMachine ___test;
	cin >> x;
	___test.run_test(x);
	system("pause");
}
// END CUT HERE
