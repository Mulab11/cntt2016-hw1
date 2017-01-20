// BEGIN CUT HERE

// END CUT HERE
#line 5 "XorBoard.cpp"
#include<bits/stdc++.h>
#define mo 555555555ll
using namespace std;
long long c[1610][1610],f[1610][1610],sumf[1610];
class XorBoard
{
        public:
        int count(int n, int m, int nc, int mc, int s)
        {
        	//cout<<n<<' '<<m<<' '<<nc<<' '<<mc<<' '<<s<<endl;
        	memset(sumf,0,sizeof(sumf));
        	c[0][0]=1;
        	for (int i=1;i<=1600;i++)
        	{
        		c[i][0]=1;
        		for (int j=1;j<=i;j++) c[i][j]=(c[i-1][j]+c[i-1][j-1])%mo;
        	}
        	
        	f[0][0]=1;sumf[0]=1;
        	for (int i=0;i<=1600;i++)
        	for (int j=1;j<=1600;j++)
        	{
        		f[i][j]=sumf[j-1];
        		sumf[j]=(sumf[j]+f[i][j])%mo;
        		//if ((i+j<=1600)&&(f[i][j]!=c[i+j-1][j-1])) cout<<"HAHA";
        	}
        	
        	long long ans=0;
			for (int i=0;i<=min(nc,n);i++)
			for (int j=0;j<=min(mc,m);j++)
			{
				if ((nc-i)&1) continue;
				if ((mc-j)&1) continue;
				int p=i*m+j*n-2*i*j;
				if (p!=s) continue;
				//cout<<i<<' '<<j<<' '<<c[n][i]*c[m][j]%mo*f[(nc-i)>>1][nc]%mo*f[(mc-j)>>1][mc]%mo<<endl;
				ans=(ans+c[n][i]*c[m][j]%mo*f[(nc-i)>>1][n]%mo*f[(mc-j)>>1][m]%mo)%mo;
			}
			return (int)ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; int Arg3 = 2; int Arg4 = 4; int Arg5 = 4; verify_case(0, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 0; int Arg3 = 0; int Arg4 = 1; int Arg5 = 0; verify_case(1, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 20; int Arg2 = 50; int Arg3 = 40; int Arg4 = 200; int Arg5 = 333759825; verify_case(2, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arg0 = 1200; int Arg1 = 1000; int Arg2 = 800; int Arg3 = 600; int Arg4 = 4000; int Arg5 = 96859710; verify_case(3, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { int Arg0 = 555; int Arg1 = 555; int Arg2 = 555; int Arg3 = 555; int Arg4 = 5550; int Arg5 = 549361755; verify_case(4, Arg5, count(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        XorBoard ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
