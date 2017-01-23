// BEGIN CUT HERE

// END CUT HERE
#line 5 "WolfPack.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=1000000007;
int n,ans;
int fac[100010],inv_fac[100010];

int fpow(int i,int j)
{int ret=1;
 for(;j;i=(ll)i*i%mod,j/=2)
 	if(j&1) ret=(ll)ret*i%mod;
 return ret;
}

int comb(int N,int M)
{return (ll)fac[N]*inv_fac[M]%mod*inv_fac[N-M]%mod;
}

class WolfPack
{	public:
	int calc(vector <int> x, vector <int> y, int m)
	{	int i,j,s,s1,k,x1,y1;
	
		n=x.size();
		fac[0]=1;
		for(i=1;i<=m;i++) fac[i]=(ll)fac[i-1]*i%mod;
		inv_fac[m]=fpow(fac[m],mod-2);
		for(i=m-1;i>=0;i--) inv_fac[i]=(ll)inv_fac[i+1]*(i+1)%mod;
		for(i=1;i<=n;i++)
		{	x1=x[i-1];
			y1=y[i-1];
			x[i-1]=x1-y1;
			y[i-1]=x1+y1;
		}
		ans=0;
		for(i=-200000;i<=200000;i++)
		{	s1=1;
			for(j=1;j<=n;j++)
			{	k=(m+i-x[j-1])/2;
				if(k<0 || k>m || (m+i-x[j-1])%2)
				{	s1=0;
					break;
				}
				else
					s1=(ll)s1*comb(m,k)%mod;
			}
			ans=(ans+s1)%mod;
		}
		s=0;
		for(i=-200000;i<=200000;i++)
		{	s1=1;
			for(j=1;j<=n;j++)
			{	k=(m+i-y[j-1])/2;
				if(k<0 || k>m || (m+i-y[j-1])%2)
				{	s1=0;
					break;
				}
				else
					s1=(ll)s1*comb(m,k)%mod;
			}
			s=(s+s1)%mod;
		}
		ans=(ll)ans*s%mod;
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {3,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 1; verify_case(0, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 0; verify_case(1, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {0,2,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 4; verify_case(2, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {7,8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {8,7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 2; verify_case(3, Arg3, calc(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {-2,-2,-2,0,0,0,2,2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-2,0,2,-2,0,2,-2,0,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1000; int Arg3 = 387540818; verify_case(4, Arg3, calc(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	WolfPack ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
