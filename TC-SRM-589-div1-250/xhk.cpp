// BEGIN CUT HERE

// END CUT HERE
#line 5 "GooseTattarrattatDiv1.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,ans;
int fa[60],f[60],g[60];
char a[60];

int find(int i) //并查集 
{return fa[i]==i?i:fa[i]=find(fa[i]);
}

class GooseTattarrattatDiv1
{	public:
	int getmin(string S)
	{	int i,j,fx,fy;
		
		n=S.length();
		for(i=1;i<=n;i++) a[i]=S[i-1];
		for(i=1;i<=26;i++) fa[i]=i;
		for(i=1;i<=n/2;i++) //对应的字母要相同，并查集合并 
		{	fx=find(a[i]-96);
			fy=find(a[n+1-i]-96);
			if(fx!=fy)
				fa[fx]=fy;
		}
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		ans=n;
		for(i=1;i<=n;i++) f[a[i]-96]++;
		for(i=1;i<=26;i++) //每个集合选择出现次数最多的那个字母不动，剩下的都变成那个字母 
		{	fx=find(i);
			g[fx]=max(g[fx],f[i]);
		}
		for(i=1;i<=26;i++) ans-=g[i];
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "geese"; int Arg1 = 2; verify_case(0, Arg1, getmin(Arg0)); }
	void test_case_1() { string Arg0 = "tattarrattat"; int Arg1 = 0; verify_case(1, Arg1, getmin(Arg0)); }
	void test_case_2() { string Arg0 = "xyyzzzxxx"; int Arg1 = 2; verify_case(2, Arg1, getmin(Arg0)); }
	void test_case_3() { string Arg0 = "xrepayuyubctwtykrauccnquqfuqvccuaakylwlcjuyhyammag"; int Arg1 = 11; verify_case(3, Arg1, getmin(Arg0)); }
	void test_case_4() { string Arg0 = "abaabb"; int Arg1 = 3; verify_case(4, Arg1, getmin(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	GooseTattarrattatDiv1 ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
