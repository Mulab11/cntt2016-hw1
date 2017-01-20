// BEGIN CUT HERE

// END CUT HERE
//#line 5 "CentaurCompany.cpp"
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
vector <int> des[55];
long long f[55][155][2],dp[155],ls[155];
int n,size[55];
int go(int pile,int point){return 2*pile-point;}
void dfs(int s,int pre)
{
	bool bo=true;
	size[s]=1;
	for (int k=0;k<des[s].size();k++) if (des[s][k]!=pre)
	{
		bo=false;
		dfs(des[s][k],s);
		size[s]+=size[des[s][k]];
	}
	if (bo)
	{
		f[s][go(0,0)+n][0]=1;
		f[s][go(1,1)+n][1]=1;
		return;
	}
	//不选这个点
	memset(dp,0,sizeof(dp));dp[go(0,0)+n]=1;
	for (int k=0;k<des[s].size();k++) if (des[s][k]!=pre)
	{
		int p=des[s][k];
		memcpy(ls,dp,sizeof(dp));
		memset(dp,0,sizeof(dp));
		for (int d=size[s];d>=-size[s];d--)
		for (int i=-size[p];i<=size[p];i++)
			dp[d+n]=dp[d+n]+ls[d-i+n]*(f[p][i+n][0]+f[p][i+n][1]);
	}
	for (int i=-size[s];i<=size[s];i++) 
	{
		f[s][i+n][0]=dp[i+n];
		//if (s==3) cout<<i<<' '<<0<<' '<<f[s][i+n][0]<<endl;
	}
	//end
	//选这个点
	memset(dp,0,sizeof(dp));dp[go(1,1)+n]=1;
	for (int k=0;k<des[s].size();k++) if (des[s][k]!=pre)
	{
		int p=des[s][k];
		memcpy(ls,dp,sizeof(dp));
		memset(dp,0,sizeof(dp));
		for (int d=size[s];d>=-size[s];d--)
		for (int i=-size[p];i<=size[p];i++)
			dp[d+n]=dp[d+n]+ls[d-i+n]*(f[p][i+n][0]+f[p][i+2+n][1]);
	}
	for (int i=-size[s];i<=size[s];i++)
	{
		f[s][i+n][1]=dp[i+n];
		//if (s==3) cout<<i<<' '<<1<<' '<<f[s][i+n][1]<<endl;
	}//end
} 
	
class CentaurCompany
{
        public:
        double getvalue(vector <int> a, vector <int> b)
        {
			n=75;cout<<n<<endl;
			for (int i=0;i<a.size();i++)
			{
				//cout<<a[i]<<' '<<b[i]<<endl;
				des[a[i]].push_back(b[i]);
				des[b[i]].push_back(a[i]);
			}
			dfs(1,0);
			double ans=0,all=0;
			for (int i=-n;i<=n;i++)
			{
				ans+=(double)max(i-2,0)*(f[1][i+n][0]+f[1][i+n][1]);
				all+=f[1][i+n][0]+f[1][i+n][1];
			}
			//cout<<(double)all<<endl;
			cout<<2*ans/all<<endl;
			return 2*ans/all; 			
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.0; verify_case(0, Arg2, getvalue(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.125; verify_case(1, Arg2, getvalue(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1,2,3,2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.375; verify_case(2, Arg2, getvalue(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {1,2,3,4,5,6,7,8,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5,6,7,8,9,10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.41796875; verify_case(3, Arg2, getvalue(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 15.500000001076842; verify_case(4, Arg2, getvalue(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {10, 7, 2, 5, 6, 2, 4, 9, 7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8, 10, 10, 4, 1, 6, 2, 2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 0.646484375; verify_case(5, Arg2, getvalue(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        CentaurCompany ___test;
        ___test.run_test(5);
        return 0;
}
// END CUT HERE
