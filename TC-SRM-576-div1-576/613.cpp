// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheExperiment.cpp"
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
#define mo 1000000009ll
using namespace std;
int sum[1010];
long long f[1010][1010][3];
int getsum(int l,int r){return sum[r]-sum[l-1];}
class TheExperiment
{
        public:
        int countPlacements(vector <string> ls, int n, int len, int l, int r)
        {
        	string st;for (int i=0;i<ls.size();i++) st+=ls[i];
        	int alllen=st.size();
			for (int i=0;i<alllen;i++)
			{
				sum[i+1]=sum[i]+st[i]-'0';
				//cout<<sum[i+1]<<endl;
			}
			f[0][0][0]=1;
			for (int i=1;i<=alllen;i++)
			for (int j=0;j<=n;j++)
			{
				f[i][j][0]=(f[i-1][j][0]+f[i-1][j][1])%mo;
				if ((i-len>=0)&&(getsum(i-len+1,i)>=l)&&(getsum(i-len+1,i)<=r))
					f[i][j][1]=(f[i-len][j-1][0]+f[i-len][j-1][1]+f[i-len][j-1][2])%mo;
				for (int k=1;k<=min(len-1,i);k++)
				{
					if ((getsum(i-k+1,i)>=l)&&(getsum(i-k+1,i)<=r))
					{
						f[i][j][2]=(f[i][j][2]+f[i-k][j-1][2]+f[i-k][j-1][0])%mo;
						f[i][j][1]=(f[i][j][1]+f[i-k][j-1][1])%mo;
					}
				}
			}
			return (f[alllen][n][0]+f[alllen][n][1])%mo;
		}	
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"341156"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 3; int Arg3 = 6; int Arg4 = 10; int Arg5 = 2; verify_case(0, Arg5, countPlacements(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { string Arr0[] = {"999112999"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 4; int Arg3 = 21; int Arg4 = 30; int Arg5 = 2; verify_case(1, Arg5, countPlacements(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { string Arr0[] = {"111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 2; int Arg3 = 2; int Arg4 = 3; int Arg5 = 0; verify_case(2, Arg5, countPlacements(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { string Arr0[] = {"59059", "110", "1132230231"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 5; int Arg3 = 10; int Arg4 = 20; int Arg5 = 6; verify_case(3, Arg5, countPlacements(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { string Arr0[] = {"111111111111111111111111", "111111111111111111111111111", "11111111111111111111111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; int Arg2 = 8; int Arg3 = 4; int Arg4 = 2700; int Arg5 = 418629948; verify_case(4, Arg5, countPlacements(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        TheExperiment ___test;
        ___test.run_test(4);
        return 0;
}
// END CUT HERE