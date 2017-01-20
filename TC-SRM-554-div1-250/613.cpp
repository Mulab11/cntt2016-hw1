// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheBrickTowerEasyDivOne.cpp"
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
class TheBrickTowerEasyDivOne
{
        public:
        int find(int num1, int h1, int num2, int h2)
        {
        	if (!num1) return num2;
        	if (!num2) return num1;
        	if (h1>h2) {swap(h1,h2);swap(num1,num2);} 
        	
			/*if (h2%h1==0)
			{
				h2/=h1;h1=1;
				if (num1%h2==0)
				{
					num2+=num1%h2-1;
					num1=h2;
				}
				else
				{
					num2+=num1%h2;
					num1%=h2;
				}
				if (num1<h2) return (num1+1)*(num2+1);
				else if (num1==h2) return num1*(num2+1)+1;
				return -1;
			}
			else */ 
			if (h1!=h2)
			{
				int ths=min(num1,num2);
				if (num1==num2) return 3*ths;
				else return 3*ths+1;
			}
			else return min(num1,num2)*2+(num1!=num2);
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 2; int Arg2 = 3; int Arg3 = 4; int Arg4 = 4; verify_case(0, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 4; int Arg2 = 4; int Arg3 = 7; int Arg4 = 12; verify_case(1, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 7; int Arg1 = 7; int Arg2 = 4; int Arg3 = 4; int Arg4 = 13; verify_case(2, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 47; int Arg1 = 47; int Arg2 = 47; int Arg3 = 47; int Arg4 = 94; verify_case(3, Arg4, find(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        TheBrickTowerEasyDivOne ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
