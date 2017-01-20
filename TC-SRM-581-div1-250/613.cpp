// BEGIN CUT HERE

// END CUT HERE
#line 5 "SurveillanceSystem.cpp"
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
int js[210],sum[210][210],bo[210],ls[210];
class SurveillanceSystem
{
        public:
        string getContainerInfo(string st, vector <int> rep, int l)
        {
			for (int i=0;i<rep.size();i++) js[rep[i]]++;
			for (int i=0;i<st.length();i++)
			for (int j=i;j<st.length();j++)
				if (i==j) sum[i][j]=(st[i]=='X');else sum[i][j]=(st[j]=='X')+sum[i][j-1];
			for (int i=0;i<=l;i++) if (js[i])
			{
				int p=0;
				memset(ls,0,sizeof(ls));
				for (int j=0;j<=st.length()-l;j++) if (sum[j][j+l-1]==i) {p++;for (int k=j;k<j+l;k++) ls[k]++;}
				//for (int j=0;j<st.length();j++) cout<<ls[j]<<' ';
				//cout<<endl<<endl;
				for (int j=0;j<st.length();j++)
				{
					if (ls[j]>=p-js[i]+1) bo[j]=max(bo[j],2);
					else if (ls[j]) bo[j]=max(bo[j],1);
				}
			}
			string s;
			for (int i=0;i<st.length();i++) if (bo[i]==2) s=s+"+";else if (bo[i]==0) s=s+"-";else s=s+"?";
			return s;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "-X--XX"; int Arr1[] = {1, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; string Arg3 = "??++++"; verify_case(0, Arg3, getContainerInfo(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "-XXXXX-"; int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; string Arg3 = "???-???"; verify_case(1, Arg3, getContainerInfo(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "------X-XX-"; int Arr1[] = {3, 0, 2, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; string Arg3 = "++++++++++?"; verify_case(2, Arg3, getContainerInfo(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "-XXXXX---X--"; int Arr1[] = {2, 1, 0, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; string Arg3 = "???-??++++??"; verify_case(3, Arg3, getContainerInfo(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arg0 = "-XX--X-XX-X-X--X---XX-X---XXXX-----X"; int Arr1[] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; string Arg3 = "???++++?++++++++++++++++++++??????--"; verify_case(4, Arg3, getContainerInfo(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        SurveillanceSystem ___test;
        ___test.run_test(1);
        return 0;
}
// END CUT HERE