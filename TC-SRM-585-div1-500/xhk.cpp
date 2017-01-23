// BEGIN CUT HERE

// END CUT HERE
#line 5 "LISNumber.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=1000000007;
int n,s,maxn,ans;
int a[110],f[2010],comb[3010][3010];

class LISNumber
{	public:
	int count(vector <int> cardsnum, int K)
	{	int i,j,k;
		
		n=cardsnum.size();
		s=0;
		for(i=1;i<=n;i++) a[i]=cardsnum[i-1],s+=a[i];
		maxn=3000;
		for(i=0;i<maxn;i++) //预处理组合数 
		{	comb[i][0]=1;
			for(j=1;j<=i;j++)
				comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%mod;
		}
		memset(f,0,sizeof(f));
		for(i=1;i<=s;i++)
		{	f[i]=1;
			for(j=1;j<=n;j++)
				f[i]=(ll)f[i]*comb[i][a[j]]%mod; //直接用组合数计算，包含重复 
			for(k=1;k<i;k++)
				f[i]=(f[i]+mod-(ll)f[k]*comb[i-k+s][s]%mod)%mod; //去掉答案为k的情况 
		}
		ans=f[K];
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 4; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 0; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {36, 36, 36, 36, 36}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 36; int Arg2 = 1; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {3, 2, 11, 5, 7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 20; int Arg2 = 474640725; verify_case(3, Arg2, count(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {31, 4, 15, 9, 26, 5, 35, 8, 9, 7, 9, 32, 3, 8, 4, 6, 26}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 58; int Arg2 = 12133719; verify_case(4, Arg2, count(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {27, 18, 28, 18, 28, 4, 5, 9, 4, 5, 23, 5,
 36, 28, 7, 4, 7, 13, 5, 26, 6, 24, 9, 7,
 7, 5, 7, 24, 7, 9, 36, 9, 9, 9, 5, 9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 116; int Arg2 = 516440918; verify_case(5, Arg2, count(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	LISNumber ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
