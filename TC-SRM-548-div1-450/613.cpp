// BEGIN CUT HERE

// END CUT HERE
#line 5 "KingdomAndDice.cpp"
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
set<int> mp;
int nxt[55];
int f[55][2555];
class KingdomAndDice
{
        public:
        double newFairness(vector <int> fst, vector <int> lst, int x)
        {
        	memset(f,0,sizeof(f));
        	memset(nxt,0,sizeof(nxt));
        	sort(fst.begin(),fst.end());
        	sort(lst.begin(),lst.end());
        	//for (int i=0;i<fst.size();i++) if (fst[i]) fst[i]++;
        	//for (int i=0;i<lst.size();i++) lst[i]++;
        	//x++;
        	int n=fst.size(),ths=0,d=0;
			for (int i=0;i<n;i++)
			{
				if (fst[i])
				{
					for (int j=0;j<n;j++) ths+=(fst[i]>lst[j]);
				}
				else d++;
			}
					//cout<<d<<' '<<ths<<endl; 
			mp.clear();
			for (int i=0;i<n;i++) {mp.insert(lst[i]);if (fst[i]) mp.insert(fst[i]);}
			for (int i=0;i<n;i++)
			{
				nxt[i]=lst[i]+1;
				while (mp.count(nxt[i])) nxt[i]++;
			}
					//for (int i=0;i<n;i++) cout<<nxt[i]<<' ';cout<<endl;
			int nxt_1=0;
			memset(f,255,sizeof(f));
			f[0][0]=0;
			for (int i=0;i<d;i++)
			for (int j=0;j<=i*n;j++) if (f[i][j]!=-1)
			{
				int nt=f[i][j]+(f[i][j]!=0);
				while (mp.count(nt)) nt++;
				for (int k=0;k<n;k++)
				{
					int minn=nxt[k];
					if (minn<=f[i][j]) minn=nt;
					if (minn>x) continue;
					if ((k<n-1)&&(minn>=lst[k+1])) continue;
					if (f[i+1][j+k+1]!=-1) f[i+1][j+k+1]=min(f[i+1][j+k+1],minn);else f[i+1][j+k+1]=minn;
				}
				int minn=nxt_1;
				if (minn<=f[i][j]) minn=nt;
				if (minn>x) continue;
				if (minn>=lst[0]) continue;
				if (f[i+1][j]!=-1) f[i+1][j]=min(f[i+1][j],minn);else f[i+1][j]=minn;
			}
			int ans=n*n;
			for (int i=0;i<=d*n;i++) if (f[d][i]!=-1)
			{
				int pp=(i+ths);
				//cout<<pp<<endl;
				if ((abs(2*pp-n*n)<abs(2*ans-n*n))||((abs(2*pp-n*n)==abs(2*ans-n*n))&&(pp<=ans))) ans=pp;
			}
			return (double)ans/(n*n);
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; double Arg3 = 0.25; verify_case(0, Arg3, newFairness(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0, 2, 7, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6, 3, 8, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10; double Arg3 = 0.375; verify_case(1, Arg3, newFairness(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5, 8}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 47; double Arg3 = 0.5; verify_case(2, Arg3, newFairness(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {19, 50, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {26, 100, 37}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1000; double Arg3 = 0.2222222222222222; verify_case(3, Arg3, newFairness(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {6371, 0, 6256, 1852, 0, 0, 6317, 3004, 5218, 9012}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1557, 6318, 1560, 4519, 2012, 6316, 6315, 1559, 8215, 1561}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10000; double Arg3 = 0.49; verify_case(4, Arg3, newFairness(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        KingdomAndDice ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
