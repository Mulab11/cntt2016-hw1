// BEGIN CUT HERE

// END CUT HERE
#line 5 "XorAndSum.cpp"
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
using namespace std;
long long p[110];
class XorAndSum
{
        public:
        long long maxSum(vector<long long> vec)
        {
        	memset(p,255,sizeof(p));
        	int js=0;
			for (int i=0;i<vec.size();i++)
			for (int j=63;j>=0;j--) if (vec[i]&(1ll<<j))
			{
				if (p[j]==-1) {p[j]=vec[i];js++;break;}
				else vec[i]^=p[j];
			}
			js=vec.size()-js;
			long long mx=0;
			for (int i=63;i>=0;i--) if (p[i]!=-1)
			{
				for (int j=i-1;j>=0;j--) if ((p[i]&(1ll<<j))&&(p[j]!=-1)) p[i]^=p[j];
				mx^=p[i];
			}
			long long sum=js*mx+mx;
			bool bo=false;
			for (int i=63;i>=0;i--) if (p[i]!=-1) {if (bo) sum+=mx^p[i];else bo=true;}
			return sum;
		
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long Arr0[] = {1,0}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 2LL; verify_case(0, Arg1, maxSum(Arg0)); }
	void test_case_1() { long Arr0[] = {1,2,3}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 8LL; verify_case(1, Arg1, maxSum(Arg0)); }
	void test_case_2() { long Arr0[] = {0,0,0,0,0,0,0,0,0,0}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(2, Arg1, maxSum(Arg0)); }
	void test_case_3() { long Arr0[] = {2,3,5,7,11,13,17,19}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 233LL; verify_case(3, Arg1, maxSum(Arg0)); }
	void test_case_4() { long Arr0[] = {123456789012345, 0, 0, 0, 0, 0, 0, 0, 0, 0}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 1234567890123450LL; verify_case(4, Arg1, maxSum(Arg0)); }
	void test_case_5() { long Arr0[] = {627,674,281,272,289,877,62,122,603,189,615}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 10742LL; verify_case(5, Arg1, maxSum(Arg0)); }
	void test_case_6() { long Arr0[] = {557}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 557LL; verify_case(6, Arg1, maxSum(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        XorAndSum ___test;
        ___test.run_test(1);
        return 0;
}
// END CUT HERE
