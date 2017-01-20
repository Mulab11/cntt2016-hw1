// BEGIN CUT HERE

// END CUT HERE
#line 5 "Stamp.cpp"
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
#include <cassert>
using namespace std;
int f[55];
bool pend[55][55];
bool check(string st)
{
	int r=0,g=0,b=0;
	for (int i=0;i<st.length();i++)
		if (st[i]=='R') r=1;
		else if (st[i]=='G') g=1;
		else if (st[i]=='B') b=1;
	return r+g+b<=1;
}
class Stamp
{
        public:
        int getMinimumCost(string col,int stamp,int push)
        {
        	for (int i=0;i<col.length();i++)
        	for (int j=i;j<col.length();j++) pend[i][j]=check(col.substr(i,j-i+1));
			int ans=stamp+push*col.length();
			for (int len=2;len<=col.length();len++)
			{
				memset(f,127/6,sizeof(f));
				for (int i=len-1;i<col.length();i++)
				{//if (i==0) assert(0);
					if (pend[0][i]) f[i]=min(f[i],i/len+1);
					for (int j=1;j<=i-len+1;j++) if (pend[j][i]) f[i]=min(f[i],f[j-1]+(i-j)/len+1);
				}
				if (f[col.length()-1]<100000000) ans=min(ans,stamp*len+push*f[col.length()-1]);
				//cout<<len<<' '<<ans<<endl;
				//cout<<len<<' '<<f[10]<<endl;
			}
			return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "RRGGBB"; int Arg1 = 1; int Arg2 = 1; int Arg3 = 5; verify_case(0, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "R**GB*"; int Arg1 = 1; int Arg2 = 1; int Arg3 = 5; verify_case(1, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "BRRB"; int Arg1 = 2; int Arg2 = 7; int Arg3 = 30; verify_case(2, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "R*RR*GG"; int Arg1 = 10; int Arg2 = 58; int Arg3 = 204; verify_case(3, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arg0 = "*B**B**B*BB*G*BBB**B**B*"; int Arg1 = 5; int Arg2 = 2; int Arg3 = 33; verify_case(4, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arg0 = "*R*RG*G*GR*RGG*G*GGR***RR*GG"; int Arg1 = 7; int Arg2 = 1; int Arg3 = 30; verify_case(5, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        Stamp ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
