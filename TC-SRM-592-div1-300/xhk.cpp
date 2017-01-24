// BEGIN CUT HERE

// END CUT HERE
#line 5 "LittleElephantAndBalls.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,ans;
int a[110],c1[10],c2[10];

class LittleElephantAndBalls
{	public:
	int getNumber(string S)
	{	int i,j,s;
		
		n=S.length();
		for(i=1;i<=n;i++) //格式转换 
			if(S[i-1]=='R')
				a[i]=1;
			else if(S[i-1]=='B')
				a[i]=2;
			else
				a[i]=3;
		memset(c1,0,sizeof(c1));
		memset(c2,0,sizeof(c2));		
		s=0;
		ans=0;
		for(i=1;i<=n;i++) //每次都放在中间，决定这个球去左/右 
		{	ans+=s;
			if(!c1[a[i]]) //贪心选择放两边 
			{	c1[a[i]]=1;
				s++;
			}
			else if(!c2[a[i]])
			{	c2[a[i]]=1;
				s++;
			}
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "RGB"; int Arg1 = 3; verify_case(0, Arg1, getNumber(Arg0)); }
	void test_case_1() { string Arg0 = "RGGRBBB"; int Arg1 = 21; verify_case(1, Arg1, getNumber(Arg0)); }
	void test_case_2() { string Arg0 = "RRRGBRR"; int Arg1 = 16; verify_case(2, Arg1, getNumber(Arg0)); }
	void test_case_3() { string Arg0 = "RRRR"; int Arg1 = 5; verify_case(3, Arg1, getNumber(Arg0)); }
	void test_case_4() { string Arg0 = "GGRRRGR"; int Arg1 = 18; verify_case(4, Arg1, getNumber(Arg0)); }
	void test_case_5() { string Arg0 = "G"; int Arg1 = 0; verify_case(5, Arg1, getNumber(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	LittleElephantAndBalls ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
