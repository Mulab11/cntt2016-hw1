// BEGIN CUT HERE

// END CUT HERE
//#line 5 "WolfPack.cpp"
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
long long ls[500100],fac[251000],nifac[251000];
long long getmi(long long a,long long x)
{
	if (!x) return 1;
	long long ans=getmi(a,x>>1);
	ans=ans*ans%mo;
	if (x&1) ans=ans*a%mo;
	return ans;
}
long long C(int n,int m){return fac[n]*nifac[m]%mo*nifac[n-m]%mo;}
long long work(vector <int> vec,int t)
{
	long long* num=ls+250050;
	for (int i=-250000;i<=250000;i++) num[i]=1;
	int n=vec.size();
	for (int i=0;i<n;i++)
	{
		int x=vec[i];
		for (int i=-250000;i<=250000;i++)
		{
			if (((t^i^x)&1)||(i<x-t)||(i>x+t)) {num[i]=0;continue;}
			int dlt=abs(x-i);
			num[i]=num[i]*C(t,(t-dlt)/2)%mo;
		}
	}
	long long ans=0;
	for (int i=-250000;i<=250000;i++) ans=(ans+num[i])%mo;
	return ans;
}
class WolfPack
{
        public:
        int calc(vector <int> x, vector <int> y, int t)
        {
        	fac[0]=nifac[0]=1;
        	for (int i=1;i<=250000;i++)
        	{
        		fac[i]=fac[i-1]*i%mo;
        		nifac[i]=getmi(fac[i],mo-2);
			} 
			int n=x.size();
			for (int i=0;i<n;i++)
			{
				int px=x[i],py=y[i];
				x[i]=px+py;
				y[i]=px-py;
			}
			return work(x,t)*work(y,t)%mo;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {3,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 1; verify_case(0, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 0; verify_case(1, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {0,2,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 4; verify_case(2, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {7,8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8,7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 2; verify_case(3, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {-2,-2,-2,0,0,0,2,2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-2,0,2,-2,0,2,-2,0,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1000; int Arg3 = 387540818; verify_case(4, Arg3, calc(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        WolfPack ___test;
        ___test.run_test(1);
        return 0;
}
// END CUT HERE
