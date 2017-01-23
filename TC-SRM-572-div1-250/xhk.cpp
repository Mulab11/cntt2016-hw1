// BEGIN CUT HERE

// END CUT HERE
#line 5 "NewArenaPassword.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m,ans;
int fa[110],c[110];
char a[110];

int find(int i)
{return fa[i]==i?i:fa[i]=find(fa[i]);
}

class NewArenaPassword
{	public:
	int minChange(string oldPassword, int K)
	{	int i,j,ma,fx,fy;
		
		n=oldPassword.length();
		m=K;
		for(i=1;i<=n;i++)
			a[i]=oldPassword[i-1];
		for(i=1;i<=n;i++) fa[i]=i;
		for(i=1;i<=m;i++)
		{	fx=find(i);
			fy=find(n-m+i);
			if(fx!=fy)
				fa[fx]=fy;
		}
		ans=0;
		for(i=1;i<=n;i++)
		{	if(find(i)!=i) continue;
			memset(c,0,sizeof(c));
			for(j=1;j<=n;j++)	
			{	if(find(j)!=i) continue;
				c[a[j]-96]++;
				ans++;
			}
			ma=0;
			for(j=1;j<=26;j++)
				ma=max(ma,c[j]);
			ans-=ma;
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "topcoderopen"; int Arg1 = 5; int Arg2 = 3; verify_case(0, Arg2, minChange(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "puyopuyo"; int Arg1 = 4; int Arg2 = 0; verify_case(1, Arg2, minChange(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "loool"; int Arg1 = 3; int Arg2 = 1; verify_case(2, Arg2, minChange(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "arena"; int Arg1 = 5; int Arg2 = 0; verify_case(3, Arg2, minChange(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "amavckdkz"; int Arg1 = 7; int Arg2 = 5; verify_case(4, Arg2, minChange(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	NewArenaPassword ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
