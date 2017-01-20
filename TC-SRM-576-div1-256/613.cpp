// BEGIN CUT HERE

// END CUT HERE
#line 5 "ArcadeManao.cpp"
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
struct node
{
	int d1,d2,len;
	friend bool operator <(node a,node b){return a.len<b.len;}
}dt[20010];
int top;
int fa[20010];
int getf(int s)
{	
	if (fa[s]==s) return s;
	return fa[s]=getf(fa[s]);
}
void merge(int x,int y)
{	
	x=getf(x);y=getf(y);
	fa[x]=y;
}
class ArcadeManao
{
        public:
        int shortestLadder(vector <string> a, int p1, int p2)
        {
        	p1--;p2--;
			int n=a.size(),m=a[0].size();
			for (int i=0;i<n*m;i++) fa[i]=i;
			for (int i=0;i<n;i++)
			for (int j=0;j<m-1;j++)
			{
				if ((a[i][j]=='X')&&(a[i][j+1]=='X')) merge(i*m+j,i*m+j+1);
			}
			for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
			{
				if (a[i][j]!='X') continue;
				int d;
				for (d=i-1;d>=0;d--) if (a[d][j]=='X') break;
				if (d==-1) continue;
				dt[++top]=(node){i*m+j,d*m+j,i-d};
			}
			sort(dt+1,dt+top+1);
			for (int i=1;i<=top+1;i++)
			{	
				if (getf((n-1)*m+0)==getf(p1*m+p2)) return dt[i-1].len;
				merge(dt[i].d1,dt[i].d2);
			}
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"XXXX....",
 "...X.XXX",
 "XXX..X..",
 "......X.",
 "XXXXXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 4; int Arg3 = 2; verify_case(0, Arg3, shortestLadder(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"XXXX",
 "...X",
 "XXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; verify_case(1, Arg3, shortestLadder(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"..X..",
 ".X.X.",
 "X...X",
 ".X.X.",
 "..X..",
 "XXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 3; int Arg3 = 4; verify_case(2, Arg3, shortestLadder(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"X"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 0; verify_case(3, Arg3, shortestLadder(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"XXXXXXXXXX",
 "...X......",
 "XXX.......",
 "X.....XXXX",
 "..XXXXX..X",
 ".........X",
 ".........X",
 "XXXXXXXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 2; verify_case(4, Arg3, shortestLadder(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        ArcadeManao ___test;
        ___test.run_test(0);
        return 0;
}
// END CUT HERE