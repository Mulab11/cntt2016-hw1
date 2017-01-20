// BEGIN CUT HERE

// END CUT HERE
#line 5 "KnightCircuit2.cpp"
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
class KnightCircuit2
{
        public:
        int maxSize(int w,int h)
        {
			if (w>h) swap(w,h);
			if (w==1) return 1;
			if (w==2) return (h+1)/2;
			if ((w==h)&&(w==3)) return 8;
			return w*h;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; verify_case(0, Arg2, maxSize(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 15; int Arg1 = 2; int Arg2 = 8; verify_case(1, Arg2, maxSize(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 100; int Arg1 = 100; int Arg2 = 10000; verify_case(2, Arg2, maxSize(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        KnightCircuit2 ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
