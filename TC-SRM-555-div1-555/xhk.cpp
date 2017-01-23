// BEGIN CUT HERE

// END CUT HERE
#line 6 "XorBoard.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=555555555;
int n,m,sc,sr,ans,lim;
int comb[3210][3210];

class XorBoard
{
	public:
	int count(int H, int W, int Rcount, int Ccount, int S)
	{	int i,j;
	 	
	 	n=H;
	 	m=W;
	 	sr=Rcount;
	 	sc=Ccount;
	 	lim=max(sc,sr)+max(n,m);
	 	for(i=0;i<=lim;i++)
	 	{	comb[i][0]=1;
	 		for(j=1;j<=i;j++)
	 			comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%mod;
	 	}
	 	ans=0;
	 	for(i=0;i<=n;i++)
	 		for(j=0;j<=m;j++)
	 			if(i<=sr && !((sr-i)&1) && j<=sc && !((sc-j)&1) && i*m+j*n-2*i*j==S)
	 			{	//cout<<i<<" "<<j<<endl;
				 	ans=(ans+(ll)comb[n][i]*comb[m][j]%mod*comb[(sr-i)/2+n-1][n-1]%mod*comb[(sc-j)/2+m-1][m-1]%mod)%mod;
				}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; int Arg3 = 2; int Arg4 = 4; int Arg5 = 4; verify_case(0, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 0; int Arg3 = 0; int Arg4 = 1; int Arg5 = 0; verify_case(1, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 20; int Arg2 = 50; int Arg3 = 40; int Arg4 = 200; int Arg5 = 333759825; verify_case(2, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 1200; int Arg1 = 1000; int Arg2 = 800; int Arg3 = 600; int Arg4 = 4000; int Arg5 = 96859710; verify_case(3, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arg0 = 555; int Arg1 = 555; int Arg2 = 555; int Arg3 = 555; int Arg4 = 5550; int Arg5 = 549361755; verify_case(4, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{XorBoard ___test;
 ___test.run_test(-1);
 return 0;
}
// END CUT HERE
