// BEGIN CUT HERE

// END CUT HERE
#line 5 "RockPaperScissors.cpp"
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
double f[55][55][55],g[55][55][55];
class RockPaperScissors
{
        public:
        double bestScore(vector <int> A, vector <int> B, vector <int> C)
        {
			int n=A.size();
			f[0][0][0]=1;
			for (int i=0;i<n;i++)
			for (int a=n;a>=0;a--)
			for (int b=n-a;b>=0;b--)
			for (int c=n-a-b;c>=0;c--)
			{
				if (a!=0) f[a][b][c]+=f[a-1][b][c]*A[i];
				if (b!=0) f[a][b][c]+=f[a][b-1][c]*B[i];
				if (c!=0) f[a][b][c]+=f[a][b][c-1]*C[i];
			}
			
			for(int a=n-1;a>=0;a--)
			for(int b=n-a-1;b>=0;b--)
			for(int c=n-a-b-1;c>=0;c--)
			if(f[a][b][c]>1e-8)
			{
				double d1=f[a+1][b][c]*(a+1),d2=f[a][b+1][c]*(b+1),d3=f[a][b][c+1]*(c+1);
				double ths=max(max(d1*3+d2,d2*3+d3),d3*3+d1);
				g[a][b][c]=(ths+d1*g[a+1][b][c]+d2*g[a][b+1][c]+d3*g[a][b][c+1])/(d1+d2+d3);
			}
			return g[0][0][0];
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {100, 100, 100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {100, 100, 100}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {100, 100, 100}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 3.999999999999999; verify_case(0, Arg3, bestScore(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {300}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 3.0; verify_case(1, Arg3, bestScore(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {300, 0,   0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,   300, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,   0,   300}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 6.333333333333332; verify_case(2, Arg3, bestScore(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {100,  0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {200, 100}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0,   200}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 3.7222222222222223; verify_case(3, Arg3, bestScore(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {150,300,300,300,300,300,300,300,300,300,300,300,300,300
,300,300,300,300,300,300,300,300,300,300,300,300,300,300
,300,300,300,300,300,300,300,300,300,300,300,300,300,300
,300,300,300,300,300,300,300,300}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {150,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
,0,0,0,0,0,0,0,0,0}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 149.00000000000003; verify_case(4, Arg3, bestScore(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        RockPaperScissors ___test;
        ___test.run_test(2);
        return 0;
}
// END CUT HERE