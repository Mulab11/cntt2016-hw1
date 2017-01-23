// BEGIN CUT HERE

// END CUT HERE
#line 5 "TPS.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=0x3f3f3f3f;
int n,ans;
int f[60][60],ga[60][60];

int dfs(int i,int fa)
{int j,s=0,flag=0;
 
 if(f[i][fa]!=inf) return f[i][fa];
 f[i][fa]=0;
 for(j=1;j<=n;j++)
 	if(j!=fa && ga[i][j])
 	{	f[i][fa]+=max(1,dfs(j,i));
 		if(f[j][i]==0) flag=1;
 	}
 f[i][fa]-=flag;
 return f[i][fa];
}

class TPS
{	public:
	int minimalBeacons(vector <string> linked)
	{	int i,j;
		
		n=linked.size();
		if(n==1) return 0;
		ans=n;
		memset(f,0x3f,sizeof(f));
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				ga[i][j]=(linked[i-1][j-1]=='Y');
		for(i=1;i<=n;i++)
		{	dfs(i,0);
			ans=min(ans,f[i][0]+1);
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"NYNN",
 "YNYN",
 "NYNY",
 "NNYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, minimalBeacons(Arg0)); }
	void test_case_1() { string Arr0[] = {"NYYY",
 "YNNN",
 "YNNN",
 "YNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, minimalBeacons(Arg0)); }
	void test_case_2() { string Arr0[] = {"NNYNNNNNNN",
 "NNNNNYNNNN",
 "YNNYNNYNNN",
 "NNYNYNNYNN",
 "NNNYNYNNYN",
 "NYNNYNNNNY",
 "NNYNNNNNNN",
 "NNNYNNNNNN",
 "NNNNYNNNNN",
 "NNNNNYNNNN"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, minimalBeacons(Arg0)); }
	void test_case_3() { string Arr0[] = {"NYNYNNYNN",
 "YNYNYNNYN",
 "NYNNNYNNY",
 "YNNNNNNNN",
 "NYNNNNNNN",
 "NNYNNNNNN",
 "YNNNNNNNN",
 "NYNNNNNNN",
 "NNYNNNNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(3, Arg1, minimalBeacons(Arg0)); }
	void test_case_4() { string Arr0[] = {"NYYYYYYYYY",
 "YNNNNNNNNN",
 "YNNNNNNNNN",
 "YNNNNNNNNN",
 "YNNNNNNNNN",
 "YNNNNNNNNN",
 "YNNNNNNNNN",
 "YNNNNNNNNN",
 "YNNNNNNNNN",
 "YNNNNNNNNN"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(4, Arg1, minimalBeacons(Arg0)); }
	void test_case_5() { string Arr0[] = {"N"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(5, Arg1, minimalBeacons(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	TPS ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
