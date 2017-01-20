// BEGIN CUT HERE

// END CUT HERE
#line 5 "DrawingPointsDivOne.cpp"
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
int sum[300][300];
bool bo[300][300];
class DrawingPointsDivOne
{
        public:
        int maxSteps(vector <int> x, vector <int> y)
        {
			for (int i=0;i<x.size();i++) {x[i]+=71;y[i]+=71;}
			for (int d=1;d<=140;d++)
			{
				memset(sum,0,sizeof(sum));
				memset(bo,false,sizeof(bo));
				for (int i=0;i<x.size();i++)
				{
					bo[x[i]][y[i]]=true;
					sum[x[i]][y[i]]++;
					sum[x[i]+d+1][y[i]+d+1]++;
					sum[x[i]][y[i]+d+1]--;
					sum[x[i]+d+1][y[i]]--;
				}
				for (int i=1;i<=290;i++)
				for (int j=1;j<=290;j++)
					sum[i][j]=sum[i][j]+sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1];
				for (int i=1;i<=290;i++)
				for (int j=1;j<=290;j++)
					if (sum[i][j]) sum[i][j]=1;
				for (int i=1;i<=290;i++)
				for (int j=1;j<=290;j++)
					sum[i][j]=sum[i][j]+sum[i][j-1]+sum[i-1][j]-sum[i-1][j-1];
				for (int i=1;i<=145;i++)
				for (int j=1;j<=145;j++)
				if ((!bo[i][j])&&(sum[i+d][j+d]+sum[i-1][j-1]-sum[i+d][j-1]-sum[i-1][j+d]==(d+1)*(d+1))) return d-1;
				
			}
			return -1; 
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(0, Arg2, maxSteps(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {0,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, maxSteps(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {-70}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(2, Arg2, maxSteps(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {-41,-40,1,-11,-32,-7,24,-11,49,-15,-22,20,-8,54,54,69,16,-30,36,-6,-30,40,64,20,-66,
 -37,-33,-18,-35,36,9,61,-43,45,5,60,-8,-58,65,-66,41,12,34,-11,-57,-38,46,63,-55,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,-24,-2,-4,23,14,1,70,-26,45,15,48,32,-41,54,-47,-67,-46,-9,-53,54,28,-61,11,53,68,
 -33,62,37,-8,-17,-17,48,19,-49,56,-41,16,17,-50,28,59,10,50,23,-16,56,31,-70,-44}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 9; verify_case(3, Arg2, maxSteps(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        DrawingPointsDivOne ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
