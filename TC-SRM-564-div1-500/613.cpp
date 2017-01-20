// BEGIN CUT HERE

// END CUT HERE
#line 5 "AlternateColors2.cpp"
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
class AlternateColors2
{
        public:
        long long countWays(int n, int k)
        {
			long long ans=0;
			//RGB
			if ((k%3==1)&&(k+2<=n))
			{
				int pile=n-(k+2);
				ans+=(long long)(pile+2)*(pile+1)/2;//getc(n+2,2); 
			}
			cout<<ans<<endl;
			//
			//RG or RB
			for (int i=0;i<=(k-1)/3;i++)//RGB 的个数 
			{
				if ((k+1-i*3)&1) continue;
				int pile=n-(k+1);
				ans+=(pile+1)*2;
			}
			cout<<ans<<endl;
			//
			//R
			ans++;//全是R 
			for (int i=n-k+1;i<n;i++)//R 的个数 
			{
				//for (int j=0;j<=n;j++)//RGB 的个数
				//{
				//	if (i+j*3>n) continue;
				//	if ((n-(i+j*3))&1) continue;
				//	if (n-(i+j*3)) ans+=2;else ans++;
				//}
				if (((n-i)%3==0)&&((n-i)/3%2==(n+i)%2)) ans++;
				//for (int j=(n+i)%2;j<=(n-i-1)/3;j+=2)//RGB 的个数
				//{
				//	ans+=2;
				//}
				if ((n-i-1)/3%2==(n+i)%2)
				{
					if ((n+i)%2<=(n-i)/3)
						ans+=(((n-i-1)/3-(n+i)%2)/2+1)*2;
				}
				else
				{
					if ((n+i)%2<=(n-i)/3-1)
						ans+=(((n-i-1)/3-1-(n+i)%2)/2+1)*2;
				}
			}
			return ans;
				 
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; long long Arg2 = 1LL; verify_case(0, Arg2, countWays(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 3; long long Arg2 = 3LL; verify_case(1, Arg2, countWays(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 6; int Arg1 = 4; long long Arg2 = 9LL; verify_case(2, Arg2, countWays(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 6; int Arg1 = 1; long long Arg2 = 21LL; verify_case(3, Arg2, countWays(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 1000; int Arg1 = 2; long long Arg2 = 1LL; verify_case(4, Arg2, countWays(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 100000; int Arg1 = 100000; long long Arg2 = 1666700000LL; verify_case(5, Arg2, countWays(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        AlternateColors2 ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
