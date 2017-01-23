// BEGIN CUT HERE

// END CUT HERE
#line 5 "TomekPhone.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m,tot,ans;
int a[3010],b[3010];

class TomekPhone
{	public:
	int minKeystrokes(vector <int> frequencies, vector <int> keySizes)
	{	int i,j;
		
		n=frequencies.size();
		for(i=1;i<=n;i++) a[i]=frequencies[i-1];
		m=keySizes.size();
		tot=0;
		for(i=1;i<=m;i++)
			for(j=1;j<=keySizes[i-1];j++) //把每个数组合起来 
				b[++tot]=j;
		if(tot<n) return -1;
		sort(b+1,b+tot+1);
		sort(a+1,a+n+1);
		ans=0;
		for(i=1;i<=n;i++) //排序后倒着放就好了 
			ans+=b[i]*a[n+1-i];
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {7,3,4,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 19; verify_case(0, Arg2, minKeystrokes(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {13,7,4,20}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = -1; verify_case(1, Arg2, minKeystrokes(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {11,23,4,50,1000,7,18}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,1,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1164; verify_case(2, Arg2, minKeystrokes(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {100,1000,1,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {50}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1234; verify_case(3, Arg2, minKeystrokes(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10,10,10,10,10,10,10,10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3353; verify_case(4, Arg2, minKeystrokes(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	TomekPhone ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
