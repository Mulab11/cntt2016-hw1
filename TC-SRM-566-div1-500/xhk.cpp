// BEGIN CUT HERE

// END CUT HERE
#line 5 "PenguinEmperor.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=1000000007;

int n,ans;
int h[360],h1[360],f[360],g[360];
long long l,m;

void update(int &i,int x)
{i+=x;
 if(i>=mod) i-=mod;
}

void mul(int A[],int B[],int C[]) //多项式乘法 
{static int ret[360];
 int i,j;
 
 memset(ret,0,sizeof(ret));
 for(i=0;i<n;i++)
 	for(j=0;j<n;j++)
 		update(ret[(i+j)%n],(ll)A[i]*B[j]%mod);
 for(i=0;i<n;i++) C[i]=ret[i];		
}

void fpow(int A[],long long j,int C[]) //多项式快速幂 
{static int ret[360],B[360];
 int i;
 
 memset(ret,0,sizeof(ret));
 ret[0]=1;
 for(i=0;i<n;i++) B[i]=A[i];
 for(;j;mul(B,B,B),j/=2)
 	if(j&1) mul(ret,B,ret);	
 for(i=0;i<n;i++) C[i]=ret[i];
}

class PenguinEmperor
{	public:
	int countJourneys(int numCities, long long daysPassed)
	{	int i,j;
		
		n=numCities;
		l=daysPassed;
		m=l/n;
		memset(f,0,sizeof(f));
		f[0]=1;
		for(i=1;i<=n;i++)
		{	memset(g,0,sizeof(g));
			g[i%n]=1;
			g[(n-i)%n]=1;
			mul(f,g,h); //构造转移矩阵 
			for(j=0;j<n;j++) f[j]=h[j];
		}
		fpow(f,m,h);
		for(i=1;i<=l%n;i++) //多余的枚举计算 
		{	memset(h1,0,sizeof(h1));
			for(j=0;j<n;j++)
			{	update(h1[(j+i)%n],h[j]);
				if((n&1) || i!=n/2) update(h1[(j+n-i)%n],h[j]);
			}
			for(j=0;j<n;j++) h[j]=h1[j];
		}
		ans=h[0];
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; long long Arg1 = 2LL; int Arg2 = 2; verify_case(0, Arg2, countJourneys(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 4; long long Arg1 = 3LL; int Arg2 = 2; verify_case(1, Arg2, countJourneys(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 5; long long Arg1 = 36LL; int Arg2 = 107374182; verify_case(2, Arg2, countJourneys(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 300; long long Arg1 = 751LL; int Arg2 = 413521250; verify_case(3, Arg2, countJourneys(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 300; long long Arg1 = 750LL; int Arg2 = 0; verify_case(4, Arg2, countJourneys(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 350; long long Arg1 = 1000000000000000000LL; int Arg2 = 667009739; verify_case(5, Arg2, countJourneys(Arg0, Arg1)); }
	void test_case_6() { int Arg0 = 5; long long Arg1 = 7LL; int Arg2 = 12; verify_case(6, Arg2, countJourneys(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	PenguinEmperor ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
