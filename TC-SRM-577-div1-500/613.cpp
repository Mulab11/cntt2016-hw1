// BEGIN CUT HERE

// END CUT HERE
#line 5 "EllysChessboard.cpp"
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
pair<int,int> st[210];
int top,n,m;
unsigned long long used;
map<unsigned long long,int> mp;
int dfs(int now)
{
	if (now>=top) return 0;
	if (mp.count(used)) return mp[used];
	int mx=0,p1,p2;
	for (int i=1;i<=top;i++) if (!(used&(1ll<<i)))
	for (int j=i+1;j<=top;j++) if ((!(used&(1ll<<j)))&&(abs(st[i].first-st[j].first)+abs(st[i].second-st[j].second)>mx))
	{
		mx=abs(st[i].first-st[j].first)+abs(st[i].second-st[j].second);
		p1=i;p2=j;
	}
	used+=(1ll<<p1);
	int ans=mx+dfs(now+1);
	used-=(1ll<<p1);
	used+=(1ll<<p2);
	ans=min(ans,mx+dfs(now+1));
	used-=(1ll<<p2);
	return mp[used]=ans;
}
class EllysChessboard
{
        public:
        int minCost(vector <string> board)
        {
			n=board.size();m=board[0].size();
			for (int i=0;i<n;i++)
			for (int j=0;j<m;j++) if (board[i][j]=='#')
			{
				st[++top]=make_pair(i,j);
			}
			return dfs(1); 
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"........",
 "........",
 "...#....",
 ".#......",
 ".......#",
 "........",
 "........",
 "........"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(0, Arg1, minCost(Arg0)); }
	void test_case_1() { string Arr0[] = {"........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, minCost(Arg0)); }
	void test_case_2() { string Arr0[] = {".#......",
 "........",
 "..#..#.#",
 "...#..#.",
 "........",
 "...#...#",
 "...#...#",
 "........"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 58; verify_case(2, Arg1, minCost(Arg0)); }
	void test_case_3() { string Arr0[] = {"##..####",
 "#####..#",
 "..#.#...",
 "#..##.##",
 ".#.###.#",
 "####.###",
 "#.#...#.",
 "##....#."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 275; verify_case(3, Arg1, minCost(Arg0)); }
	void test_case_4() { string Arr0[] = {"########",
 "########",
 "########",
 "########",
 "########",
 "########",
 "########",
 "########"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 476; verify_case(4, Arg1, minCost(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        EllysChessboard ___test;
        ___test.run_test(0);
        return 0;
}
// END CUT HERE