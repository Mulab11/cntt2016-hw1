// BEGIN CUT HERE

// END CUT HERE
#line 5 "TreeUnion.cpp"
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
int fa1[2010],fa2[2010],top;
vector <int> des1[2010],des2[2010];
int dis1[2010][2010],dis2[2010][2010];
void dfs1(int lk,int s,int d,int pre=0)
{
	dis1[lk][d]++;
	for (int k=0;k<des1[s].size();k++) if (des1[s][k]!=pre) dfs1(lk,des1[s][k],d+1,s);
}
void dfs2(int lk,int s,int d,int pre=0)
{
	dis2[lk][d]++;
	for (int k=0;k<des2[s].size();k++) if (des2[s][k]!=pre) dfs2(lk,des2[s][k],d+1,s);
}
class TreeUnion
{
        public:
        double expectedCycles(vector <string> L, vector <string> R, int K)
        {
			string ls;
			ls.clear();
			for (int i=0;i<L.size();i++) ls+=L[i];
			ls+=" ";
			int p=0;top=1;
			for (int now=0;now<ls.size();now++)
			{
				if (ls[now]==' ') {fa1[++top]=p+1;p=0;}
				else p=p*10+ls[now]-'0';
			}
			ls.clear();
			for (int i=0;i<R.size();i++) ls+=R[i];
			ls+=" ";
			p=0;top=1;
			for (int now=0;now<ls.size();now++)
			{
				if (ls[now]==' ') {fa2[++top]=p+1;p=0;}
				else p=p*10+ls[now]-'0';
			}
			
			for (int i=2;i<=top;i++)
			{
				des1[fa1[i]].push_back(i);
				des1[i].push_back(fa1[i]);
				des2[fa2[i]].push_back(i);
				des2[i].push_back(fa2[i]);
			}
			for (int i=1;i<=top;i++)
			{
				dfs1(i,i,0);
				dfs2(i,i,0);
			}
			double ans=0;
			for (int i1=1;i1<=top;i1++)
			for (int i2=1;i2<=top;i2++)
			for (int d1=1;d1<=K-3;d1++)
			{
				int d2=K-2-d1;
				ans+=(double)dis1[i1][d1]*dis2[i2][d2];
			}
			return ans/top/(top-1)/2;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"0"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; double Arg3 = 1.0; verify_case(0, Arg3, expectedCycles(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"0 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; double Arg3 = 1.3333333333333333; verify_case(1, Arg3, expectedCycles(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"0 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; double Arg3 = 0.3333333333333333; verify_case(2, Arg3, expectedCycles(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"0 ", "1 1 1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0 1 0 ", "1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; double Arg3 = 4.0; verify_case(3, Arg3, expectedCycles(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"0 1 2 0 1 2 0 1 2 5 6 1", "0 11", " 4"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0 1 1 0 2 3 4 3 4 6 6", " 10 12 12"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; double Arg3 = 13.314285714285713; verify_case(4, Arg3, expectedCycles(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        TreeUnion ___test;
        ___test.run_test(2);
        return 0;
}
// END CUT HERE