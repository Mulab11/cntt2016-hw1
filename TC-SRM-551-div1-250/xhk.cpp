// BEGIN CUT HERE

// END CUT HERE
#line 5 "ColorfulChocolates.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,ans,tot;
int a[110],b[110];

class ColorfulChocolates
{	public:
	int maximumSpread(string chocolates, int maxSwaps)
	{	int i,j,k,s,lim;

		n=chocolates.length();
		
		for(i=1;i<=n;i++)
			a[i]=chocolates[i-1]-64;
		ans=0;
		for(i=1;i<=26;i++)
			for(j=1;j<=n;j++)
			{	tot=0;
				s=0;
				for(k=j;k>=1;k--)
					if(a[k]==i)
					{	b[++tot]=j-k-s;
						s++;
					}
				s=0;	
				for(k=j+1;k<=n;k++)
					if(a[k]==i)
					{	b[++tot]=k-j-1-s;
						s++;
					}	
				sort(b+1,b+tot+1);
				lim=maxSwaps;
				s=0;
				for(k=1;k<=tot;k++)
					if(lim>=b[k])
					{	lim-=b[k];
						s++;
					}
					else
						break;
				ans=max(ans,s);
			}
		return ans;	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "ABCDCBC"; int Arg1 = 1; int Arg2 = 2; verify_case(0, Arg2, maximumSpread(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "ABCDCBC"; int Arg1 = 2; int Arg2 = 3; verify_case(1, Arg2, maximumSpread(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "ABBABABBA"; int Arg1 = 3; int Arg2 = 4; verify_case(2, Arg2, maximumSpread(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "ABBABABBA"; int Arg1 = 4; int Arg2 = 5; verify_case(3, Arg2, maximumSpread(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "QASOKZNHWNFODOQNHGQKGLIHTPJUVGKLHFZTGPDCEKSJYIWFOO"; int Arg1 = 77; int Arg2 = 5; verify_case(4, Arg2, maximumSpread(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	ColorfulChocolates ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
