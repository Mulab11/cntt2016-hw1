// BEGIN CUT HERE

// END CUT HERE
#line 5 "StringPath.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=1000000009;
int n,m,l,ans;
int f[9][9][70010];
char a[110],b[110];

void update(int &i,int x) //更新答案 
{i=(i+x);
 if(i>=mod) i-=mod;
}

class StringPath
{	public:
	int countBoards(int N, int M, string A, string B)
	{	int i,j,k,x,y,sta;
		
		n=N;
		m=M;
		l=n+m-1;
		for(i=1;i<=l;i++) a[i]=A[i-1],b[i]=B[i-1];
		memset(f,0,sizeof(f));
		f[1][0][0]=1;
		for(i=1;i<=n;i++) //f[i][j][k]表示当前看到(i,j)最近m个位置的状态 
			for(j=0;j<=m;j++)
			{	if(j==0 && i!=1) continue;
				if(i==n && j==m) continue;
				x=i;
				y=j;
				if(y==m)
				{	x++;
					y=1;
				}
				else
					y++;
				for(k=0;k<(1<<(2*m));k++)
				{	if(!f[i][j][k]) continue;
					sta=(k&3);
					if(y!=1 || x==1) sta|=(k>>(2*m-2));	//判断(x,y)这一位是否可行(先不考虑(x,y)这个字符) 
					if(i==1 && j==0) sta=3; //特判初始情况 
					if(a[x+y-1]==b[x+y-1]) //分成a,b当前为是否一样讨论 
					{	update(f[x][y][(k>>2)+((sta&3)<<(2*m-2))],f[i][j][k]);
						update(f[x][y][(k>>2)],(ll)f[i][j][k]*25%mod);
					}
					else
					{	update(f[x][y][(k>>2)+((sta&1)<<(2*m-2))],f[i][j][k]);
						update(f[x][y][(k>>2)+((sta&2)<<(2*m-2))],f[i][j][k]);
						update(f[x][y][(k>>2)],(ll)f[i][j][k]*24%mod);
					}
				}
			}	
		ans=0;	
		for(k=0;k<(1<<(2*m-2));k++)
			update(ans,f[n][m][(3<<(2*m-2))+k]);
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; string Arg2 = "ABC"; string Arg3 = "ADC"; int Arg4 = 2; verify_case(0, Arg4, countBoards(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 2; string Arg2 = "ABC"; string Arg3 = "ABD"; int Arg4 = 0; verify_case(1, Arg4, countBoards(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 4; string Arg2 = "ABCDDE"; string Arg3 = "ACCBDE"; int Arg4 = 1899302; verify_case(2, Arg4, countBoards(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 8; int Arg1 = 8; string Arg2 = "ZZZZZZZZZZZZZZZ"; string Arg3 = "ZABCDEFGHIJKLMZ"; int Arg4 = 120390576; verify_case(3, Arg4, countBoards(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	StringPath ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
