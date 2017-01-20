// BEGIN CUT HERE

// END CUT HERE
#line 5 "YetAnotherBoardGame.cpp"
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
int n,m,a[15][15],ans;
int chk1[15],chk2[15];
void dfs(int s1,int s2,int p,int now=0)
{
	if (now>=ans) return;
	if (s1==n+1)
	{
		for (int i=1;i<=m;i++) if (a[n][i]!=0) return;
		ans=now;
		return;
	}
	if (s1==1)
	{
		if (s2!=m) dfs(s1,s2+1,p,now);else {dfs(s1+1,1,1,now);dfs(s1+1,1,2,now);}
	}
	else if (a[s1-1][s2]==0)
	{
		if (s2!=m) dfs(s1,s2+1,p,now);else {dfs(s1+1,1,1,now);dfs(s1+1,1,2,now);}
		return;
	}
	
	if ((p==1)&&(chk2[s2])) return;
	if ((p==2)&&(chk1[s2])) return;
	if (p==1)
	{
		a[s1-1][s2]^=1;
		if (s2!=1) a[s1][s2-1]^=1;
		if (s2!=m) a[s1][s2+1]^=1;
		if (s1!=n) a[s1+1][s2]^=1;
		chk1[s2]++;
		if (s2!=m) dfs(s1,s2+1,p,now+1);else {dfs(s1+1,1,1,now+1);dfs(s1+1,1,2,now+1);}
		a[s1-1][s2]^=1;
		if (s2!=1) a[s1][s2-1]^=1;
		if (s2!=m) a[s1][s2+1]^=1;
		if (s1!=n) a[s1+1][s2]^=1;
		chk1[s2]--;
	}
	else
	{
		a[s1-1][s2]^=1;
		if (s2!=1) a[s1][s2-1]^=1;
		if (s2!=m) a[s1][s2+1]^=1;
		if (s1!=n) a[s1+1][s2]^=1;
		a[s1][s2]^=1;
		chk2[s2]++;
		if (s2!=m) dfs(s1,s2+1,p,now+1);else {dfs(s1+1,1,1,now+1);dfs(s1+1,1,2,now+1);}
		a[s1-1][s2]^=1;
		if (s2!=1) a[s1][s2-1]^=1;
		if (s2!=m) a[s1][s2+1]^=1;
		if (s1!=n) a[s1+1][s2]^=1;
		a[s1][s2]^=1;
		chk2[s2]--;
	}
}
		
	
class YetAnotherBoardGame
{
        public:
        int minimumMoves(vector <string> vec)
        {
			n=vec.size();m=vec[0].size();
			for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
				a[i][j]=(vec[i-1][j-1]=='W');
			for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
			{
				cout<<a[i][j]<<' ';
				if (j==m) cout<<endl;
			}
			ans=2100000000;
			dfs(1,1,1);
			dfs(1,1,2);
			return (ans!=2100000000)?ans:-1;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"BBBBBBBBB",
 "BBWBBBBBB",
 "BWWWBBBBB",
 "BBWBBBWBB",
 "BBBBBWBWB",
 "BBBBBBWBB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, minimumMoves(Arg0)); }
	void test_case_1() { string Arr0[] = {"BBW",
 "WWW",
 "BWW"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, minimumMoves(Arg0)); }
	void test_case_2() { string Arr0[] = {"WBW",
 "BBW",
 "WBW"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(2, Arg1, minimumMoves(Arg0)); }
	void test_case_3() { string Arr0[] = {"BBBB",
 "WBWB",
 "BBBB",
 "BBBB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(3, Arg1, minimumMoves(Arg0)); }
	void test_case_4() { string Arr0[] = {"WWWWWBW",
 "WBWBWBW",
 "BBWBBWW"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(4, Arg1, minimumMoves(Arg0)); }
	void test_case_5() { string Arr0[] = {"WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 30; verify_case(5, Arg1, minimumMoves(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        YetAnotherBoardGame ___test;
        ___test.run_test(2);
        return 0;
}
// END CUT HERE