// BEGIN CUT HERE

// END CUT HERE
#line 5 "Mountains.cpp"
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
#define mo 1000000009
using namespace std;
vector <int> h;
vector <string> vis;
map <pair<int,vector<int> >,int> mp;
int n,len;
int search(int now,vector <int> &vec)
{
	if (now<0) return 1;
	if (mp.count(make_pair(now,vec))) return mp[make_pair(now,vec)];
	vector <int> ls;
	int ans=0;
	for (int i=0;i<len;i++)
	{
		ls=vec;
		bool can=true;
		for (int j=0;j<len;j++)
		{
			int ths=max(0,h[now]-abs(j-i));
			if ((ths>ls[j])!=(vis[now][j]=='X')) {can=false;break;}
			ls[j]=max(ls[j],ths);
		}
		if (can) {ans+=search(now-1,ls);if (ans>=mo) ans-=mo;}
	}
	return mp[make_pair(now,vec)]=ans;
}
class Mountains
{
        public:
        int countPlacements(vector <int> h_, vector <string> vis_)
        {
			h=h_;vis=vis_;
			n=h.size();len=vis[0].size();
			vector <int> ls;for (int i=1;i<=len;i++) ls.push_back(0);
			mp.clear();
			return search(n-1,ls);
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2, 3, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"------",
 "XXXX--",
 "---XXX"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(0, Arg2, countPlacements(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {4, 3, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"XXXXX--------",
 "----------XXX",
 "----XXXXXXX--"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(1, Arg2, countPlacements(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {13, 2, 3, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"XXXXXXXXX",
 "-XXX-----",
 "----XXXXX",
 "-----XXX-"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 9; verify_case(2, Arg2, countPlacements(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {8, 2, 9, 3, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"X------",
 "-------",
 "------X",
 "-------",
 "XXXXXXX"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 98; verify_case(3, Arg2, countPlacements(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {20, 20, 20, 20, 20, 20, 45, 50, 49, 50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"-------------------",
 "-------------------",
 "-------------------",
 "-------------------",
 "-------------------",
 "-------------------",
 "-------------------",
 "------------XXXXXXX",
 "XXXXXXX------------",
 "XXXXXXXXXXXXXXXXXXX"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 973726691; verify_case(4, Arg2, countPlacements(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        Mountains ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
