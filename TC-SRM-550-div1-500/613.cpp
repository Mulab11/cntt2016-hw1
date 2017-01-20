// BEGIN CUT HERE

// END CUT HERE
//#line 5 "CheckerExpansion.cpp"
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
bool inside(long long x,long long y,long long t)
{
	if ((x<=0)||(y<=0)) return 0;
	if (x<y) return 0;
	if (x>=2*t) return 0;
	if (y>t) return 0;
	if ((x>=t)&&(y>2*t-x)) return 0;
	return true;
}
int get(long long x,long long y)
{
	if ((x==1)&&(y==1)) return 1;
	if ((x==2)&&(y==1)) return 0;
	if ((x==2)&&(y==2)) return 2;
	if ((x==3)&&(y==1)) return 2;
	long long now=2;
	while (!inside(x,y,now)) now<<=1;
	long long half=now>>1;
	if (inside(x-now,y,half)) return get(x-now,y);
	if (inside(x-half,y-half,half)) return get(x-half,y-half);
	return 0;
}

vector <string> vec;
class CheckerExpansion
{
        public:
        vector <string> resultAfter(long long t, long long x0, long long y0, int w, int h)
        {
        
			/*for (int i=1;i<=16;i++)
        	for (int j=1;j<=16;j++)
        	{
        		if ((i>=j)&&(get(i,j))) cout<<get(i,j);else cout<<' ';
        		if (j==16) cout<<endl;
        	} */       
 		       
        
        	vec.resize(h);
        	for (int i=0;i<h;i++) vec[i].resize(w);
        	x0++;y0++;
        	for (long long i=x0;i<x0+w;i++)
        	for (long long j=y0;j<y0+h;j++)
        	{
        		int d=0;
				if (inside(i,j,t)) d=get(i,j);
        		if (d==0) vec[(h-1)-(j-y0)][i-x0]='.';
        		else if (d==1) vec[(h-1)-(j-y0)][i-x0]='A';
        		else vec[(h-1)-(j-y0)][i-x0]='B';
        	}
        	/*for (int i=1;i<=16;i++)
        	for (int j=1;j<=16;j++)
        	{
        		cout<<i<<' '<<j<<"    "<<get(i,j)<<endl;
        	}*/
        	
			return vec;	
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { long long Arg0 = 1LL; long long Arg1 = 0LL; long long Arg2 = 0LL; int Arg3 = 4; int Arg4 = 4; string Arr5[] = {"....", "....", "....", "A..." }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(0, Arg5, resultAfter(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { long long Arg0 = 5LL; long long Arg1 = 4LL; long long Arg2 = 1LL; int Arg3 = 3; int Arg4 = 4; string Arr5[] = {"A..", "...", "B..", ".B." }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(1, Arg5, resultAfter(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { long long Arg0 = 1024LL; long long Arg1 = 1525LL; long long Arg2 = 512LL; int Arg3 = 20; int Arg4 = 2; string Arr5[] = {"B...B...B...........", ".B.A.B.A.B.........." }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(2, Arg5, resultAfter(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { long long Arg0 = 53LL; long long Arg1 = 85LL; long long Arg2 = 6LL; int Arg3 = 5; int Arg4 = 14; string Arr5[] = {".....", ".....", "B....", ".B.A.", ".....", ".....", ".....", ".....", ".....", ".....", "B....", ".B...", "..B..", ".A.B." }; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); verify_case(3, Arg5, resultAfter(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        CheckerExpansion ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
