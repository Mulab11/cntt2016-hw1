// BEGIN CUT HERE

// END CUT HERE
//#line 5 "NextAndPrev.cpp"
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
#define next asuidhusd
using namespace std;
int go[33],tp[333],ans,next,pre,l[333],r[333];
bool vis[33];
void zuo(int bg)
{
	int mx=-1,ths=0;
	for (int i=bg;i<bg+26;i++) if (tp[i]!=-1)
	{//cout<<tp[i]<<endl;
		if (tp[i]<mx) return;
		mx=tp[i];
	}
	for (int i=2*26;i<3*26;i++) l[i]=r[i]=i;
	for (int i=bg;i<bg+26;i++) if (tp[i]!=-1)
	{
		l[tp[i]]=min(l[tp[i]],i);
		r[tp[i]]=max(r[tp[i]],i);
	}
	for (int i=2*26;i<3*26;i++) ths+=next*(i-l[i])+pre*(r[i]-i);
	ans=min(ans,ths);
}
class NextAndPrev
{
    public:
        int getMinimum(int C,int D,string s,string t)
		{
			next=C;pre=D;ans=2100000000;
			if(s==t) return 0;
			memset(go,255,sizeof(go));
			memset(tp,255,sizeof(tp));
			for (int i=0;i<s.size();i++)
			{
				if ((go[s[i]-'a']!=-1)&&(go[s[i]-'a']!=t[i]-'a')) return -1;
				go[s[i]-'a']=t[i]-'a';
				vis[t[i]-'a']=true;
			}
			bool bo=true;
			for (int i=0;i<26;i++) if (!vis[i]) bo=false;
			if (bo) return -1;
			for (int i=0;i<26;i++) if (go[i]!=-1)
			for (int j=0;j<=4;j++) tp[i+26*j]=go[i]+26*2;
			for (int i=0;i<4*26;i++) zuo(i);
			return (ans!=2100000000)?ans:-1;
		}
        
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); if ((Case == -1) || (Case == 8)) test_case_8(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 8; string Arg2 = "aeaae"; string Arg3 = "bcbbc"; int Arg4 = 21; verify_case(0, Arg4, getMinimum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 5; int Arg1 = 8; string Arg2 = "aeaae"; string Arg3 = "bccbc"; int Arg4 = -1; verify_case(1, Arg4, getMinimum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 1; string Arg2 = "srm"; string Arg3 = "srm"; int Arg4 = 0; verify_case(2, Arg4, getMinimum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 1000; int Arg1 = 39; string Arg2 = "a"; string Arg3 = "b"; int Arg4 = 975; verify_case(3, Arg4, getMinimum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arg0 = 123; int Arg1 = 456; string Arg2 = "pqrs"; string Arg3 = "abab"; int Arg4 = -1; verify_case(4, Arg4, getMinimum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arg0 = 100; int Arg1 = 19; string Arg2 = "topcoder"; string Arg3 = "ssszsffs"; int Arg4 = 676; verify_case(5, Arg4, getMinimum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_6() { int Arg0 = 1; int Arg1 = 100000; string Arg2 = "c```````````sk"; string Arg3 = "wog"; int Arg4 = 64; verify_case(6, Arg4, getMinimum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_7() { int Arg0 = 7; int Arg1 = 6; string Arg2 = "qwerty"; string Arg3 = "jjjjjj"; int Arg4 = 125; verify_case(7, Arg4, getMinimum(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_8() { int Arg0 = 306; int Arg1 = 26; string Arg2 = "me"; string Arg3 = "ii"; int Arg4 = 572; verify_case(8, Arg4, getMinimum(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        NextAndPrev ___test;
        ___test.run_test(3);
        return 0;
}
// END CUT HERE
