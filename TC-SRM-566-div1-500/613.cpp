// BEGIN CUT HERE

// END CUT HERE
#line 5 "PenguinEmperor.cpp"
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
#define mo 1000000007ll
using namespace std;
long long ls[430],a[430],b[430],x[430];
int n;
void times(long long a[],long long b[],long long c[])
{
	memset(ls,0,sizeof(ls));
	for (int i=0;i<n;i++)
	for (int j=0;j<n;j++)
	{
		ls[(i+j)%n]=(ls[(i+j)%n]+a[i]*b[j])%mo;
	}
	memcpy(c,ls,sizeof(ls));	
} 
class PenguinEmperor
{
        public:
        int countJourneys(int n_, long long t)
        {
        	n=n_;
			a[0]=b[0]=1;
			for (int i=1;i<=n;i++)
			{
				memset(x,0,sizeof(x));
				x[i%n]++;if (i%n!=n-i) x[n-i]++;
				times(a,x,a);
				//for(int j=0;j<n;j++)printf("%lld ",a[j]);printf("\n");	
				if (i==t%n) memcpy(b,a,sizeof(b));
			}
			t/=n;
			for (;t;t>>=1)
			{
				if (t&1) times(b,a,b);
				times(a,a,a);
			}
			return b[0];
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; long long Arg1 = 2LL; int Arg2 = 2; verify_case(0, Arg2, countJourneys(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 4; long long Arg1 = 3LL; int Arg2 = 2; verify_case(1, Arg2, countJourneys(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 5; long long Arg1 = 36LL; int Arg2 = 107374182; verify_case(2, Arg2, countJourneys(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 300; long long Arg1 = 751LL; int Arg2 = 413521250; verify_case(3, Arg2, countJourneys(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 300; long long Arg1 = 750LL; int Arg2 = 0; verify_case(4, Arg2, countJourneys(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 350; long long Arg1 = 1000000000000000000LL; int Arg2 = 667009739; verify_case(5, Arg2, countJourneys(Arg0, Arg1)); }
	void test_case_6() { int Arg0 = 5; long long Arg1 = 7LL; int Arg2 = 12; verify_case(6, Arg2, countJourneys(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        PenguinEmperor ___test;
        ___test.run_test(0);
        return 0;
}
// END CUT HERE
