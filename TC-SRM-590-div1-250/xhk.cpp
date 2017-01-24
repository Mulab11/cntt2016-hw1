// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndChess.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,N,M;
int a[110],b[110];

class FoxAndChess
{	public:
	string ableToMove(string begin, string target)
	{	int i,j;
		
		n=begin.length();
		N=M=0;
		for(i=1;i<=n;i++)
			if(begin[i-1]!='.') a[++N]=i-1; //提取非空位 
		for(i=1;i<=n;i++)
			if(target[i-1]!='.') b[++M]=i-1; //提取非空位
		if(N!=M) return "Impossible";
		for(i=1;i<=N;i++)
		{	if(begin[a[i]]!=target[b[i]]) return "Impossible"; //对应位不同无解 
			if(begin[a[i]]=='L' && a[i]<b[i]) return "Impossible"; //为L且在左边无解 
			if(begin[a[i]]=='R' && a[i]>b[i]) return "Impossible"; //为R且在右边无解 
		}
		return "Possible";
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "R..."; string Arg1 = "..R."; string Arg2 = "Possible"; verify_case(0, Arg2, ableToMove(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "..R."; string Arg1 = "R..."; string Arg2 = "Impossible"; verify_case(1, Arg2, ableToMove(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = ".L.R.R."; string Arg1 = "L...R.R"; string Arg2 = "Possible"; verify_case(2, Arg2, ableToMove(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = ".L.R."; string Arg1 = ".R.L."; string Arg2 = "Impossible"; verify_case(3, Arg2, ableToMove(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "LRLLRLRLLRLLRLRLRL"; string Arg1 = "LRLLRLRLLRLLRLRLRL"; string Arg2 = "Possible"; verify_case(4, Arg2, ableToMove(Arg0, Arg1)); }
	void test_case_5() { string Arg0 = "L"; string Arg1 = "."; string Arg2 = "Impossible"; verify_case(5, Arg2, ableToMove(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	FoxAndChess ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
