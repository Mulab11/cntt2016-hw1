// BEGIN CUT HERE

// END CUT HERE
//#line 5 "LeftRightDigitsGame2.cpp"
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
#define pa pair<string,string>
using namespace std;
pa f[55][55][3][3];
bool legal[55][55][3][3];
string st,low;
int check(string s1,string s2)
{
	if (s1>s2) return 2;
	else if (s1==s2) return 1;
	return 0;
}
void update(string s1,string s2)
{
	int p1=check(s1,low.substr(0,s1.size())),p2=check(s2,low.substr(low.size()-s2.size(),s2.size()));
	if (legal[s1.size()][s2.size()][p1][p2]) f[s1.size()][s2.size()][p1][p2]=min(f[s1.size()][s2.size()][p1][p2],make_pair(s1,s2));
	else
	{
		legal[s1.size()][s2.size()][p1][p2]=true;
		f[s1.size()][s2.size()][p1][p2]=make_pair(s1,s2);
	}
}
class LeftRightDigitsGame2
{
        public:
        string minNumber(string st_, string low_)
        {
			low=low_;st=st_;
			memset(legal,false,sizeof(legal));
			legal[0][0][1][1]=true;
			for (int l=0;l<=st.size();l++)
			for (int r=0;r<=st.size()-l;r++)
			for (int tl=0;tl<=2;tl++)
			for (int tr=0;tr<=2;tr++)
			if ((legal[l][r][tl][tr])&&(l+r!=st.size()))
			{
				char ch=st[st.size()-1-l-r];
				update(f[l][r][tl][tr].first+ch,f[l][r][tl][tr].second);
				update(f[l][r][tl][tr].first,ch+f[l][r][tl][tr].second);
			}
			
			string ans="~";
			for (int i=0;i<st.size();i++)
			{
				pa ls;
				if (legal[i][st.size()-i][2][0])
				{
					ls=f[i][st.size()-i][2][0];
					ans=min(ans,ls.first+ls.second);
				}
				if (legal[i][st.size()-i][2][1])
				{
					ls=f[i][st.size()-i][2][1];
					ans=min(ans,ls.first+ls.second);
				}
				if (legal[i][st.size()-i][2][2])
				{
					ls=f[i][st.size()-i][2][2];
					ans=min(ans,ls.first+ls.second);
				}
				if (legal[i][st.size()-i][1][2])
				{
					ls=f[i][st.size()-i][1][2];
					ans=min(ans,ls.first+ls.second);
				}
				if (legal[i][st.size()-i][1][1])
				{
					ls=f[i][st.size()-i][1][1];
					ans=min(ans,ls.first+ls.second);
				}
			}
			if (ans=="~") ans="";
			return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "565"; string Arg1 = "556"; string Arg2 = "556"; verify_case(0, Arg2, minNumber(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "565"; string Arg1 = "566"; string Arg2 = "655"; verify_case(1, Arg2, minNumber(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "565"; string Arg1 = "656"; string Arg2 = ""; verify_case(2, Arg2, minNumber(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "9876543210"; string Arg1 = "5565565565"; string Arg2 = "5678943210"; verify_case(3, Arg2, minNumber(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "8016352"; string Arg1 = "1000000"; string Arg2 = "1086352"; verify_case(4, Arg2, minNumber(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        LeftRightDigitsGame2 ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
