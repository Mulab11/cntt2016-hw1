// BEGIN CUT HERE

// END CUT HERE
//#line 5 "MapGuessing.cpp"
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
#include <cassert>
using namespace std;
int st[40][40],bit[1050000],n,top;
char emp[40];
long long ans,must[40];
//int bitcount(long long s){return bit[s>>20]+bit[s&((1<<20)-1)];}
void search(int now,int js,long long m)
{
	if (now>top) return;
	search(now+1,js,m);
	m|=must[now];
	int ls=n-bit[m>>20]-bit[m&1048575];
	if ((js+1)&1) {ans+=(1ll<<ls);ans--;}else {ans-=(1ll<<ls);ans++;}
	
	if (ls) search(now+1,js+1,m);
}
bool check(string goal,int top)
{
	for (int i=0;i<n;i++) if (st[top][i]!=-1)
	{
		if (goal[i]-'0'!=st[top][i]) return false;
	}
	return true;
}
class MapGuessing
{
        public:
        long long countPatterns(string goal, vector <string> cd)
        {
        	for (int i=1;i<(1<<20);i++) bit[i]=bit[i-(i&(-i))]+1;
        	memset(st,255,sizeof(st));
			n=goal.size();
			string code;
			for (int i=0;i<cd.size();i++) code+=cd[i];
			bool can=false;
			for (int bg=0;bg<n;bg++)
			{
				int now=bg;int tim=-1;
				top++;memset(st[top],255,sizeof(st[top]));
				for (int i=0;i<code.size();i++)
				{
					if (code[i]=='<') now--;
					if (code[i]=='>') now++;
					if ((now==-1)||(now==n)) {tim=-2;break;}
					if (code[i]=='1') st[top][now]=1;
					if (code[i]=='0') st[top][now]=0;
					if (check(goal,top)) tim=i;
				}
				if (tim==-2) {top--;continue;}
				can=true;
				memset(st[top],255,sizeof(st[top]));
				now=bg;
				for (int i=0;i<=tim;i++)
				{
					if (code[i]=='<') now--;
					if (code[i]=='>') now++;
					if (code[i]=='1') st[top][now]=1;
					if (code[i]=='0') st[top][now]=0;
				}
				for (int i=0;i<n;i++) if (st[top][i]==-1) must[top]+=(1ll<<i);
			}
			cout<<top<<endl;
			if (!can) return 0;
			ans=1;
			search(1,0,0ll);
			return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "000000000000000000000000000000000000"; string Arr1[] = {"<<<<<<<>>>>0>>>"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 30LL; verify_case(0, Arg2, countPatterns(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "001"; string Arr1[] = {"0>1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 5LL; verify_case(1, Arg2, countPatterns(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "000"; string Arr1[] = {"1>1>1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1LL; verify_case(2, Arg2, countPatterns(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "11001"; string Arr1[] = {">><<<<><<"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(3, Arg2, countPatterns(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "1000101011"; string Arr1[] = {"1<<0>>0>1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 22LL; verify_case(4, Arg2, countPatterns(Arg0, Arg1)); }
	void test_case_5() { string Arg0 = "00000010000000000000000000000000"; string Arr1[] = {"><>>0<0<>>1>0><>", "<<0>>0<>><0>0>>><><", ">>>0<>", ">0><>>>>0<<><>>0>>>0<0>>0>"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 13601LL; verify_case(5, Arg2, countPatterns(Arg0, Arg1)); }
	void test_case_6() { string Arg0 = "11100011010111111010100100110001101"; string Arr1[] = {"11111111111111111111"
,"1<><><><><><><><><>1"
,"1<>000>000><0<><0<>1"
,"1<0<><>0><0<00>00<>1"
,"1<>00<>000><0<0<0<>1"
,"1<><>0>0><0<0<><0<>1"
,"1<000<>0><0<0<><0<>1"
,"1<><><><><><><><><>1"
,"1<>000><000<>000><>1"
,"1<>0><><0<><>0><><>1"
,"1<>000><000<>000><>1"
,"1<><>0><><0<><>0><>1"
,"1<>000><000<>000><>1"
,"1<><><><><><><><><>1"
,"11111111111111111111"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 90LL; verify_case(6, Arg2, countPatterns(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        MapGuessing ___test;
        ___test.run_test(5);
        return 0;
}
// END CUT HERE
