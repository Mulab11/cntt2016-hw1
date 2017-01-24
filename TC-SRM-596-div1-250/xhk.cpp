// BEGIN CUT HERE

// END CUT HERE
#line 5 "IncrementAndDoubling.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=1e9;
int n,ans;
int a[110],cnt[2010];

class IncrementAndDoubling
{	public:
	int getMin(vector <int> desiredArray)
	{	int i,j,s;
		
		n=desiredArray.size();
		for(i=1;i<=n;i++) a[i]=desiredArray[i-1];
		for(i=1;i<(1<<10);i++) cnt[i]=cnt[i-(i&(-i))]+1;
		ans=inf;	
		for(i=0;i<=10;i++)
		{	s=0;
			for(j=1;j<=n;j++)
				if(a[j]<(1<<(i+1))) //如果倍增次数大于这个数位数，只要把数位上的1补上 
					s+=cnt[a[j]];
				else
					s+=(a[j]/(1<<i))+(a[j]&((1<<i)-1)); //如果倍增次数小于这个数位数，先把高位填好，一次倍增完，再补低位 
			ans=min(ans,s+i);
		}
		return ans;		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, getMin(Arg0)); }
	void test_case_1() { int Arr0[] = {16, 16, 16}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(1, Arg1, getMin(Arg0)); }
	void test_case_2() { int Arr0[] = {100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(2, Arg1, getMin(Arg0)); }
	void test_case_3() { int Arr0[] = {0, 0, 1, 0, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(3, Arg1, getMin(Arg0)); }
	void test_case_4() { int Arr0[] = {123, 234, 345, 456, 567, 789}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 40; verify_case(4, Arg1, getMin(Arg0)); }
	void test_case_5() { int Arr0[] = {7,5,8,1,8,6,6,5,3,5,5,2,8,9,9,4,6,9,4,4,1,9,9,2,8,4,7,4,8,8,6,3,9,4,3,4,5,1,9,8,3,8,3,7,9,3,8,4,4,7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 84; verify_case(5, Arg1, getMin(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	IncrementAndDoubling ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
