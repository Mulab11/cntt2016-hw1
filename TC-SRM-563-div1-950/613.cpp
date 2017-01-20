// BEGIN CUT HERE

// END CUT HERE
#line 5 "CoinsGame.cpp"
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
#define left LEFT
#define right RIGHT
#define mo 1000000009ll
using namespace std;
int a[55][55],up[55][55],down[55][55],left[55][55],right[55][55],num[55][55];
long long ls[55][55],mi[5555];
map<long long,int> mp;
class CoinsGame
{
        public:
        int ways(vector <string> board)
        {
			int n=board.size(),m=board[0].size();
			for (int i=1;i<=n;i++) for (int j=1;j<=m;j++) a[i][j]=(board[i-1][j-1]=='.');
			
			for (int i=1;i<=m;i++) up[1][i]=down[n][i]=-1;
			for (int i=1;i<=n;i++) left[i][1]=right[i][m]=-1;
			
			for (int i=2;i<=n;i++)
			for (int j=1;j<=m;j++)
			if (a[i-1][j]) up[i][j]=i-1;else up[i][j]=i;
			
			for (int i=n-1;i>=1;i--)
			for (int j=1;j<=m;j++)
			if (a[i+1][j]) down[i][j]=i+1;else down[i][j]=i;
			
			for (int i=1;i<=n;i++)
			for (int j=2;j<=m;j++)
			if (a[i][j-1]) left[i][j]=j-1;else left[i][j]=j;
			
			for (int i=1;i<=n;i++)
			for (int j=m-1;j>=1;j--)
			if (a[i][j+1]) right[i][j]=j+1;else right[i][j]=j;
			
			for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
			if (a[i][j]) num[i][j]=1;
			
			for (int t=1;t<=n*m;t++)
			{
				mp.clear();
				for (int i=1;i<=n;i++)
				for (int j=1;j<=m;j++)
				if (a[i][j])
				{
					long long s=0;
					if (up[i][j]!=-1) s=s*2555+num[up[i][j]][j];else s=s*2555+2544;
					if (down[i][j]!=-1) s=s*2555+num[down[i][j]][j];else s=s*2555+2544;
					if (left[i][j]!=-1) s=s*2555+num[i][left[i][j]];else s=s*2555+2544;
					if (right[i][j]!=-1) s=s*2555+num[i][right[i][j]];else s=s*2555+2544;
					ls[i][j]=s;
					mp[s]=0;
				}
				int tp=0;
				for (map<long long,int>::iterator it=mp.begin();it!=mp.end();it++) it->second=++tp;
				for (int i=1;i<=n;i++)
				for (int j=1;j<=m;j++)
					if (a[i][j]) num[i][j]=mp[ls[i][j]];
			}
			
			mp.clear();int d=0;
			for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
			if (a[i][j]) {mp[num[i][j]]++;d++;}
			//cout<<d<<endl;
			
			mi[0]=1;for (int i=1;i<=5000;i++) mi[i]=mi[i-1]*2%mo;
			long long ans=mi[d]-1;
			for (map<long long,int>::iterator it=mp.begin();it!=mp.end();it++) ans-=mi[it->second]-1;
			return (ans%mo+mo)%mo;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {".."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, ways(Arg0)); }
	void test_case_1() { string Arr0[] = {"##.#",
 ".###",
 "###.",
 "#.##"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 11; verify_case(1, Arg1, ways(Arg0)); }
	void test_case_2() { string Arr0[] = {"####",
 "#..#",
 "#..#",
 "####"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, ways(Arg0)); }
	void test_case_3() { string Arr0[] = {"#.#.#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, ways(Arg0)); }
	void test_case_4() { string Arr0[] = {"........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 688856388; verify_case(4, Arg1, ways(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        CoinsGame ___test;
        ___test.run_test(2);
        return 0;
}
// END CUT HERE
