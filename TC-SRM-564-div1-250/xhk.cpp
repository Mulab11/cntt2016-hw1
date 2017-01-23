// BEGIN CUT HERE

// END CUT HERE
#line 5 "KnightCircuit2.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m;

class KnightCircuit2
{	public:
	int maxSize(int w, int h)
	{	int i,j;
	 	
	 	n=w;
	 	m=h;
	 	if(n<m) swap(n,m);
	 	if(m>=3) //分类讨论 n,m>=3的时候min(n,m)=3答案为8否则答案为n*m 
	 		return (n==3 && m==3)?8:n*m;
	 	else if(m==1) //边界情况 
	 		return 1;
	 	else if(m==2) //边界情况
	 		return (n+1)/2;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; verify_case(0, Arg2, maxSize(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 15; int Arg1 = 2; int Arg2 = 8; verify_case(1, Arg2, maxSize(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 100; int Arg1 = 100; int Arg2 = 10000; verify_case(2, Arg2, maxSize(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	KnightCircuit2 ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
