// BEGIN CUT HERE

// END CUT HERE
#line 5 "LittleElephantAndBoard.cpp"
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
long long fac[1000100],nifac[1000100],mi2[1000100];
long long getmi(long long a,long long x)
{
	if (!x) return 1;
	long long ans=getmi(a,x>>1);
	ans=ans*ans%mo;
	if (x&1) ans=ans*a%mo;
	return ans;
}
long long C(int n,int m)
{
	if ((n<=0)||(m<=0)) return 0;
	if (n<m) return 0;
	return fac[n]*nifac[m]%mo*nifac[n-m]%mo;
}
long long work(int r,int g,int b)
{
	int n=r+g+b;
	if ((r>(n+1)/2)||(g>(n+1)/2)||(b>(n+1)/2)) return 0;
	if (n==1) return 1;
	if (n==2) return 2;
	long long ans=0;
	for (int rr=-1;rr<=1;rr++)
	{
		int row=b+rr; if (row<=0) continue;
		for (int x0=0;x0<=row;x0++)
		{
			if (((row-x0+r-g)&1)||((row-x0+g-r)&1)) continue;
			int x1=(row-x0+r-g)/2,x_1=(row-x0+g-r)/2;//if (x0+x1+x_1!=row) assert(0);
			if ((x1<0)||(x_1<0)) continue;
			long long p=fac[row]*nifac[x0]%mo*nifac[x1]%mo*nifac[x_1]%mo;
			p=p*mi2[x0]%mo;
			p=p*C(row-1+r-x0-x1,row-1)%mo;
			ans=(ans+p+p*(rr==0))%mo;
		}
	}
	return ans;
}
class LittleElephantAndBoard
{
        public:
        int getNumber(int m, int r, int g, int b)
        {
			fac[0]=nifac[0]=1;
			for (int i=1;i<=1000000;i++) {fac[i]=fac[i-1]*i%mo;nifac[i]=getmi(fac[i],mo-2);}
			mi2[0]=1;for (int i=1;i<=1000000;i++) mi2[i]=mi2[i-1]*2%mo;
			if ((r>m)||(g>m)||(b>m)) return 0;
			return work(m-r,m-g,m-b)*2%mo;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 1; int Arg3 = 1; int Arg4 = 4; verify_case(0, Arg4, getNumber(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; int Arg3 = 0; int Arg4 = 0; verify_case(1, Arg4, getNumber(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 7; int Arg2 = 7; int Arg3 = 6; int Arg4 = 496; verify_case(2, Arg4, getNumber(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 474; int Arg1 = 250; int Arg2 = 300; int Arg3 = 398; int Arg4 = 969878317; verify_case(3, Arg4, getNumber(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        LittleElephantAndBoard ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
