// BEGIN CUT HERE

// END CUT HERE
#line 5 "Incubator.cpp"
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
bool a[110][110];
int part[110];
bool used[110];
vector <int> des[110];
bool search(int s)
{
	for (int k=0;k<des[s].size();k++) if (!used[des[s][k]])
	{
		used[des[s][k]]=true;
		if ((!part[des[s][k]])||(search(part[des[s][k]]))) {part[s]=des[s][k];part[des[s][k]]=s;return true;}
	}
	return false;
}
class Incubator
{
        public:
        int maxMagicalGirls(vector <string> love)
        {
			int n=love.size();
			for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)
				if (love[i][j]=='Y') a[i+1][j+1]=true;
			for (int k=1;k<=n;k++)
			for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				a[i][j]=a[i][j]|(a[i][k]&a[k][j]);
			for (int i=1;i<=n;i++)
			for (int j=1;j<=n;j++)
				if (a[i][j]) des[i].push_back(j+n); 
			int ans=0;
			for (int i=1;i<=2*n;i++)
			{
				memset(used,false,sizeof(used));
				if ((!part[i])&&(search(i))) ans++;
			}
			return n-ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"NY","NN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, maxMagicalGirls(Arg0)); }
	void test_case_1() { string Arr0[] = {"NYN", "NNY", "NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, maxMagicalGirls(Arg0)); }
	void test_case_2() { string Arr0[] = {"NNYNN","NNYNN","NNNYY","NNNNN","NNNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, maxMagicalGirls(Arg0)); }
	void test_case_3() { string Arr0[] = {"NNNNN","NYNNN","NYNYN","YNYNN","NNNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(3, Arg1, maxMagicalGirls(Arg0)); }
	void test_case_4() { string Arr0[] = {"NNNNN","NNNNN","NNNNN","NNNNN","NNNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(4, Arg1, maxMagicalGirls(Arg0)); }
	void test_case_5() { string Arr0[] = {"NNYNNNNN","NNNYNNNN","NNNNYNNN","NNYNNNNN","NNNNNYYN","NNNYNNNY","NNNNNNNN","NNNNNNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(5, Arg1, maxMagicalGirls(Arg0)); }
	void test_case_6() { string Arr0[] = {"Y"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(6, Arg1, maxMagicalGirls(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        Incubator ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
