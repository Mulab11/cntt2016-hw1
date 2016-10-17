// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheDivisionGame.cpp"
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
bool pend(int s)
{
	for (int i=2;i*i<=s;i++) if (s%i==0) return false;
	return true;
}
int num[40],ths[1000100],fac[1000100];
class TheDivisionGame
{
        public:
        long long countWinningIntervals(int l, int r)
        {
			memset(fac,0,sizeof(fac));
			for (int i=0;i<=r-l;i++) ths[i]=i+l;
			for (int i=2;i<=35000;i++) if (pend(i))
			for (int j=(l-1)/i*i+i;;j+=i)
			{if (j<l) assert(0);
				if (j>r) break;
				while (ths[j-l]%i==0)
				{
					fac[j-l]++;
					ths[j-l]/=i;
				}
			}
			for (int i=0;i<=r-l;i++) if (ths[i]!=1) fac[i]++;
			memset(num,0,sizeof(num));
			long long ans=0;num[0]=1;int sg=0;
			for (int i=l;i<=r;i++)
			{
				sg^=fac[i-l];//cout<<sg<<endl;
				ans+=num[sg];
				num[sg]++;
			}//exit(0);cout<<ans<<endl;
			return (long long)(r-l+1)*(r-l+2)/2-ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 9; int Arg1 = 10; long long Arg2 = 2LL; verify_case(0, Arg2, countWinningIntervals(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 5; long long Arg2 = 9LL; verify_case(1, Arg2, countWinningIntervals(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 6; long long Arg2 = 13LL; verify_case(2, Arg2, countWinningIntervals(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 2; int Arg1 = 100; long long Arg2 = 4345LL; verify_case(3, Arg2, countWinningIntervals(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 12566125; int Arg1 = 12567777; long long Arg2 = 1313432LL; verify_case(4, Arg2, countWinningIntervals(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        TheDivisionGame ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
