// BEGIN CUT HERE

// END CUT HERE
#line 5 "MegaFactorial.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long

struct matrix
{int val[20][20];
 void init()
 {	int i,j;
 	for(i=0;i<20;i++)
 		for(j=0;j<20;j++)
 			val[i][j]=0;
 }
};
struct matrix g[40],f,e;

int n,m,M,ans,mod=1000000009;

void update(int &i,int x)
{i=(i+x)-(i+x>=M?M:0);
}

matrix operator *(matrix A,matrix B)
{matrix ret;
 int i,j,k;
 
 ret.init();
 for(i=0;i<=m;i++)
 	for(j=0;j<=m;j++)
 	{	if(A.val[i][j]==0) continue;
	 	for(k=0;k<=m;k++)
 			update(ret.val[i][k],(ll)A.val[i][j]*B.val[j][k]%M);
	}
 return ret;
}

int fpow(int i,int j,int M)
{int ret=1;
 for(;j;i=(ll)i*i%M,j/=2)
 	if(j&1) ret=(ll)ret*i%M;
 return ret;
}

matrix fpow(matrix A,int j)
{matrix ret;
 if(j==0) return e;
 ret=fpow(A,j/2);
 ret=ret*ret;
 if(j&1) ret=ret*A;
 return ret;
}

int solve(int base)
{int i,j,t,w,s;
 
 g[0].init();
 for(i=1;i<=m;i++)
	for(j=i;j<=m;j++)
		g[0].val[i][j]=1;
 g[0].val[0][0]=1;
 //for(i=1;i<=m;i++) g[0].val[0][i]=1;
 w=0;
 t=n/base;
 while(t)
 {	w++;
 	g[w]=fpow(g[w-1],base);
	for(i=1;i<=m;i++) update(g[w].val[0][i],1);
	t/=base;
 }
 f.init();
 f.val[0][0]=1;
 //f.val[0][1]=1;
 
 //cout<<w<<endl;
 
 //for(i=0;i<=m;i++)
 //{	for(j=0;j<=m;j++)
 //		cout<<g[0].val[i][j]<<" ";
 //	cout<<endl;
 //}
 
 t=n;
 s=1;
 for(i=1;i<=w;i++) s*=base;
 for(;w>=0;w--)
 {	f=f*fpow(g[w],t/s);
 	//cout<<"## "<<t/s<<endl;
	t%=s;
 	s/=base;
 }
 return f.val[0][m];
}

class MegaFactorial
{	public:
	int countTrailingZeros(int N, int K, int B)
	{	int i,j,k,s1,s2;
		
		n=N;
		m=K;
		for(i=0;i<=m;i++) e.val[i][i]=1;
		if(B==2 || B==3 || B==5 || B==7)
		{	M=mod;
			return solve(B);
		}
		else if(B==4)
		{	M=mod;
			s1=solve(2);
			M=2;
			s2=solve(2);
			ans=(ll)(s1+mod-s2)%mod*fpow(2,mod-2,mod)%mod;
			return ans;
		}
		else if(B==9)
		{	M=mod;
			s1=solve(3);
			M=2;
			s2=solve(3);
			ans=(ll)(s1+mod-s2)%mod*fpow(2,mod-2,mod)%mod;
			return ans;
		}
		else if(B==8)
		{	M=mod;
			s1=solve(2);
			M=3;
			s2=solve(2);
			ans=(ll)(s1+mod-s2)%mod*fpow(3,mod-2,mod)%mod;
			return ans;
		}
		else if(B==6)
		{	M=mod;
			//n=2;
			return solve(3);
		}
		else if(B==10)
		{	M=mod;
			return solve(5);
		}
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 6; int Arg1 = 1; int Arg2 = 4; int Arg3 = 2; verify_case(0, Arg3, countTrailingZeros(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 2; int Arg2 = 6; int Arg3 = 2; verify_case(1, Arg3, countTrailingZeros(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 3; int Arg2 = 10; int Arg3 = 22; verify_case(2, Arg3, countTrailingZeros(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 50; int Arg1 = 10; int Arg2 = 8; int Arg3 = 806813906; verify_case(3, Arg3, countTrailingZeros(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arg0 = 1000000000; int Arg1 = 16; int Arg2 = 2; int Arg3 = 633700413; verify_case(4, Arg3, countTrailingZeros(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	MegaFactorial ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
