// BEGIN CUT HERE

// END CUT HERE
#line 5 "TwoConvexShapes.cpp"
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
long long ans;
int a[55][55],n,m;
long long f[55][55];
bool bo[55][55];
void zuo()
{
	for (int i=0;i<=m;i++) f[0][i]=1;
	for (int i=1;i<=n;i++)
	for (int j=0;j<=m;j++)
	{
		if (!j) f[i][j]=0;else f[i][j]=f[i][j-1];
		if (bo[i][j]) f[i][j]=(f[i][j]+f[i-1][j])%mo;
	}
	ans+=f[n][m];
}
		
void work()
{
	for (int i=1;i<=n;i++)
	for (int j=0;j<=m;j++)
	{	
		bo[i][j]=true;
		for (int k=1;k<=j;k++) if (a[i][k]==-1) {bo[i][j]=false;break;}
		for (int k=j+1;k<=m;k++) if (a[i][k]==1) {bo[i][j]=false;break;}
	}
	zuo();
	for (int i=1;i<=n/2;i++)
	for (int j=0;j<=m;j++)
		swap(bo[i][j],bo[n-i+1][j]);
	zuo();
	for (int i=1;i<=n/2;i++)
	for (int j=0;j<=m;j++)
		swap(bo[i][j],bo[n-i+1][j]);
	for (int j=0;j<=n;j++)
	{
		for (int i=1;i<=j;i++) if (!bo[i][m]) goto bomb1;
		for (int i=j+1;i<=n;i++) if (!bo[i][0]) goto bomb1;
		ans--;
		bomb1:;
	}
	for (int j=0;j<=m;j++)
	{
		for (int i=1;i<=n;i++) if (!bo[i][j]) goto bomb2;
		ans--;
		bomb2:;
	}
	ans++;
	for (int i=1;i<=n;i++)
	for (int j=1;j<=m;j++)
		if (a[i][j]==-1) {ans--;goto bomb3;}
	bomb3:;	
}
	
class TwoConvexShapes
{
        public:
        int countWays(vector <string> board)
        {
			n=board.size();m=board[0].size();
			for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
			{
				if (board[i-1][j-1]=='?') a[i][j]=0;
				else if (board[i-1][j-1]=='W') a[i][j]=-1;
				else a[i][j]=1;
			}
			work();
			for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				a[i][j]*=-1;
			work();
			return (ans+mo)%mo;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"??",
 "??"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 14; verify_case(0, Arg1, countWays(Arg0)); }
	void test_case_1() { string Arr0[] = {"B?",
 "??"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(1, Arg1, countWays(Arg0)); }
	void test_case_2() { string Arr0[] = {"WWB",
 "WWW",
 "WWW",
 "WWW"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, countWays(Arg0)); }
	void test_case_3() { string Arr0[] = {"BBBBBB",
 "WWBBBB",
 "WBBBBB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, countWays(Arg0)); }
	void test_case_4() { string Arr0[] = {"?BB?",
 "BBBB",
 "?BB?"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(4, Arg1, countWays(Arg0)); }
	void test_case_5() { string Arr0[] = {"?WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
 "B?WWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
 "BB?WWWWWWWWWWWWWWWWWWWWWWWWWWWW",
 "BBB?WWWWWWWWWWWWWWWWWWWWWWWWWWW",
 "BBBB?WWWWWWWWWWWWWWWWWWWWWWWWWW",
 "BBBBB?WWWWWWWWWWWWWWWWWWWWWWWWW",
 "BBBBBB?WWWWWWWWWWWWWWWWWWWWWWWW",
 "BBBBBBB?WWWWWWWWWWWWWWWWWWWWWWW",
 "BBBBBBBB?WWWWWWWWWWWWWWWWWWWWWW",
 "BBBBBBBBB?WWWWWWWWWWWWWWWWWWWWW",
 "BBBBBBBBBB?WWWWWWWWWWWWWWWWWWWW",
 "BBBBBBBBBBB?WWWWWWWWWWWWWWWWWWW",
 "BBBBBBBBBBBB?WWWWWWWWWWWWWWWWWW",
 "BBBBBBBBBBBBB?WWWWWWWWWWWWWWWWW",
 "BBBBBBBBBBBBBB?WWWWWWWWWWWWWWWW",
 "BBBBBBBBBBBBBBB?WWWWWWWWWWWWWWW",
 "BBBBBBBBBBBBBBBB?WWWWWWWWWWWWWW",
 "BBBBBBBBBBBBBBBBB?WWWWWWWWWWWWW",
 "BBBBBBBBBBBBBBBBBB?WWWWWWWWWWWW",
 "BBBBBBBBBBBBBBBBBBB?WWWWWWWWWWW",
 "BBBBBBBBBBBBBBBBBBBB?WWWWWWWWWW",
 "BBBBBBBBBBBBBBBBBBBBB?WWWWWWWWW",
 "BBBBBBBBBBBBBBBBBBBBBB?WWWWWWWW",
 "BBBBBBBBBBBBBBBBBBBBBBB?WWWWWWW",
 "BBBBBBBBBBBBBBBBBBBBBBBB?WWWWWW",
 "BBBBBBBBBBBBBBBBBBBBBBBBB?WWWWW",
 "BBBBBBBBBBBBBBBBBBBBBBBBBB?WWWW",
 "BBBBBBBBBBBBBBBBBBBBBBBBBBB?WWW",
 "BBBBBBBBBBBBBBBBBBBBBBBBBBBB?WW",
 "BBBBBBBBBBBBBBBBBBBBBBBBBBBBB?W"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 73741817; verify_case(5, Arg1, countWays(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        TwoConvexShapes ___test;
        ___test.run_test(5);
        return 0;
}
// END CUT HERE
