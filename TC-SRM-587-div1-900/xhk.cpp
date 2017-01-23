// BEGIN CUT HERE

// END CUT HERE
#line 5 "ThreeColorability.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m,flag;
int fa[60],used[60];
char a[110][110];
vector<string> ans;

void dfs(int i,int col) //二分图染色 
{int j,k;
 
 if(used[i]==-1)
 	used[i]=col;
 else if(used[i]!=col)
	flag=0;
 else
 	return;
 if(!flag) return;
 for(j=1;j<=m;j++)
 {	if(a[i][j]=='?') continue;
 	for(k=1;k<=n;k++)
 		if(k!=i && a[k][j]!='?')
 		{	if(a[i][j]==a[k][j])
 				dfs(k,col);
 			else
 				dfs(k,col^1);
 		}
 }
}

int check() //判断当前局面有没有合法解 
{int i,j;
 
 memset(used,-1,sizeof(used));
 flag=1;
 for(i=1;i<=n;i++)
 	if(used[i]==-1) dfs(i,0);
 return flag;
}

class ThreeColorability
{	public:
	vector <string> lexSmallest(vector <string> cells)
	{	int i,j;
		string s;
		
		n=cells.size();
		m=cells[0].length();
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				a[i][j]=cells[i-1][j-1];
		ans.clear();
		if(!check()) return ans;
		for(i=1;i<=n;i++) //逐位确定 
			for(j=1;j<=m;j++)
				if(a[i][j]=='?')
				{	a[i][j]='N';
					if(!check()) a[i][j]='Z';
				}
		for(i=1;i<=n;i++)
		{	s="";
			for(j=1;j<=m;j++)
				s+=a[i][j];
			ans.push_back(s);
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"Z"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"Z" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, lexSmallest(Arg0)); }
	void test_case_1() { string Arr0[] = {"??", "?N"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NN", "NN" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, lexSmallest(Arg0)); }
	void test_case_2() { string Arr0[] = {"ZZZ", "ZNZ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, lexSmallest(Arg0)); }
	void test_case_3() { string Arr0[] = {"N?N??NN","??ZN??Z","NN???Z?","ZZZ?Z??","Z???NN?","N?????N","ZZ?N?NN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, lexSmallest(Arg0)); }
	void test_case_4() { string Arr0[] = {"ZZZZ","ZZZZ","ZZZZ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"ZZZZ", "ZZZZ", "ZZZZ" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, lexSmallest(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	ThreeColorability ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
