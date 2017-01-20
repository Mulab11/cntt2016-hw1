// BEGIN CUT HERE

// END CUT HERE
//#line 5 "CharacterBoard.cpp"
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
#define mo 1000000009ll
using namespace std;
int st[2100000];
long long ans;
int top,n,m,w;
vector <string> mp;
long long getmi(long long a,long long x)
{
	if (!x) return 1;
	long long ans=getmi(a,x>>1);
	ans=ans*ans%mo;
	if (x&1) ans=ans*a%mo;
	return ans;
}
long long zuo(int l,int r)
{
	if (l>r) return 0;
	l-=n*m;r-=n*m;
	cout<<l<<' '<<r<<endl;
	return getmi(26,l)*(1-getmi(26,r-l+1)+mo)%mo*getmi(1-26+mo,mo-2)%mo;
}
map<int,int> ls;
long long zuo2(int l)
{
	ls.clear();
	for (int i=0;i<n;i++)
	for (int j=0;j<m;j++)
	{
		int ths=((long long)i*w+j)%l;
		if (!ls.count(ths)) ls[ths]=mp[i][j];
		else if (ls[ths]!=mp[i][j]) return 0;
	}
	return getmi(26,l-ls.size());
}
class CharacterBoard
{
        public:
        int countGenerators(vector <string> mmp, int W, int i0, int j0)
        {
        	mp=mmp;w=W;
			n=mp.size();m=mp[0].size();
			for (int dx=-n+1;dx<n;dx++)
			for (int dy=-m+1;dy<m;dy++)
			{
				long long p=abs((long long)dx*w+dy);
				for (long long i=1;i*i<=p;i++) if (p%i==0)
				{
					if (i<=w) st[++top]=i;
					if (p/i<=w) st[++top]=p/i;
				}
			}
			sort(st+1,st+top+1);
			//for (int i=1;i<=top;i++) cout<<st[i]<<endl;
			int lst=1;
			for (int i=1;i<=top;i++) if (st[i]!=st[i-1])
			{
				ans+=zuo(lst,st[i]-1);lst=st[i]+1;
				ans+=zuo2(st[i]);
			}
			if (lst<=w) ans+=zuo(lst,w);
			return ans%mo;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"dea",
 "abc"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; int Arg2 = 1; int Arg3 = 1; int Arg4 = 1; verify_case(0, Arg4, countGenerators(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { string Arr0[] = {"xyxxy"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 1; int Arg3 = 0; int Arg4 = 28; verify_case(1, Arg4, countGenerators(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { string Arr0[] = {"gogogo",
 "jijiji",
 "rarara"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 0; int Arg3 = 0; int Arg4 = 0; verify_case(2, Arg4, countGenerators(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { string Arr0[] = {"abababacac",
 "aaacacacbb",
 "ccabababab"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8827; int Arg2 = 104; int Arg3 = 6022; int Arg4 = 829146844; verify_case(3, Arg4, countGenerators(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        CharacterBoard ___test;
        ___test.run_test(3);
        return 0;
}
// END CUT HERE