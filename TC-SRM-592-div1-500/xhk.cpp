// BEGIN CUT HERE

// END CUT HERE
#line 5 "LittleElephantAndPermutationDiv1.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=1000000007;
int n,m,ans;
int f[51][51][2510];

void update(int &i,int x)
{i=(i+x)-(i+x>=mod?mod:0);
}

class LittleElephantAndPermutationDiv1
{	public:
	int getNumber(int N, int K)
	{	int i,j,k;
		
		n=N;
		m=K;
		memset(f,0,sizeof(f));
		f[0][0][0]=1; //一开始假设a[]为1~n最后乘上n! 
		for(i=0;i<n;i++)
			for(j=0;j<=i && j<=n-i;j++)
				for(k=0;k<=n*n;k++) //f[i][j][k]表示前i个数占了j个>i的位置,<=i的位置的贡献是k 
				{	if(!f[i][j][k]) continue;
					update(f[i+1][j][k+i+1],f[i][j][k]); //分类讨论i+1填哪以及i+1这个位置被谁填了 
					
					update(f[i+1][j+1][k],f[i][j][k]);
					update(f[i+1][j][k+i+1],(ll)f[i][j][k]*j%mod);
					
					update(f[i+1][j][k+i+1],(ll)f[i][j][k]*(i-(i-j))%mod);
					update(f[i+1][j-1][k+2*(i+1)],(ll)f[i][j][k]*(i-(i-j))%mod*j%mod);
				}
		ans=0;
		for(k=m;k<=n*n;k++)
			update(ans,f[n][0][k]);
		for(i=2;i<=n;i++) ans=(ll)ans*i%mod;
		return ans;	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; verify_case(0, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 1; int Arg2 = 4; verify_case(1, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 8; int Arg2 = 18; verify_case(2, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 74; int Arg2 = 484682624; verify_case(3, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 50; int Arg1 = 1000; int Arg2 = 539792695; verify_case(4, Arg2, getNumber(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	LittleElephantAndPermutationDiv1 ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
