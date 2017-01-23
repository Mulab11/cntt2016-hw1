// BEGIN CUT HERE

// END CUT HERE
#include<bits/stdc++.h>
using namespace std;

#define ll long long
int n,tot;
int a[1000010],b[1000010];
long long ans;

class TheDivisionGame
{	public:
	long long countWinningIntervals(int L, int R)
	{	int i,j,k,t,s,x,last;
		
		tot=R-L+1;
		memset(a,0,sizeof(a));
		for(i=L;i<=R;i++) b[i-L+1]=i;
		for(i=2;i<=40000;i++) //枚举因数i 
		{	x=((L-1)/i+1)*i;
			for(;x<=R;x+=i) //用它去筛x 
			{	while(b[x-L+1]%i==0)
				{	a[x-L+1]++;
					b[x-L+1]/=i;
				}
			}
		}
		for(i=1;i<=tot;i++)
			if(b[i]>1) a[i]++;
		for(i=2;i<=tot;i++) //前缀xor和 
			a[i]^=a[i-1];
		a[++tot]=0;	
		sort(a+1,a+tot+1);
		ans=(ll)(R-L+1)*(R-L+2)/2;
		for(i=1;i<=tot;i=last+1)
		{	last=i;
			while(last+1<=tot && a[last+1]==a[i]) last++; //求出i~last的sg前缀xor和相同 
			ans-=(ll)(last-i+1)*(last-i)/2; //减去xor=0的方案 
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 9; int Arg1 = 10; long long Arg2 = 2LL; verify_case(0, Arg2, countWinningIntervals(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 5; long long Arg2 = 9LL; verify_case(1, Arg2, countWinningIntervals(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 6; long long Arg2 = 13LL; verify_case(2, Arg2, countWinningIntervals(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 2; int Arg1 = 100; long long Arg2 = 4345LL; verify_case(3, Arg2, countWinningIntervals(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 12566125; int Arg1 = 12567777; long long Arg2 = 1313432LL; verify_case(4, Arg2, countWinningIntervals(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	TheDivisionGame ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
