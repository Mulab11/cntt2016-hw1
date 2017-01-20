// BEGIN CUT HERE

// END CUT HERE
#line 5 "PolygonTraversal.cpp"
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
int mi[30];
long long f[270000][20];
inline bool getwei(int s,int w) {return s&mi[w-1];}
inline bool getsumwei(int s,int l,int r)
{
	if (l>r) return false;
	return s&(mi[r]-mi[l-1]);
}
class PolygonTraversal
{
        public:
        long long count(int n, vector <int> vec)
        {
        	memset(f,0,sizeof(f));
			mi[0]=1;for (int i=1;i<=20;i++) mi[i]=mi[i-1]*2;
			int p=0;for (int i=0;i<vec.size();i++) p+=mi[vec[i]-1];
			f[p][vec[vec.size()-1]]=1;
			for (int i=0;i<mi[n]-1;i++) if ((i&p)==p)
			for (int j=1;j<=n;j++) if (f[i][j])
			{
				for (int k=1;k<=n;k++) if (!getwei(i,k))
				{
					if (!getsumwei(i,min(j,k)+1,max(j,k)-1)) continue;
					if ((!getsumwei(i,max(j,k)+1,n))&&(!getsumwei(i,1,min(j,k)-1))) continue;
					//cout<<(i|mi[k-1])<<' '<<k<<endl;
					f[i|mi[k-1]][k]+=f[i][j];
				}
			}
			//cout<<f[mi[0]+mi[2]+mi[4]][5]<<endl;
			long long ans=0;
			for (int i=1;i<=n;i++) if ((abs(i-vec[0])>1)&&((i!=1)||(vec[0]!=n))&&((i!=n)||(vec[0]!=1))) ans+=f[mi[n]-1][i];
			return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arr1[] = {1, 3, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1LL; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 6; int Arr1[] = {1, 4, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1LL; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 7; int Arr1[] = {2, 4, 7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 2LL; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 7; int Arr1[] = {1, 2, 3, 4, 6, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(3, Arg2, count(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 18; int Arr1[] = {1, 7, 18}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 4374612736LL; verify_case(4, Arg2, count(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        PolygonTraversal ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
