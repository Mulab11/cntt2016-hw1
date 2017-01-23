// BEGIN CUT HERE

// END CUT HERE
#line 5 "KingdomAndTrees.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=1000000000;
int n,ans;
int a[110],b[110];

int check(int x)
{int i,j,last=0;
 
 for(i=1;i<=n;i++)
 	if(a[i]+x<=last)
	 	return 0;
 	else if(a[i]>=x)
 		last=max(a[i]-x,last+1);
 	else
 		last=last+1;
 return 1;
}

class KingdomAndTrees
{	public:
	int minLevel(vector <int> heights)
	{	int i,j,l,r,mid;
	
		n=heights.size();
		for(i=1;i<=n;i++) a[i]=heights[i-1];
		l=0;
		r=inf;
		ans=inf;
		while(l<=r)
		{	mid=(l+r)/2;	
			if(check(mid))
			{	ans=min(ans,mid);
				r=mid-1;
			}
			else
				l=mid+1;
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {9, 5, 11}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, minLevel(Arg0)); }
	void test_case_1() { int Arr0[] = {5, 8}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, minLevel(Arg0)); }
	void test_case_2() { int Arr0[] = {1, 1, 1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(2, Arg1, minLevel(Arg0)); }
	void test_case_3() { int Arr0[] = {548, 47, 58, 250, 2012}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 251; verify_case(3, Arg1, minLevel(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	KingdomAndTrees ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
