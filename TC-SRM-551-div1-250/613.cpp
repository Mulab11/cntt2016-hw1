// BEGIN CUT HERE

// END CUT HERE
#line 5 "ColorfulChocolates.cpp"
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
int stk[200010],top;
class ColorfulChocolates
{
        public:
        int maximumSpread(string st,int mx)
        {
        	int ans=0;
			for (char ch='A';ch<='Z';ch++)
			{
				top=0;
				for (int i=0;i<st.length();i++) if (st[i]==ch) stk[++top]=i;
				if (!top) continue;
				stk[0]=-100000000;stk[top+1]=100000000;
				for (int i=1;i<=top;i++)
				{
					int l=i-1,r=i+1,rem=mx;
					while (rem>=min(stk[i]-stk[l]-(i-l),stk[r]-stk[i]-(r-i)))
					{
						if (stk[i]-stk[l]-(i-l)<stk[r]-stk[i]-(r-i)) {rem-=stk[i]-stk[l]-(i-l);l--;}
						else {rem-=stk[r]-stk[i]-(r-i);r++;}
					}
					ans=max(ans,r-l-1);
				}
			}
			return ans;	
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "ABCDCBC"; int Arg1 = 1; int Arg2 = 2; verify_case(0, Arg2, maximumSpread(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "ABCDCBC"; int Arg1 = 2; int Arg2 = 3; verify_case(1, Arg2, maximumSpread(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "ABBABABBA"; int Arg1 = 3; int Arg2 = 4; verify_case(2, Arg2, maximumSpread(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "ABBABABBA"; int Arg1 = 4; int Arg2 = 5; verify_case(3, Arg2, maximumSpread(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "QASOKZNHWNFODOQNHGQKGLIHTPJUVGKLHFZTGPDCEKSJYIWFOO"; int Arg1 = 77; int Arg2 = 5; verify_case(4, Arg2, maximumSpread(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        ColorfulChocolates ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
