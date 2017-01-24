// BEGIN CUT HERE

// END CUT HERE
#line 5 "HexagonalBoard.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m,flag;
int a[110][110],used[110][110],col[5],v[6][2]={0,1,0,-1,1,0,-1,0,-1,1,1,-1};

void dfs(int i,int j,int p)
{int k,x,y;
 
 used[i][j]=p;
 col[p]=1;
 for(k=0;k<6;k++)
 {	x=i+v[k][0];
 	y=j+v[k][1];
 	if(x>0 && x<=n && y>0 && y<=m && a[x][y])
 	{	if(used[x][y]!=-1) //已来过 
 		{	if(used[x][y]==p) //有奇环 
 			{	flag=0;
 				break;
 			}
 		}
 		else
 			dfs(x,y,p^1);
 	}
 }
}

class HexagonalBoard
{	public:
	int minColors(vector <string> board)
	{	int i,j;
		
		n=board.size();
		m=board[0].length();
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				a[i][j]=(board[i-1][j-1]=='X');
		memset(used,-1,sizeof(used));		
		memset(col,0,sizeof(col));
		flag=1;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++) //染色 
				if(a[i][j] && used[i][j]==-1)
					dfs(i,j,0);
		if(!col[0] && !col[1]) return 0;			
		if(!flag) return 3;
		if(!col[1]) return 1;
		return 2;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"---",
 "---",
 "---"}
 ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, minColors(Arg0)); }
	void test_case_1() { string Arr0[] = {"-X--",
 "---X",
 "----",
 "-X--"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, minColors(Arg0)); }
	void test_case_2() { string Arr0[] = {"XXXX",
 "---X",
 "---X",
 "---X"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, minColors(Arg0)); }
	void test_case_3() { string Arr0[] = {"XX-XX--"
,"-XX-XXX"
,"X-XX--X"
,"X--X-X-"
,"XX-X-XX"
,"-X-XX-X"
,"-XX-XX-"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(3, Arg1, minColors(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	HexagonalBoard ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
