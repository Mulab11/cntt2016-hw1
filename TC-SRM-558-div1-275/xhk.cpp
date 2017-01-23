// BEGIN CUT HERE

// END CUT HERE
#line 5 "Stamp.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=0x3f3f3f3f;
int n,ans;
int f[110];
char col;
char a[110];

class Stamp
{	public:
	int getMinimumCost(string desiredColor, int stampCost, int pushCost)
	{	int i,j,sc,pc,l;
		
		n=desiredColor.length();
		for(i=1;i<=n;i++) a[i]=desiredColor[i-1];
		sc=stampCost;
		pc=pushCost;
		ans=inf;
		for(l=1;l<=n;l++) //枚举长度l 
		{	memset(f,0x3f,sizeof(f));
			f[0]=0;
			for(i=1;i<=n;i++) //f[i]表示把前i个填好的花费 
			{	j=1;
				col=a[i];
				while(j<=i && (a[i-j+1]=='*' || col=='*' || a[i-j+1]==col))
				{	if(j>=l)
						f[i]=min(f[i],f[i-j]+pc*((j-1)/l+1));
					if(a[i-j+1]!='*') col=a[i-j+1];	
					j++;
				}
			}
			ans=min(ans,f[n]+l*sc);
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "RRGGBB"; int Arg1 = 1; int Arg2 = 1; int Arg3 = 5; verify_case(0, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "R**GB*"; int Arg1 = 1; int Arg2 = 1; int Arg3 = 5; verify_case(1, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "BRRB"; int Arg1 = 2; int Arg2 = 7; int Arg3 = 30; verify_case(2, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "R*RR*GG"; int Arg1 = 10; int Arg2 = 58; int Arg3 = 204; verify_case(3, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arg0 = "*B**B**B*BB*G*BBB**B**B*"; int Arg1 = 5; int Arg2 = 2; int Arg3 = 33; verify_case(4, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arg0 = "*R*RG*G*GR*RGG*G*GGR***RR*GG"; int Arg1 = 7; int Arg2 = 1; int Arg3 = 30; verify_case(5, Arg3, getMinimumCost(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	Stamp ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
