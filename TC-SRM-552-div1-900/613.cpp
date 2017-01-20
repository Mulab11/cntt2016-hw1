// BEGIN CUT HERE

// END CUT HERE
#line 5 "HolyNumbers.cpp"
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
long long pr[400010],prnum,js;
bool bo[1000100];
//map<long long,long long> mp;
void init(int n)
{
	memset(bo,true,sizeof(bo));
	for (int i=2;i<=n;i++)
	{
		if (bo[i]) pr[++prnum]=i;
		for (int j=1;j<=prnum;j++)
		{
			if (i*pr[j]>n) break;
			bo[i*pr[j]]=false;
			if (i%pr[j]==0) break;
		}
	}
}
long long calc(long long n,int fst)
{
	if (fst>prnum) return 0;
	if (n<pr[fst]) return 0;
	if (pr[fst]*pr[fst]>=n) return upper_bound(pr+fst,pr+prnum+1,n)-(pr+fst);
	//if (mp.count((n<<20)+fst)) {js++;return mp[(n<<20)+fst];}
	long long ans=calc(n,fst+1),now=pr[fst];
	while (now<=n)
	{
		ans+=calc(n/now,fst+1)+1;
		now=now*pr[fst]*pr[fst];
	}
	return /*mp[(n<<20)+fst]=*/ans;
}
class HolyNumbers
{
        public:
        long long count(long long n, int p)
        {
        	p=min((long long)p,n);
			init(p);
			long long ans=calc(n,1)+1;
			//cout<<mp.size()<<' '<<js<<endl;
			return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 10000000000ll; int Arg1 = 1000000; long long Arg2 = 3336332555ll; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 10LL; int Arg1 = 3; long long Arg2 = 5LL; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 123LL; int Arg1 = 12; long long Arg2 = 32LL; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 123LL; int Arg1 = 456; long long Arg2 = 88LL; verify_case(3, Arg2, count(Arg0, Arg1)); }
	void test_case_4() { long long Arg0 = 123456789LL; int Arg1 = 12345; long long Arg2 = 25994500LL; verify_case(4, Arg2, count(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        HolyNumbers ___test;
        ___test.run_test(0);
        return 0;
}
// END CUT HERE
