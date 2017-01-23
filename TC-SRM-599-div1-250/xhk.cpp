// BEGIN CUT HERE

// END CUT HERE
#line 5 "BigFatInteger.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=1e9;
int n,ans;
int a[110];

int calc(int i,int k)
{if((1<<k)>=i) return 1;
 return (i-1)/(1<<k)+1;
}

class BigFatInteger
{	public:
	int minOperations(int A, int B)
	{	int i,j,t,s;
	
		t=A;
		n=0;
		for(i=2;i*i<=A;i++)
			if(t%i==0)
			{	s=0;
				while(t%i==0)
				{	t/=i;
					s++;
				}
				a[++n]=B*s;
			}
		if(t>1) a[++n]=B;
		//cout<<a[1]<<" "<<a[2]<<" "<<n<<endl;
		ans=inf;
		for(i=0;i<=30;i++)
		{	s=0;
			for(j=1;j<=n;j++)
				s+=calc(a[j],i);
			ans=min(ans,s+i);
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 6; int Arg1 = 1; int Arg2 = 2; verify_case(0, Arg2, minOperations(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 162; int Arg1 = 1; int Arg2 = 4; verify_case(1, Arg2, minOperations(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 999983; int Arg1 = 9; int Arg2 = 5; verify_case(2, Arg2, minOperations(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 360; int Arg1 = 8; int Arg2 = 8; verify_case(3, Arg2, minOperations(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	BigFatInteger ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
