// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndFlowerShopDivOne.cpp"
#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> PI;

struct unit
{int x1,x2,y1,y2,d,s;
};

int n,m,lim,ans;
int g[40][40],s1[40][40],s2[40][40];
PI q[1000010];
vector<unit> a;
vector<PI> b,c;

bool operator <(unit A,unit B)
{return A.d<B.d;
}

void work()
{int i,j,k,t,w;

 if(b.empty() || c.empty()) return;
 t=1;
 w=0;
 k=b.size()-1;
 for(i=0;i<c.size();i++)
 {	while(k>=0 && b[k].first+c[i].first>=-lim)
 	{	while(w>=t && q[w].second<b[k].second) w--;
	 	q[++w]=b[k];
	 	k--;
	}
 	while(t<=w && q[t].first+c[i].first>lim) t++;
 	if(t<=w) ans=max(ans,q[t].second+c[i].second);
 }
}

class FoxAndFlowerShopDivOne
{	public:
	int theMaxFlowers(vector <string> flowers, int maxDiff)
	{	int i,j,i1,j1,x,y;
	
		lim=maxDiff;
		n=flowers.size();
		m=flowers[0].length();
		memset(g,0,sizeof(g));
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				if(flowers[i-1][j-1]=='L')
					g[i][j]=1;
				else if(flowers[i-1][j-1]=='P')
					g[i][j]=2;			
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
			{	s1[i][j]=s1[i-1][j]+s1[i][j-1]-s1[i-1][j-1]+(g[i][j]==1);
				s2[i][j]=s2[i-1][j]+s2[i][j-1]-s2[i-1][j-1]+(g[i][j]==2);
			}
		a.clear();	
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				for(i1=i;i1<=n;i1++)
					for(j1=j;j1<=m;j1++)
					{	x=s1[i1][j1]-s1[i1][j-1]-s1[i-1][j1]+s1[i-1][j-1];
						y=s2[i1][j1]-s2[i1][j-1]-s2[i-1][j1]+s2[i-1][j-1];
						a.push_back((unit){i,i1,j,j1,x-y,x+y});
					}
		sort(a.begin(),a.end());			
		ans=-1;
		for(i=1;i<=n;i++)
		{	b.clear();
			c.clear();
			for(j=0;j<a.size();j++)
				if(a[j].x1>=i)
					b.push_back(make_pair(a[j].d,a[j].s));
				else if(a[j].x2<i)
					c.push_back(make_pair(a[j].d,a[j].s));
			//cout<<"JJ"<<endl;		
			work();
			//cout<<"Gg"<<endl;
		}
		for(i=1;i<=m;i++)
		{	b.clear();
			c.clear();
			for(j=0;j<a.size();j++)
				if(a[j].y1>=i)
					b.push_back(make_pair(a[j].d,a[j].s));
				else if(a[j].y2<i)
					c.push_back(make_pair(a[j].d,a[j].s));
			work();
		}
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
{	FoxAndFlowerShopDivOne ___test;
	___test.run_test(-1);
	//cout<<___test.theMaxFlowers({"LP","LL"},2)<<endl;
	return 0;
}
// END CUT HERE
