// BEGIN CUT HERE

// END CUT HERE
#line 5 "EqualSums.cpp"
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
#define mo 1000000007
using namespace std;
int num[110],a[110][110],n;
bool vis[110];
vector <int> des[110],len[110];
int dfs(int s,int d)
{
	vis[s]=true;
	if ((num[s]!=-1)&&(num[s]!=d)) return -1;
	if (d<0) return -1;
	if (num[s]==d) return 2100000000;
	num[s]=d;
	int minn=2100000000;
	if (s<=n) minn=d;
	for (int k=0;k<des[s].size();k++) minn=min(minn,dfs(des[s][k],len[s][k]-d));
	return minn;
}
class EqualSums
{
        public:
        int count(vector <string> board)
        {
			n=board.size();
			for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)
			{
				if (board[i][j]=='-') a[i+1][j+1]=-1;else a[i+1][j+1]=board[i][j]-'0';
				if (a[i+1][j+1]>=0)
				{
					des[i+1].push_back(n+j+1);
					len[i+1].push_back(a[i+1][j+1]);
					des[n+j+1].push_back(i+1);
					len[n+j+1].push_back(a[i+1][j+1]);
				}	
			}
			long long ans0=1,ans1=1;
			for (int i=1;i<=2*n;i++) if (!vis[i])
			{
				int p0=0,p1=0;
				for (int j=0;j<=9;j++)
				{
					memset(num,-1,sizeof(num));
					int d=dfs(i,j);
					if (d==-1) continue;
					p1++;if (d!=0) p0++;
				}
				ans1=ans1*p1%mo;
				ans0=ans0*p0%mo;
			}
			return (ans1-ans0+mo)%mo;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1-",
 "-2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, count(Arg0)); }
	void test_case_1() { string Arr0[] = {"123",
 "4--",
 "--9"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, count(Arg0)); }
	void test_case_2() { string Arr0[] = {"9--",
 "-9-",
 "--9"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 271; verify_case(2, Arg1, count(Arg0)); }
	void test_case_3() { string Arr0[] = {"11",
 "12"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, count(Arg0)); }
	void test_case_4() { string Arr0[] = {"-4--",
 "-0-2",
 "--1-",
 "4---"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(4, Arg1, count(Arg0)); }
	void test_case_5() { string Arr0[] = {"--2",
 "02-",
 "-10"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(5, Arg1, count(Arg0)); }
	void test_case_6() { string Arr0[] = {"----------1---------------0-----7-----------------",
 "-----4--------------------------------------------",
 "--------5-------------5-3---5---------------6-----",
 "-------2----------1-------------------------------",
 "-----4--------------------------------------------",
 "-----3--------------------------------------------",
 "-6----------5-------------------------------------",
 "-------------------------------7---5----------6---",
 "--------6-------------6-4---6---------------7-----",
 "-------------4----------------5-------------------",
 "3------------------------------------------6------",
 "3------------------------------------------6------",
 "-------------4----------------5-------------------",
 "---------------2-------------------------3--------",
 "--2------------------------------------------2----",
 "---8---------------1-------------------3----------",
 "---------------3----------------------------------",
 "----7----------------5---0-----------------------5",
 "----------------5-------------------------3-----1-",
 "----------1---------------0-----7-----------------",
 "-------------5----------------6-------------------",
 "-7----------6-------------------------------------",
 "---8---------------1-------------------3----------",
 "-----------------------3--------------------------",
 "----8----------------6---1-----------------------6",
 "------------------------------------------4-----2-",
 "-----------5---------------5----------------------",
 "-----------------------------6--------------------",
 "----8----------------6---1-----------------------6",
 "----------------5-------------------------3-----1-",
 "-------------------------------6---4--2-------5---",
 "-6----------5-------------------------------------",
 "--------5-------------5-3---5---------------6-----",
 "-------------5----------------6-------------------",
 "-----3--------------------------------------------",
 "---------------2-------------------------3--------",
 "---------4---------------------------6------------",
 "-------------------------------6---4--2-------5---",
 "------2-------------1------------22---------------",
 "--------5-------------5-3---5---------------6-----",
 "-----------5--3------------5----------------------",
 "--2------------------------------------------2----",
 "---------5---------------------------7------------",
 "-------------4----------------5-------------------",
 "-----------------5------------------4---6------2--",
 "-------------------------------6---4--2-------5---",
 "-----------------------2--------------------------",
 "----------------6-------------------------4-----2-", 
 "-------------------------------6---4--2-------5---",
 "--------5-------------5-3---5---------------6-----"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 45094393; verify_case(6, Arg1, count(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        EqualSums ___test;
        ___test.run_test(0);
        return 0;
}
// END CUT HERE
