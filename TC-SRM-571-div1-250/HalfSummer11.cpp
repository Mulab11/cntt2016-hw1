#line 2 "FoxAndMp3.cpp"
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
#define maxn 
typedef long long ll;
using namespace std;
class FoxAndMp3 {
	public:
		vector <string> playList(int n) {
			vector <string> ans;
			int lim = min(50, n);
			ans.pb("1.mp3");
			int now = 1; string str = "1";
			for (int i = 2; i <= lim; ++i) {
				if (now * 10 <= n) {
					now *= 10; str = str + "0";
					ans.pb(str + ".mp3"); continue;
				}
				for (int i = str.length() - 1; i >= 0; --i)
					if (str[i] < '9') {
						int x = 0;
						for (int j = 0; j <= i; ++j)
							x = x * 10 + str[j] - '0';
						++x;
						if (x <= n) {
							string tmp = "";
							for (int j = 0; j < i; ++j)
								tmp = tmp + str[j];
							tmp = tmp + char(str[i] + 1);
							now = x; str = tmp;
							ans.pb(str + ".mp3");
							break;
						}
					}
			}
			return ans;
		}
		
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { int Arg0 = 3; string Arr1[] = {"1.mp3", "2.mp3", "3.mp3" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, playList(Arg0)); }
	void test_case_1() { int Arg0 = 10; string Arr1[] = {"1.mp3", "10.mp3", "2.mp3", "3.mp3", "4.mp3", "5.mp3", "6.mp3", "7.mp3", "8.mp3", "9.mp3" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, playList(Arg0)); }
	void test_case_2() { int Arg0 = 16; string Arr1[] = {"1.mp3", "10.mp3", "11.mp3", "12.mp3", "13.mp3", "14.mp3", "15.mp3", "16.mp3", "2.mp3", "3.mp3", "4.mp3", "5.mp3", "6.mp3", "7.mp3", "8.mp3", "9.mp3" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, playList(Arg0)); }
	void test_case_3() { int Arg0 = 32; string Arr1[] = {"1.mp3", "10.mp3", "11.mp3", "12.mp3", "13.mp3", "14.mp3", "15.mp3", "16.mp3", "17.mp3", "18.mp3", "19.mp3", "2.mp3", "20.mp3", "21.mp3", "22.mp3", "23.mp3", "24.mp3", "25.mp3", "26.mp3", "27.mp3", "28.mp3", "29.mp3", "3.mp3", "30.mp3", "31.mp3", "32.mp3", "4.mp3", "5.mp3", "6.mp3", "7.mp3", "8.mp3", "9.mp3" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, playList(Arg0)); }
	void test_case_4() { int Arg0 = 100000009; string Arr1[] = {"1.mp3", "10.mp3", "100.mp3", "1000.mp3", "10000.mp3", "100000.mp3", "1000000.mp3", "10000000.mp3", "100000000.mp3", "100000001.mp3", "100000002.mp3", "100000003.mp3", "100000004.mp3", "100000005.mp3", "100000006.mp3", "100000007.mp3", "100000008.mp3", "100000009.mp3", "10000001.mp3", "10000002.mp3", "10000003.mp3", "10000004.mp3", "10000005.mp3", "10000006.mp3", "10000007.mp3", "10000008.mp3", "10000009.mp3", "1000001.mp3", "10000010.mp3", "10000011.mp3", "10000012.mp3", "10000013.mp3", "10000014.mp3", "10000015.mp3", "10000016.mp3", "10000017.mp3", "10000018.mp3", "10000019.mp3", "1000002.mp3", "10000020.mp3", "10000021.mp3", "10000022.mp3", "10000023.mp3", "10000024.mp3", "10000025.mp3", "10000026.mp3", "10000027.mp3", "10000028.mp3", "10000029.mp3", "1000003.mp3" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, playList(Arg0)); }
	void test_case_5() { int Arg0 = 1; string Arr1[] = {"1.mp3" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(5, Arg1, playList(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main() {
	FoxAndMp3 ___test;
	int x; cin >> x;
	___test.run_test(x);
	system("pause");
}
// END CUT HERE
