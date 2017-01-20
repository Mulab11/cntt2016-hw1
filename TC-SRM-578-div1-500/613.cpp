// BEGIN CUT HERE

// END CUT HERE
#line 5 "WolfInZooDivOne.cpp"
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
#define mo 1000000007
using namespace std;
int l[2010],r[2010],top;
int up[2010][2010],f[2010][2010];
class WolfInZooDivOne
{
        public:
        int count(int n, vector <string> L, vector <string> R)
        {
			string ls;
			ls.clear();
			for (int i=0;i<L.size();i++) ls+=L[i];
			ls+=" ";
			int p=0;top=0;
			for (int now=0;now<ls.size();now++)
			{
				if (ls[now]==' ') {l[++top]=p+1;p=0;}
				else p=p*10+ls[now]-'0';
			}
			ls.clear();
			for (int i=0;i<R.size();i++) ls+=R[i];
			ls+=" ";
			p=0;top=0;
			for (int now=0;now<ls.size();now++)
			{
				if (ls[now]==' ') {r[++top]=p+1;p=0;}
				else p=p*10+ls[now]-'0';
			}
			
			for (int i=0;i<=n;i++)
			for (int j=i;j<=n;j++)
			{
				int mx=j+1;
				for (int k=1;k<=top;k++)
					if ((l[k]<=i)&&(r[k]>=j)) mx=max(mx,r[k]+1);
				up[i][j]=mx;
			}
			int ans=0;
			f[0][0]=1;
			for (int i=0;i<=n;i++)
			for (int j=i;j<=n;j++)
			{
				ans=(ans+f[i][j])%mo;
				for (int k=up[i][j];k<=n;k++) f[j][k]=(f[j][k]+f[i][j])%mo;
			}
			return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; string Arr1[] = {"0"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"4"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 16; verify_case(0, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 5; string Arr1[] = {"0 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"2 4"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 21; verify_case(1, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 10; string Arr1[] = {"0 4 2 7"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"3 9 5 9"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 225; verify_case(2, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 100; string Arr1[] = {"0 2 2 7 10 1","3 16 22 30 33 38"," 42 44 49 51 57 60 62"," 65 69 72 74 77 7","8 81 84 88 91 93 96"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"41 5 13 22 12 13 ","33 41 80 47 40 ","4","8 96 57 66 ","80 60 71 79"," 70 77 ","99"," 83 85 93 88 89 97 97 98"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 6419882; verify_case(3, Arg3, count(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        WolfInZooDivOne ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE