// BEGIN CUT HERE

// END CUT HERE
//#line 5 "MagicMolecule.cpp"
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
long long bo[55],used;
int n,lim,num[55],sum,allans,js[55],err;
#define check(x) (((used|bo[x])&((1ll<<(x+1))-1))==used)
void search(int now,int lim,int ans)
{
	err++;if (err>100000000) return;
	if (now>=n) {allans=min(allans,ans);return;}
	if (ans>=allans) return;
	if ((lim)&&(js[now]!=0))
	{
		long long p=used;used|=(1ll<<now);
		search(now+1,lim-1,ans+num[now]);
		used=p;
	}
	if (check(now)) search(now+1,lim,ans);
}
int rd[55];
class MagicMolecule
{
        public:
        int maxMagicPower(vector <int> dd, vector <string> mp)
        {
			n=dd.size();
			for (int i=0;i<n;i++) rd[i]=i;
			for (int i=1;i<=500;i++) swap(rd[rand()%n],rd[rand()%n]);
			for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)
				if ((mp[i][j]=='N')&&(i!=j)) {js[rd[i]]++;bo[rd[i]]+=(1ll<<rd[j]);}
			for (int i=0;i<n;i++) {num[rd[i]]=dd[i];sum+=dd[i];}
			allans=sum+1;search(0,n/3,0);
			return sum-allans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NYY","YNN","YNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(0, Arg2, maxMagicPower(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNYY","NNYY","YYNN","YYNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(1, Arg2, maxMagicPower(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {86,15,100,93,53,50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NYYYYN","YNNNNY","YNNYYN","YNYNYN","YNYYNY","NYNNYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 332; verify_case(2, Arg2, maxMagicPower(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {3969,9430,7242,8549,8190,8368,3704,9740,1691}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NYYYYYYYY","YNYYYYYYY","YYNYYYYYY","YYYNYYYYY","YYYYNYYYY","YYYYYNYYY","YYYYYYNNY","YYYYYYNNY","YYYYYYYYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 57179; verify_case(3, Arg2, maxMagicPower(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        MagicMolecule ___test;
        ___test.run_test(3);
        return 0;
}
// END CUT HERE
