// BEGIN CUT HERE

// END CUT HERE
#line 5 "HatRack.cpp"
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
vector <int> des[2010];
int dep[2010],mindep[2010],maxdep[2010],js[2010];
long long mi[70];
void dfs(int s,int pre)
{
	dep[s]=dep[pre]+1;
	mindep[s]=2100000000;maxdep[s]=-2100000000;
	int ls=0;
	for (int k=0;k<des[s].size();k++) if (des[s][k]!=pre)
	{
		dfs(des[s][k],s);
		mindep[s]=min(mindep[s],mindep[des[s][k]]);
		maxdep[s]=max(maxdep[s],maxdep[des[s][k]]);
		/*if (mindep[des[s][k]]==2100000000)
		{
			mindep[s]=min(mindep[s],dep[des[s][k]]);
			maxdep[s]=max(maxdep[s],dep[des[s][k]]);
		}*/
		ls++;
	}
	if (ls<2)
	{
		mindep[s]=min(mindep[s],dep[s]);
		maxdep[s]=max(maxdep[s],dep[s]);
	}
}
class HatRack
{
        public:
        long long countWays(vector <int> k1, vector <int> k2)
        {
        	if (k1.size()==0) return 1;
        	if (k1.size()==1) return 2;
        	int n=0;
			for (int i=0;i<k1.size();i++)
			{
				cout<<k1[i]<<' '<<k2[i]<<endl;
				n=max(n,k1[i]);n=max(n,k2[i]);
				des[k1[i]].push_back(k2[i]);des[k2[i]].push_back(k1[i]);
			}
			int ls=0;
			for (int i=1;i<=n;i++) if (des[i].size()==2) ls++;else if (des[i].size()>=4) return 0;
			if (ls>2) return 0;
			long long ans=0;
			mi[0]=1;for (int i=1;i<=60;i++) mi[i]=mi[i-1]*2;
			for (int i=1;i<=n;i++) if (des[i].size()==2)
			{
				dfs(i,0);//cout<<i<<' '<<mindep[i]<<' '<<maxdep[i]<<endl;
				memset(js,0,sizeof(js));ls=0;
				for (int j=1;j<=n;j++)
				{
					//if (mindep[j]==2100000000) continue;
					if (maxdep[j]-mindep[j]>1) goto bomb;
					if (maxdep[j]-mindep[j]>0) js[dep[j]]++;
					if (js[dep[j]]>=2) goto bomb;
					if ((des[j].size()==3-(i==j))&&(maxdep[j]==mindep[j])) ls++;
				}
				ans+=mi[ls];
				bomb:;
			}
			return ans;
				
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 2LL; verify_case(0, Arg2, countWays(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 2LL; verify_case(1, Arg2, countWays(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(2, Arg2, countWays(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {6,6,6,4,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,4,5,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(3, Arg2, countWays(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1,1,2,2,11,11,8,8,3,3,4,4,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,11,8,12,13,9,10,4,5,7,6,14}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 16LL; verify_case(4, Arg2, countWays(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {1,2,3,4,5,6,7,8,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5,6,7,8,9,10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(5, Arg2, countWays(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        HatRack ___test;
        ___test.run_test(4);
        return 0;
}
// END CUT HERE
