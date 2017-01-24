// BEGIN CUT HERE

// END CUT HERE
#line 5 "LittleElephantAndString.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,ans;
int a[110];

class LittleElephantAndString
{	public:
	int getNumber(string A, string B)
	{	int i,j;
		
		memset(a,0,sizeof(a));
		for(i=0;i<A.length();i++) a[A[i]-64]++,a[B[i]-64]--; //判断是否无解 
		for(i=1;i<=26;i++)
			if(a[i]) return -1;
		ans=A.length();
		j=B.length()-1;
		for(i=A.length()-1;i>=0;i--) //找出a里面包含b串倒数连续的最长一段的子序列不动，剩下的都要移动 
			if(A[i]==B[j])
			{	ans--;
				j--;
			}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "ABC"; string Arg1 = "CBA"; int Arg2 = 2; verify_case(0, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "A"; string Arg1 = "B"; int Arg2 = -1; verify_case(1, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "AAABBB"; string Arg1 = "BBBAAA"; int Arg2 = 3; verify_case(2, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; string Arg1 = "ZYXWVUTSRQPONMLKJIHGFEDCBA"; int Arg2 = 25; verify_case(3, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "A"; string Arg1 = "A"; int Arg2 = 0; verify_case(4, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_5() { string Arg0 = "DCABA"; string Arg1 = "DACBA"; int Arg2 = 2; verify_case(5, Arg2, getNumber(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	LittleElephantAndString ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
