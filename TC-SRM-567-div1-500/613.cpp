// BEGIN CUT HERE

// END CUT HERE
#line 5 "StringGame.cpp"
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
int num[210][210];
bool can[210],used[210];
class StringGame
{
        public:
        vector <int> getWinningStrings(vector <string> vec)
        {
			for (int i=0;i<vec.size();i++)
			{
				sort(vec[i].begin(),vec[i].end());
				for (int j=0;j<vec[i].length();j++) num[i][vec[i][j]]++;
			}
			vector <int> ans; 
			for (int i=0;i<vec.size();i++)
			{
				bool bo=false;
				for (int j=0;j<vec.size();j++) if ((i!=j)&&(vec[i]==vec[j])) {bo=true;break;}
				if (bo) continue;
				memset(can,true,sizeof(can));can[i]=false;
				memset(used,false,sizeof(used));
				bool all=true;
				for (int t=1;t<=26;t++)
				{
					bool pd=false;
					for (int ch='a';ch<='z';ch++) if (!used[ch])
					{
						pd=true;
						for (int j=0;j<vec.size();j++) if ((can[j])&&(num[j][ch]>num[i][ch])) {pd=false;break;}
						if (pd)
						{
							for (int j=0;j<vec.size();j++) if (num[j][ch]<num[i][ch]) can[j]=false;
							used[ch]=true;
							break;
						}
					}
					if (!pd) {all=false;break;}
				}
				if (all) ans.push_back(i);
			}
			return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"a", "b", "c", "d"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, 2, 3 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, getWinningStrings(Arg0)); }
	void test_case_1() { string Arr0[] = {"aabbcc", "aaabbb", "aaaccc"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, getWinningStrings(Arg0)); }
	void test_case_2() { string Arr0[] = {"ab", "ba"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, getWinningStrings(Arg0)); }
	void test_case_3() { string Arr0[] = {"xaocxsss", "oooxsoas", "xaooosss", "xaocssss", "coxaosxx"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 3, 4 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, getWinningStrings(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        StringGame ___test;
        ___test.run_test(1);
        return 0;
}
// END CUT HERE
