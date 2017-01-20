// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheSquareRootDilemma.cpp"
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
long long st[210],num[210],top;
void getfac(int x)
{
	top=0;
	for (int i=2;i*i<=x;i++) if (x%i==0)
	{
		st[++top]=i;num[top]=0; 
		while (x%i==0)
		{
			num[top]+=2;
			x/=i;
		}
	}
	if (x!=1) {st[++top]=x;num[top]=2;}
}
int dfs(int now,long long ths,int lim1,int lim2,long long all)
{
	if (ths>lim1) return 0;
	if (now>top)
	{
		if (all/ths>lim2) return 0;
		return 1;
	}
	int ans=0;
	for (int i=0;i<=num[now];i++)
	{
		ans+=dfs(now+1,ths,lim1,lim2,all);
		ths*=st[now];
	}
	return ans;
}
class TheSquareRootDilemma
{
        public:
        int countPairs(int n, int m)
        {
			int ans=0;
			for (int i=1;(long long)i*i<=(long long)n*m;i++)
			{
				getfac(i);
				ans+=dfs(1,1,n,m,(long long)i*i);
			}
			return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; verify_case(0, Arg2, countPairs(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 10; int Arg1 = 1; int Arg2 = 3; verify_case(1, Arg2, countPairs(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 8; int Arg2 = 5; verify_case(2, Arg2, countPairs(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 100; int Arg1 = 100; int Arg2 = 310; verify_case(3, Arg2, countPairs(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        TheSquareRootDilemma ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
