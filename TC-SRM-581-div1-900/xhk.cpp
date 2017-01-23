// BEGIN CUT HERE

// END CUT HERE
#line 5 "YetAnotherBoardGame.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m,ans;
int a[20][20],b[20],c[20];

void trans(int i,int j,int flag)
{a[i-1][j]^=1;
 a[i+1][j]^=1;
 a[i][j-1]^=1;
 a[i][j+1]^=1;
 if(flag==2) a[i][j]^=1;
}

void dfs(int i,int j,int s)
{int k,t;
 
 if(i==n+1)
 {	if(a[n][m] || (m>1 && a[n][m-1])) return;
 	if(ans==-1 || s<ans)
 		ans=s;
 	return;
 }
 if(i==n && j>2 && a[i][j-2]) return;
 if(i==1 || !a[i-1][j])
 {	if(j==m)
 		dfs(i+1,1,s);
 	else
	 	dfs(i,j+1,s);
 }
 if(i!=1 && !a[i-1][j]) return;
 if(b[i]+c[j]==3) return;
 if(b[i])
 {	trans(i,j,b[i]);
 	t=c[j];
	c[j]=b[i];
 	if(j==m)
 		dfs(i+1,1,s+1);
 	else
 		dfs(i,j+1,s+1);
 	trans(i,j,b[i]);
 	c[j]=t;
 }
 else if(c[j])
 {	trans(i,j,c[j]);
 	t=b[i];
 	b[i]=c[j];
 	if(j==m)
 		dfs(i+1,1,s+1);
 	else
 		dfs(i,j+1,s+1);
 	trans(i,j,c[j]);
 	b[i]=t;
 }
 else
 {	trans(i,j,1);
 	b[i]=c[j]=1;
	if(j==m)
 		dfs(i+1,1,s+1);
 	else
 		dfs(i,j+1,s+1);
 	trans(i,j,1);	
 	b[i]=c[j]=0;
 	
 	trans(i,j,2);
 	b[i]=c[j]=2;
	if(j==m)
 		dfs(i+1,1,s+1);
 	else
 		dfs(i,j+1,s+1);
 	trans(i,j,2);	
 	b[i]=c[j]=0;
 }
}
 
class YetAnotherBoardGame
{	public:
	int minimumMoves(vector <string> board)
	{	int i,j;
		
		n=board.size();
		m=board[0].length();
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				a[i][j]=board[i-1][j-1]=='W'?1:0;			
		ans=-1;		
		memset(b,0,sizeof(b));
		memset(c,0,sizeof(c));
		dfs(1,1,0);
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"BBBBBBBBB",
 "BBWBBBBBB",
 "BWWWBBBBB",
 "BBWBBBWBB",
 "BBBBBWBWB",
 "BBBBBBWBB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, minimumMoves(Arg0)); }
	void test_case_1() { string Arr0[] = {"BBW",
 "WWW",
 "BWW"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, minimumMoves(Arg0)); }
	void test_case_2() { string Arr0[] = {"WBW",
 "BBW",
 "WBW"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(2, Arg1, minimumMoves(Arg0)); }
	void test_case_3() { string Arr0[] = {"BBBB",
 "WBWB",
 "BBBB",
 "BBBB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(3, Arg1, minimumMoves(Arg0)); }
	void test_case_4() { string Arr0[] = {"WWWWWBW",
 "WBWBWBW",
 "BBWBBWW"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(4, Arg1, minimumMoves(Arg0)); }
	void test_case_5() { string Arr0[] = {"WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 30; verify_case(5, Arg1, minimumMoves(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	YetAnotherBoardGame ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
