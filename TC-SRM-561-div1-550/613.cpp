// BEGIN CUT HERE

// END CUT HERE
//#line 5 "CirclesGame.cpp"
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
int x[55],y[55],r[55];
bool inside(int c,int d)
{
	//return (x[c]+r[c]<x[d]+r[d])&&(x[c]-r[c]>x[d]-r[d])&&(y[c]+r[c]<y[d]+r[d])&&(y[c]-r[c]>y[d]-r[d]);
	if (r[c]>=r[d]) return false;
	return (x[c]-x[d])*(x[c]-x[d])+(y[c]-y[d])*(y[c]-y[d])<(r[c]-r[d])*(r[c]-r[d]);
}
int fa[55],sg[55];
vector <int> des[55],son[55];
bool bo[55];
void getsg(int s)
{
	son[s].push_back(s);
	for (int k=0;k<des[s].size();k++)
	{
		getsg(des[s][k]);
		for (int d=0;d<son[des[s][k]].size();d++) son[s].push_back(son[des[s][k]][d]);
	}
	vector <int> ls;
	for (int k=0;k<son[s].size();k++)
	{
		int d=son[s][k];
		while (d!=s) {bo[d]=true;d=fa[d];}bo[d]=true;
		int p=0;
		for (int kk=0;kk<son[s].size();kk++) if ((!bo[son[s][kk]])&&(bo[fa[son[s][kk]]])) p^=sg[son[s][kk]];
		ls.push_back(p);
		d=son[s][k];
		while (d!=s) {bo[d]=false;d=fa[d];}bo[d]=false;
	}
	sort(ls.begin(),ls.end());
	if (ls[0]!=0) {sg[s]=0;return;}
	for (int i=1;i<ls.size();i++) if (ls[i]-ls[i-1]>1) {sg[s]=ls[i]-1;return;}
	sg[s]=ls[ls.size()-1]+1;
}
class CirclesGame
{
        public:
        string whoCanWin(vector <int> x_, vector <int> y_, vector <int> r_)
        {
			int n=r_.size();
			for (int i=1;i<=n;i++) {x[i]=x_[i-1];y[i]=y_[i-1];r[i]=r_[i-1];} 
			for (int i=1;i<=n;i++)
			{
				int minn=2100000000,id=0;
				for (int j=1;j<=n;j++) if ((inside(i,j))&&(minn>r[j])) {minn=r[j];id=j;}
				if (id) {fa[i]=id;des[id].push_back(i);}
			}
			int ans=0;
			for (int i=1;i<=n;i++) if (!fa[i]) {getsg(i);ans^=sg[i];}
			if (ans) return "Alice";else return "Bob";
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "Alice"; verify_case(0, Arg3, whoCanWin(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "Bob"; verify_case(1, Arg3, whoCanWin(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {0, 0, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "Alice"; verify_case(2, Arg3, whoCanWin(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {0, 0, 0, 10, 10, 20}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 0, 0, 0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 3, 1, 2, 1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "Bob"; verify_case(3, Arg3, whoCanWin(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {10,20,30,40,50,60,70,80}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8,7,6,5,4,3,2,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,2,2,2,2,2,2,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "Bob"; verify_case(4, Arg3, whoCanWin(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {0, 3, 6, 9, 12, -4747, -4777}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-5858, -5858, -5858, -5858, -5858, 777, 777}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {58, 1, 1, 1, 1, 44, 8}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "Bob"; verify_case(5, Arg3, whoCanWin(Arg0, Arg1, Arg2)); }
	void test_case_6() { int Arr0[] = {5202, 5699, -7433, 5068, -9483, -684, -6593, 5108, -7813, 6823, 3267, -8222, -8547, 2878, 2413, 8557, 5149, 5073, -8638, -6108, 8097}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8728, -7407, 4338, -8414, 7652, -3705, -984, 5976, -9180, -9119, 9301, 2398, 7915, 6205, 7665, 717, -9884, 11, -8579, -6903, -746}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {4196, 9303, 7152, 5875, 2943, 788, 502, 416, 1958, 3174, 182, 1256, 1147, 444, 979, 65, 1040, 1233, 438, 175, 1140}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arg3 = "Alice"; verify_case(6, Arg3, whoCanWin(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        CirclesGame ___test;
        ___test.run_test(3);
        return 0;
}
// END CUT HERE
