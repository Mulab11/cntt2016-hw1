// BEGIN CUT HERE

// END CUT HERE
#line 6 "CuttingBitString.cpp"
#include<bits/stdc++.h>
using namespace std;

int n;
int f[110];
char a[110];

int check(int l,int r)
{long long x=0,s;
 int i;

 if(a[l]=='0') return 0;
 for(i=l;i<=r;i++)
 	x=x*2+a[i]-48;
 s=1;
 for(i=0;i<=25;i++)
 {	if(x==s) return 1;
 	s*=5;
 }
 return 0;
}

class CuttingBitString
{
	public:
	int getmin(string S)
	{	int i,j;
		
		n=S.length();
		for(i=1;i<=n;i++) a[i]=S[i-1];
		f[0]=0;
		for(i=1;i<=n;i++)
		{	f[i]=-1;
			for(j=0;j<i;j++)
				if(f[j]!=-1 && check(j+1,i))
				{	if(f[i]==-1 || f[j]+1<f[i])
						f[i]=f[j]+1;
				}
		}
		return f[n];
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "101101101"; int Arg1 = 3; verify_case(0, Arg1, getmin(Arg0)); }
	void test_case_1() { string Arg0 = "1111101"; int Arg1 = 1; verify_case(1, Arg1, getmin(Arg0)); }
	void test_case_2() { string Arg0 = "00000"; int Arg1 = -1; verify_case(2, Arg1, getmin(Arg0)); }
	void test_case_3() { string Arg0 = "110011011"; int Arg1 = 3; verify_case(3, Arg1, getmin(Arg0)); }
	void test_case_4() { string Arg0 = "1000101011"; int Arg1 = -1; verify_case(4, Arg1, getmin(Arg0)); }
	void test_case_5() { string Arg0 = "111011100110101100101110111"; int Arg1 = 5; verify_case(5, Arg1, getmin(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{CuttingBitString ___test;
 ___test.run_test(-1);
 return 0;
}
// END CUT HERE
