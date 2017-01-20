// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndFlowerShopDivOne.cpp"
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
using namespace std;
int a[55][55],sum[55][55],js[55][55],f[55][2010],g[55][2010],n,m;
int work(int mx)
{
	for (int i=1;i<=n;i++)
	for (int j=1;j<=m;j++)
	{
		sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
		js[i][j]=js[i-1][j]+js[i][j-1]-js[i-1][j-1]+(a[i][j]!=0);
	}
	
	memset(f,234,sizeof(f));
	for (int i=1;i<=n;i++)
	{
		for (int l=1;l<=m;l++)
		for (int r=l;r<=m;r++)
		for (int d=1;d<=i;d++)
		{
			int s=sum[i][r]-sum[i][l-1]-sum[d-1][r]+sum[d-1][l-1],num=js[i][r]-js[i][l-1]-js[d-1][r]+js[d-1][l-1];
			f[i][s+1000]=max(f[i][s+1000],num);
		}
	}
	for (int i=1;i<=n;i++)
	for (int j=1;j<=2000;j++)
		f[i][j]=max(f[i][j],f[i-1][j]);
	
	memset(g,234,sizeof(g));
	for (int i=1;i<=n;i++)
	{
		for (int l=1;l<=m;l++)
		for (int r=l;r<=m;r++)
		for (int d=i;d<=n;d++)
		{
			int s=sum[d][r]-sum[d][l-1]-sum[i-1][r]+sum[i-1][l-1],num=js[d][r]-js[d][l-1]-js[i-1][r]+js[i-1][l-1];
			g[i][s+1000]=max(g[i][s+1000],num);
		}
	}
	for (int i=n;i>=1;i--)
	for (int j=1;j<=2000;j++)
		g[i][j]=max(g[i][j],g[i+1][j]);
		
	int ans=-1;
	for (int i=1;i<n;i++)
	for (int j=1;j<=2000;j++)
	for (int k=1;k<=2000;k++)
	{
		if ((j+k<=2000+mx)&&(j+k>=2000-mx)) ans=max(ans,f[i][j]+g[i+1][k]);
	}
	return ans;
}
		
class FoxAndFlowerShopDivOne
{
        public:
        int theMaxFlowers(vector <string> board, int mx)
        {
			n=board.size();m=board[0].size();
			for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
			{
				if (board[i-1][j-1]=='.') a[i][j]=0;
				else if (board[i-1][j-1]=='L') a[i][j]=1;
				else a[i][j]=-1;
			}
			int ans=work(mx);
			for (int i=1;i<=n;i++)
			for (int j=1;j<=m;j++)
			{
				if (board[i-1][j-1]=='.') a[j][i]=0;
				else if (board[i-1][j-1]=='L') a[j][i]=1;
				else a[j][i]=-1;
			}
			swap(n,m);
			ans=max(ans,work(mx));
			return ans;
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"LLL",
 "PPP",
 "LLL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 7; verify_case(0, Arg2, theMaxFlowers(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"LLL",
 "PPP",
 "LLL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 6; verify_case(1, Arg2, theMaxFlowers(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"...",
 "...",
 "..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 0; verify_case(2, Arg2, theMaxFlowers(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"LLPL.LPP",
 "PLPPPPLL",
 "L.P.PLLL",
 "LPL.PP.L",
 ".LLL.P.L",
 "PPLP..PL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 38; verify_case(3, Arg2, theMaxFlowers(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"LLLLLLLLLL",
 "LLLLLLLLLL",
 "LLLLLLLLLL",
 "LLLLLLLLLL",
 "LLLLLLLLLL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = -1; verify_case(4, Arg2, theMaxFlowers(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"LLLP..LLP.PLL.LL..LP",
 "L.PL.L.LLLL.LPLLPLP.",
 "PLL.LL.LLL..PL...L..",
 ".LPPP.PPPLLLLPLP..PP",
 "LP.P.PPL.L...P.L.LLL",
 "L..LPLPP.PP...PPPL..",
 "PP.PLLL.LL...LP..LP.",
 "PL...P.PPPL..PLP.L..",
 "P.PPPLPLP.LL.L.LLLPL",
 "PLLPLLP.LLL.P..P.LPL",
 "..LLLPLPPPLP.P.LP.LL",
 "..LP..L..LLPPP.LL.LP",
 "LPLL.PLLPPLP...LL..P",
 "LL.....PLL.PLL.P....",
 "LLL...LPPPPL.PL...PP",
 ".PLPLLLLP.LPP...L...",
 "LL...L.LL.LLLPLPPPP.",
 "PLPLLLL..LP.LLPLLLL.",
 "PP.PLL..L..LLLPPL..P",
 ".LLPL.P.PP.P.L.PLPLL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; int Arg2 = 208; verify_case(5, Arg2, theMaxFlowers(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        FoxAndFlowerShopDivOne ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
