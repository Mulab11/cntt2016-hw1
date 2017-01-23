// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheSquareRootDilemma.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
int n,m,tot,cnt,seed=314159;
int u[100010],prime[10010];
long long ans;
unsigned long long pw[100010],a[100010];

class TheSquareRootDilemma
{	public:
	int countPairs(int N, int M)
	{	int i,j,t,s;
		unsigned long long w;
		
		n=N;
		m=M;
		if(n<m) swap(n,m);
		memset(u,0,sizeof(u));
		tot=0;
		for(i=2;i<=n;i++)
			if(!u[i])
			{	prime[++tot]=i;
				for(j=i+i;j<=n;j+=i)
					u[j]=1;
			}
		pw[0]=1;
		for(i=1;i<=n;i++) pw[i]=pw[i-1]*seed;	
		cnt=0;
		for(i=1;i<=n;i++)
		{	w=0;
			t=i;
			for(j=1;j<=tot && (ll)prime[j]*prime[j]<=i;j++)
			{	s=0;
				while(t%prime[j]==0)
				{	t/=prime[j];
					s^=1;
				}
				if(s&1) w+=pw[prime[j]];
			}
			if(t!=1) w+=pw[t];
			a[++cnt]=w;
		}
		sort(a+1,a+cnt+1);
		ans=0;
		for(i=1;i<=m;i++)
		{	w=0;
			t=i;
			for(j=1;j<=tot && (ll)prime[j]*prime[j]<=i;j++)
			{	s=0;
				while(t%prime[j]==0)
				{	t/=prime[j];
					s^=1;
				}
				if(s&1) w+=pw[prime[j]];
			}
			if(t!=1) w+=pw[t];
			ans+=upper_bound(a+1,a+cnt+1,w+1)-lower_bound(a+1,a+cnt+1,w);
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; verify_case(0, Arg2, countPairs(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 10; int Arg1 = 1; int Arg2 = 3; verify_case(1, Arg2, countPairs(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 8; int Arg2 = 5; verify_case(2, Arg2, countPairs(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 100; int Arg1 = 100; int Arg2 = 310; verify_case(3, Arg2, countPairs(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	TheSquareRootDilemma ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
