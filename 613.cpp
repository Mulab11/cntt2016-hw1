// BEGIN CUT HERE

// END CUT HERE
#line 5 "KingdomAndCities.cpp"
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
#define LL long long
#define mo 1000000007ll
using namespace std;
int c[2555][2555];
long long f[55][2555];
long long calc2(long long a,long long b){return (a*b*a*b%mo+a*b*(c[a][2]+c[b][2])*2%mo)%mo;}
long long calc3(long long a,long long b,long long c){return a*b*c%mo*(a+b+c)*2%mo;}
class KingdomAndCities
{
        public:
        int howMany(int n, int m, int d)
        {
			if ((d<n-1)||(d>n*(n-1)/2)) return 0;
			c[0][0]=1;
			for (int i=1;i<=2500;i++)
			{
				c[i][0]=1;
				for (int j=1;j<=i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%mo;
			}
			
			for (int i=1;i<=n;i++)
			for (int j=0;j<=d;j++)
			{
				f[i][j]=c[i*(i-1)/2][j];
				for (int k=1;k<i;k++)
				for (int l=k-1;l<=min(k*(k-1)/2,j);l++)
					f[i][j]=(f[i][j]-(LL)c[i-1][k-1]*f[k][l]%mo*c[(i-k)*(i-k-1)/2][j-l]%mo+mo)%mo;
			}
			
			if (m==0) return f[n][d];
			if (m==1)
			{
				if ((n==1)||(d<2)) return 0;
				LL ans=(LL)c[n-1][2]*f[n-1][d-2]%mo;
				for (int i=1;i<=n-2;i++)
				for (int j=0;j<=d-2;j++)
					ans=(ans+(LL)i*(n-1-i)*c[n-2][i-1]%mo*f[i][j]%mo*f[n-1-i][d-2-j]%mo)%mo;
				return ans;
			}
			
			if ((n==2)||(d<3)) return 0;
			if (d==3) return (n==3)?1:((n==4)?2:0);
			long long ans=(LL)(n-2)*(n-2)%mo*f[n-2][d-3]%mo;
			for (int i=1;i<=n-2;i++)
			for (int k=0;k<=d-3;k++)
				ans=(ans+f[i][k]*f[n-2-i][d-3-k]%mo*i*(n-2-i)*2%mo*c[n-3][i-1]%mo)%mo;
			ans=(ans+f[n-2][d-4]*c[n-2][2]%mo*c[n-2][2]%mo)%mo;
			for (int i=1;i<n-2;i++)
			for (int k=0;k<=d-4;k++)
				ans=(ans+f[i][k]*f[n-2-i][d-4-k]%mo*calc2(i,n-2-i)%mo*c[n-3][i-1]%mo)%mo;
			for (int i1=1;i1<n-2;i1++)
			for (int k1=0;k1<=d-4;k1++)
			for (int i2=1;i1+i2<n-2;i2++)
			for (int k2=0;k1+k2<=d-4;k2++)
				ans=(ans+f[i1][k1]*f[i2][k2]%mo*f[n-2-i1-i2][d-4-k1-k2]%mo*calc3(i1,i2,n-2-i1-i2)%mo*c[n-3][i1-1]%mo*c[n-3-i1][i2-1]%mo)%mo;
			return ans;
			
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 0; int Arg2 = 3; int Arg3 = 1; verify_case(0, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 1; int Arg2 = 4; int Arg3 = 9; verify_case(1, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 2; int Arg2 = 11; int Arg3 = 0; verify_case(2, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 5; int Arg1 = 0; int Arg2 = 8; int Arg3 = 45; verify_case(3, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 10; int Arg1 = 2; int Arg2 = 20; int Arg3 = 150810825; verify_case(4, Arg3, howMany(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        KingdomAndCities ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
