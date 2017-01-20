// BEGIN CUT HERE

// END CUT HERE
#line 5 "CuttingBitString.cpp"
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
int f[210];
bool check(string st)
{
	if (st[0]=='0') return false;
	long long ans=0;
	for (int i=0;i<st.length();i++) ans=ans*2+st[i]-'0';
	if (ans==1ll) return true;
	if (ans==5ll) return true;
	if (ans==25ll) return true;
	if (ans==125ll) return true;
	if (ans==625ll) return true;
	if (ans==3125ll) return true;
	if (ans==15625ll) return true;
	if (ans==78125ll) return true;
	if (ans==390625ll) return true;
	if (ans==1953125ll) return true;
	if (ans==9765625ll) return true;
	if (ans==48828125ll) return true;
	if (ans==244140625ll) return true;
	if (ans==1220703125ll) return true;
	if (ans==6103515625ll) return true;
	if (ans==30517578125ll) return true;
	if (ans==152587890625ll) return true;
	if (ans==762939453125ll) return true;
	if (ans==3814697265625ll) return true;
	if (ans==19073486328125ll) return true;
	if (ans==95367431640625ll) return true;
	if (ans==476837158203125ll) return true;
	if (ans==2384185791015625ll) return true;
	if (ans==11920928955078125ll) return true;
	return false;
}
class CuttingBitString
{
        public:
        int getmin(string st)
        {
        	memset(f,127/3,sizeof(f));
			for (int i=0;i<st.length();i++)
			{
				if (check(st.substr(0,i+1))) {f[i]=1;continue;}
				for (int j=0;j<i;j++) if (check(st.substr(j+1,i-(j+1)+1))) f[i]=min(f[i],f[j]+1);
			}
			if (f[st.length()-1]>233) return -1;else return f[st.length()-1];
				
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "101101101"; int Arg1 = 3; verify_case(0, Arg1, getmin(Arg0)); }
	void test_case_1() { string Arg0 = "1111101"; int Arg1 = 1; verify_case(1, Arg1, getmin(Arg0)); }
	void test_case_2() { string Arg0 = "00000"; int Arg1 = -1; verify_case(2, Arg1, getmin(Arg0)); }
	void test_case_3() { string Arg0 = "110011011"; int Arg1 = 3; verify_case(3, Arg1, getmin(Arg0)); }
	void test_case_4() { string Arg0 = "1000101011"; int Arg1 = -1; verify_case(4, Arg1, getmin(Arg0)); }
	void test_case_5() { string Arg0 = "111011100110101100101110111"; int Arg1 = 5; verify_case(5, Arg1, getmin(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        CuttingBitString ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
