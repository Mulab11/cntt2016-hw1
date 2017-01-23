// BEGIN CUT HERE

// END CUT HERE
#line 5 "AlternateColors2.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
long long ans;

class AlternateColors2
{	public:
	long long countWays(int n, int k)
	{	int i,j;
		long long s,N,K;
		
		//分成三个阶段，第一个阶段三色球都有，第二个阶段只有两种颜色的球，最后一个阶段只有一种颜色的球 
		
		ans=0;
		if(k%3==1) ans=(ll)(n-k)*(n-k-1)/2; //在第一阶段取到k的方案 
		for(i=0;i*3<k;i++) //在二三阶段取到的方案 
		{	N=n-i*3;
			K=k-i*3;
			s=0;
			if(K&1) s+=N-K; 
			s+=(K+1)/2;
			ans+=2*s;
			ans--;
		}
		return ans;	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; long long Arg2 = 1LL; verify_case(0, Arg2, countWays(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 3; long long Arg2 = 3LL; verify_case(1, Arg2, countWays(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 6; int Arg1 = 4; long long Arg2 = 9LL; verify_case(2, Arg2, countWays(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 6; int Arg1 = 1; long long Arg2 = 21LL; verify_case(3, Arg2, countWays(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 1000; int Arg1 = 2; long long Arg2 = 1LL; verify_case(4, Arg2, countWays(Arg0, Arg1)); }
	void test_case_5() { int Arg0 = 100000; int Arg1 = 100000; long long Arg2 = 1666700000LL; verify_case(5, Arg2, countWays(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	AlternateColors2 ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
