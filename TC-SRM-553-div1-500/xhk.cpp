// BEGIN CUT HERE

// END CUT HERE
#line 5 "TwoConvexShapes.cpp"
#include<bits/stdc++.h>
using namespace std;

const int mod=1000000007;
int n,m,ans;
int a[110][110],g1[110][110],g2[110][110],f[110][110];

void update(int &i,int x)
{i=(i+x)-(i+x>=mod?mod:0);
}

int work()
{int i,j,s,ret=0;
 
 for(i=1;i<=n;i++)
 	for(j=1;j<=m;j++)
 	{	g1[i][j]=g1[i][j-1]+(a[i][j]==1);
 		g2[i][j]=g2[i][j-1]+(a[i][j]==2);
 	}
 memset(f,0,sizeof(f));
 f[0][0]=1;
 for(i=1;i<=n;i++)
 {	s=0;
 	for(j=0;j<=m;j++)
 	{	update(s,f[i-1][j]);
	 	if(g2[i][j]==0 && g1[i][m]-g1[i][j]==0)
		 	f[i][j]=s;
	}
 }
 for(i=0;i<=m;i++)
 	update(ret,f[n][i]);
 return ret;
}
 	
class TwoConvexShapes
{	public:
	int countWays(vector <string> grid)
	{	int i,j,s1,s2,s3,s4,ss1,ss2;
	 
	 	n=grid.size();
	 	m=grid[0].length();
	 	for(i=1;i<=n;i++)
	 		for(j=1;j<=m;j++)
	 			if(grid[i-1][j-1]=='?')
	 				a[i][j]=0;
	 			else if(grid[i-1][j-1]=='B')
	 				a[i][j]=1;
	 			else
	 				a[i][j]=2;					
		ans=0;
		update(ans,work());
	 	for(i=1;i<=n;i++)
		 	for(j=1;j<=m;j++)
			 	if(a[i][j]) a[i][j]=3-a[i][j];
		update(ans,work());
		for(i=1;i<=n;i++)
			for(j=1;j<=m/2;j++)
				swap(a[i][j],a[i][m+1-j]);
		update(ans,work());
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				if(a[i][j]) a[i][j]=3-a[i][j];			
		update(ans,work());
		//cout<<ans<<endl;
		ss1=0;
		ss2=0;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				if(a[i][j]==1)
					ss1++;
				else if(a[i][j]==2)
					ss2++;
		s1=0;
		s2=0;			
		s3=ss1;
		s4=ss2;			
		for(j=0;j<=m;j++)
		{	for(i=1;i<=n;i++)
				if(a[i][j]==1)
				{	s1++;
					s3--;
				}
				else if(a[i][j]==2)
				{	s2++;
					s4--;
				}
			if(s2==0 && s3==0) ans--;
			if(s1==0 && s4==0) ans--;
		}
		s1=0;
		s2=0;
		s3=ss1;
		s4=ss2;
		for(i=0;i<=n;i++)
		{	for(j=1;j<=m;j++)
				if(a[i][j]==1)
				{	s1++;
					s3--;
				}
				else if(a[i][j]==2)
				{	s2++;
					s4--;
				}
			if(s2==0 && s3==0) ans--;
			if(s1==0 && s4==0) ans--;
		}
		if(ss1==0) ans++;
		if(ss2==0) ans++;
		ans=(ans%mod+mod)%mod;
		return ans;	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"??",
 "??"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 14; verify_case(0, Arg1, countWays(Arg0)); }
	void test_case_1() { string Arr0[] = {"B?",
 "??"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(1, Arg1, countWays(Arg0)); }
	void test_case_2() { string Arr0[] = {"WWB",
 "WWW",
 "WWW",
 "WWW"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, countWays(Arg0)); }
	void test_case_3() { string Arr0[] = {"BBBBBB",
 "WWBBBB",
 "WBBBBB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(3, Arg1, countWays(Arg0)); }
	void test_case_4() { string Arr0[] = {"?BB?",
 "BBBB",
 "?BB?"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(4, Arg1, countWays(Arg0)); }
	void test_case_5() { string Arr0[] = {"?WWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
 "B?WWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
 "BB?WWWWWWWWWWWWWWWWWWWWWWWWWWWW",
 "BBB?WWWWWWWWWWWWWWWWWWWWWWWWWWW",
 "BBBB?WWWWWWWWWWWWWWWWWWWWWWWWWW",
 "BBBBB?WWWWWWWWWWWWWWWWWWWWWWWWW",
 "BBBBBB?WWWWWWWWWWWWWWWWWWWWWWWW",
 "BBBBBBB?WWWWWWWWWWWWWWWWWWWWWWW",
 "BBBBBBBB?WWWWWWWWWWWWWWWWWWWWWW",
 "BBBBBBBBB?WWWWWWWWWWWWWWWWWWWWW",
 "BBBBBBBBBB?WWWWWWWWWWWWWWWWWWWW",
 "BBBBBBBBBBB?WWWWWWWWWWWWWWWWWWW",
 "BBBBBBBBBBBB?WWWWWWWWWWWWWWWWWW",
 "BBBBBBBBBBBBB?WWWWWWWWWWWWWWWWW",
 "BBBBBBBBBBBBBB?WWWWWWWWWWWWWWWW",
 "BBBBBBBBBBBBBBB?WWWWWWWWWWWWWWW",
 "BBBBBBBBBBBBBBBB?WWWWWWWWWWWWWW",
 "BBBBBBBBBBBBBBBBB?WWWWWWWWWWWWW",
 "BBBBBBBBBBBBBBBBBB?WWWWWWWWWWWW",
 "BBBBBBBBBBBBBBBBBBB?WWWWWWWWWWW",
 "BBBBBBBBBBBBBBBBBBBB?WWWWWWWWWW",
 "BBBBBBBBBBBBBBBBBBBBB?WWWWWWWWW",
 "BBBBBBBBBBBBBBBBBBBBBB?WWWWWWWW",
 "BBBBBBBBBBBBBBBBBBBBBBB?WWWWWWW",
 "BBBBBBBBBBBBBBBBBBBBBBBB?WWWWWW",
 "BBBBBBBBBBBBBBBBBBBBBBBBB?WWWWW",
 "BBBBBBBBBBBBBBBBBBBBBBBBBB?WWWW",
 "BBBBBBBBBBBBBBBBBBBBBBBBBBB?WWW",
 "BBBBBBBBBBBBBBBBBBBBBBBBBBBB?WW",
 "BBBBBBBBBBBBBBBBBBBBBBBBBBBBB?W"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 73741817; verify_case(5, Arg1, countWays(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	TwoConvexShapes ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
