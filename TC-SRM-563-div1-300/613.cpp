// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndHandle.cpp"
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
int need[160];
class FoxAndHandle
{
        public:
        string lexSmallestName(string st)
        {
			for (int i=0;i<st.length();i++) need[st[i]]++;
			int len=0;for (int i='a';i<='z';i++) {need[i]>>=1;len+=need[i];}
			int bg=0;string ans;
			for (int i=1;i<=len;i++)
			for (char j='a';j<='z';j++) if (need[j])
			{
				int p=bg;
				while (st[p]!=j) p++;
				bool chk=true;
				need[j]--;
				for (char k='a';k<='z';k++) 
				{
					int js=0;
					for (int l=p+1;l<st.length();l++) if (st[l]==k) js++;
					if (js<need[k]) {chk=false;break;}
				}
				if (chk)
				{
					bg=p+1;
					ans+=j;//cout<<j<<endl<<bg<<endl;
					break;
				}
				else need[j]++;
			}
			return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "foxfox"; string Arg1 = "fox"; verify_case(0, Arg1, lexSmallestName(Arg0)); }
	void test_case_1() { string Arg0 = "ccieliel"; string Arg1 = "ceil"; verify_case(1, Arg1, lexSmallestName(Arg0)); }
	void test_case_2() { string Arg0 = "abaabbab"; string Arg1 = "aabb"; verify_case(2, Arg1, lexSmallestName(Arg0)); }
	void test_case_3() { string Arg0 = "bbbbaaaa"; string Arg1 = "bbaa"; verify_case(3, Arg1, lexSmallestName(Arg0)); }
	void test_case_4() { string Arg0 = "fedcbafedcba"; string Arg1 = "afedcb"; verify_case(4, Arg1, lexSmallestName(Arg0)); }
	void test_case_5() { string Arg0 = "nodevillivedon"; string Arg1 = "deilvon"; verify_case(5, Arg1, lexSmallestName(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        FoxAndHandle ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
