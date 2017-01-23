// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheNumberGame.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m;
int a[110],b[110];

class TheNumberGame
{	public:
	string determineOutcome(int A, int B)
	{	int i,j,t,flag;
		
		t=A;
		while(t)
		{	a[++n]=t%10;
			t/=10;
		}
		t=B;
		while(t)
		{	b[++m]=t%10;
			t/=10;
		}
		if(n<m) return "Manao loses";
		if(n==m)
		{	flag=1;
			for(i=1;i<=n;i++)
				if(a[i]!=b[i]) flag=0;
			if(flag) return "Manao wins";
			flag=1;
			for(i=1;i<=n;i++)
				if(a[i]!=b[m+1-i]) flag=0;
			if(flag) return "Manao wins";
			return "Manao loses";
		}
		for(i=1;i<=n-m+1;i++)
		{	flag=1;
			for(j=1;j<=m;j++)
				if(a[i+j-1]!=b[j]) flag=0;
			if(flag) return "Manao wins";
			flag=1;
			for(j=1;j<=m;j++)
				if(a[i+j-1]!=b[m+1-j]) flag=0;
			if(flag) return "Manao wins";	
		}
		return "Manao loses";
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 45; int Arg1 = 4; string Arg2 = "Manao wins"; verify_case(0, Arg2, determineOutcome(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 45; int Arg1 = 5; string Arg2 = "Manao wins"; verify_case(1, Arg2, determineOutcome(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 99; int Arg1 = 123; string Arg2 = "Manao loses"; verify_case(2, Arg2, determineOutcome(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 2356236; int Arg1 = 5666; string Arg2 = "Manao loses"; verify_case(3, Arg2, determineOutcome(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	TheNumberGame ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
