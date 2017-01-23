// BEGIN CUT HERE

// END CUT HERE
#line 5 "KingdomAndCities.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int maxn=50,mod=1000000007;
int n,m,ne,ans;
int comb[1310][60],c[60][60];

void work()
{int i,j,k,p;
 
 for(i=0;i<=max(n,n*(n-1)/2);i++)
 {	comb[i][0]=1;
 	for(j=1;j<=min(maxn,i);j++)
 		comb[i][j]=(comb[i-1][j-1]+comb[i-1][j])%mod;
 }
 c[1][0]=1;
 for(i=2;i<=n;i++)
 	for(j=0;j<=ne;j++)
 	{	c[i][j]=comb[i*(i-1)/2][j];
 		for(k=1;k<i;k++)
 			for(p=0;p<=j;p++)
 				c[i][j]=(c[i][j]+mod-(ll)comb[i-1][k-1]*c[k][p]%mod*comb[(i-k)*(i-k-1)/2][j-p]%mod)%mod;
 		//if(j>i*(i-1)/2) cout<<c[i][j]<<endl;		
 	}
}

class KingdomAndCities
{	public:
	int howMany(int N, int M, int K)
	{	int i,j,i1,j1;
	
		n=N;
		m=M;
		ne=K;
		work();
		ans=0;
		if(m==0)
			return c[n][ne];
		else if(m==1)
		{	for(i=1;i<n-1;i++)
				for(j=0;j<=ne-2;j++)
					ans=(ans+(ll)comb[n-1-1][i-1]*c[i][j]%mod*c[n-1-i][ne-2-j]%mod*i%mod*(n-1-i)%mod)%mod;
			ans=(ans+(ll)c[n-1][ne-2]*comb[n-1][2]%mod)%mod;		
			return ans;
		}
		else
		{	for(i=1;i<n-2;i++)
				for(j=0;j<=ne-4;j++)
					for(i1=1;i1+i<n-2;i1++)
						for(j1=0;j1+j<=ne-4;j1++)
							ans=(ans+(ll)comb[n-2][i]*comb[n-2-i][i1]%mod*c[i][j]%mod*c[i1][j1]%mod*c[n-2-i-i1][ne-4-j-j1]%mod*i%mod*i1%mod*i1%mod*(n-2-i-i1)%mod)%mod;
			for(i=2;i<n-2;i++)
				for(j=0;j<=ne-4;j++)
					ans=(ans+(ll)comb[n-2][i]*c[i][j]%mod*c[n-2-i][ne-4-j]%mod*comb[i][2]%mod*i%mod*(n-2-i)%mod*2%mod)%mod;
			for(i=1;i<n-2;i++)
				for(j=0;j<=ne-4;j++)
					ans=(ans+(ll)comb[n-2-1][i-1]*c[i][j]%mod*c[n-2-i][ne-4-j]%mod*i%mod*(n-2-i)%mod*i%mod*(n-2-i)%mod)%mod;
			for(i=1;i<n-2;i++)	
				for(j=0;j<=ne-3;j++)
					ans=(ans+(ll)comb[n-2][i]*c[i][j]%mod*c[n-2-i][ne-3-j]%mod*i%mod*(n-2-i)%mod)%mod;
			ans=(ans+(ll)c[n-2][ne-4]*comb[n-2][2]%mod*comb[n-2][2]%mod)%mod;
			ans=(ans+(ll)c[n-2][ne-3]*(n-2)%mod*(n-2)%mod)%mod;
			return ans;
		}	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 0; int Arg2 = 3; int Arg3 = 1; verify_case(0, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 1; int Arg2 = 4; int Arg3 = 9; verify_case(1, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 5; int Arg1 = 2; int Arg2 = 11; int Arg3 = 0; verify_case(2, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 5; int Arg1 = 0; int Arg2 = 8; int Arg3 = 45; verify_case(3, Arg3, howMany(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 10; int Arg1 = 2; int Arg2 = 20; int Arg3 = 150810825; verify_case(4, Arg3, howMany(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	KingdomAndCities ___test;
	___test.run_test(-1);
	//cout<<___test.howMany(23,2,29)<<endl;
	return 0;
}
// END CUT HERE
