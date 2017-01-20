// BEGIN CUT HERE

// END CUT HERE
//#line 5 "MagicalHats.cpp"
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
int x[15],y[15],js,n,lenx,leny,guess,mi[15];
int bx[15],by[15];
int f[5000010];
inline int getwei(int s,int w) {return (s/mi[w])%3;}
int getf(int s,int coin,int remain)
{
	if (f[s]<100000000) return f[s];
	if (!coin)
	{	
		for (int i=0;i<js;i++) if (getwei(s,i)==2) {bx[x[i]]^=1;by[y[i]]^=1;}
		bool pd=true;
		for (int i=0;i<lenx;i++) if (bx[i]) {pd=false;break;}
		for (int i=0;i<leny;i++) if (by[i]) {pd=false;break;}
		for (int i=0;i<js;i++) if (getwei(s,i)==2) {bx[x[i]]^=1;by[y[i]]^=1;}
		if (pd) return f[s]=0;else return f[s]=-100000000;
	}
	f[s]=-100000000;
	for (int i=0;i<js;i++) if (getwei(s,i)==0)
	{
		int p1=getf(s+mi[i],coin,remain-1),p2=getf(s+2*mi[i],coin-1,remain-1);
		if ((p1<0)&&(p2<0)) {f[s]=-100000000;break;}
		if (p1<0) f[s]=max(f[s],p2+(remain>0));
		else if (p2<0) f[s]=max(f[s],p1);
		else f[s]=max(f[s],min(p1,p2+(remain>0)));
	}
	//cout<<s<<' '<<coin<<' '<<remain<<"   "<<f[s]<<endl;
	return f[s];
}	
class MagicalHats
{
        public:
        int findMaximumReward(vector <string> board, vector <int> coin, int g)
        {
        	sort(coin.begin(),coin.end());
			n=coin.size();lenx=board.size();leny=board[0].size();guess=g;
			mi[0]=1;for (int i=1;i<=14;i++) mi[i]=mi[i-1]*3;
			for (int i=0;i<lenx;i++)
			for (int j=0;j<leny;j++)
				if (board[i][j]=='H')
				{
					x[js]=i;y[js]=j;
					js++;
					bx[i]^=1;by[j]^=1;
				}
			memset(f,127/3,sizeof(f));
			int p=getf(0,coin.size(),guess);
			if (p<0) return -1;
			int ans=0;
			for (int i=0;i<p;i++) ans+=coin[i];
			return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"H"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 1; verify_case(0, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"HHH",
 "H.H",
 "HH."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 9; verify_case(1, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"HH",
 "HH"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 6; verify_case(2, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"HHH",
 "HHH",
 "H.H"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {13,13,13,13}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 13; verify_case(3, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"HHH",
 "HHH",
 "H.H"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {13,13,13,13}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 26; verify_case(4, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arr0[] = {"H.H.",
 ".H.H",
 "H.H."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {17}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; int Arg3 = -1; verify_case(5, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
	void test_case_6() { string Arr0[] = {"HHH",
 "H.H",
 "HHH",
 "H.H",
 "HHH"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {33,337,1007,2403,5601,6003,9999}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; int Arg3 = 1377; verify_case(6, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
	void test_case_7() { string Arr0[] = {".............",
 ".............",
 ".............",
 ".............",
 ".............",
 ".............",
 ".....H.H.....",
 "......H......",
 ".....H.H.....",
 ".............",
 ".............",
 ".............",
 "............."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {22}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 22; verify_case(7, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        MagicalHats ___test;
        ___test.run_test(5);
        return 0;
}
// END CUT HERE
