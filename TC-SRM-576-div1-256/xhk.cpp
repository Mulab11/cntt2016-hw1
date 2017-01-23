// BEGIN CUT HERE

// END CUT HERE
#line 5 "ArcadeManao.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m,sx,sy;
int a[110][110],fa[10010];

int id(int x,int y)
{return (x-1)*m+y;
}

int find(int i)
{return fa[i]==i?i:fa[i]=find(fa[i]);
}

class ArcadeManao
{	public:
	int shortestLadder(vector <string> level, int coinRow, int coinColumn)
	{	int i,j,p,fx,fy;
		
		n=level.size();
		m=level[0].length();
		sx=coinRow;
		sy=coinColumn;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				a[i][j]=(level[i-1][j-1]=='X'?1:0);
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				fa[id(i,j)]=id(i,j);
		for(i=1;i<=n;i++)
			for(j=1;j<m;j++)
				if(a[i][j] && a[i][j+1])
				{	fx=find(id(i,j));
					fy=find(id(i,j+1));
					if(fx!=fy)
						fa[fx]=fy;
				}
		for(p=1;p<=n;p++)
		{	if(find(id(n,1))==find(id(sx,sy))) return p-1;
			for(j=1;j<=m;j++)
				for(i=1;i+p<=n;i++)
				{	if(!a[i][j] || !a[i+p][j]) continue;
					fx=find(id(i,j));
					fy=find(id(i+p,j));
					if(fx!=fy) fa[fx]=fy;
				}
		}
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"XXXX....",
 "...X.XXX",
 "XXX..X..",
 "......X.",
 "XXXXXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 4; int Arg3 = 2; verify_case(0, Arg3, shortestLadder(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"XXXX",
 "...X",
 "XXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 1; verify_case(1, Arg3, shortestLadder(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"..X..",
 ".X.X.",
 "X...X",
 ".X.X.",
 "..X..",
 "XXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 3; int Arg3 = 4; verify_case(2, Arg3, shortestLadder(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"X"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 0; verify_case(3, Arg3, shortestLadder(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"XXXXXXXXXX",
 "...X......",
 "XXX.......",
 "X.....XXXX",
 "..XXXXX..X",
 ".........X",
 ".........X",
 "XXXXXXXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 2; verify_case(4, Arg3, shortestLadder(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	ArcadeManao ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
