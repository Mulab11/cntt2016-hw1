// BEGIN CUT HERE

// END CUT HERE
#line 5 "PiecewiseLinearFunction.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,ans,tot;
int a[210],b[210],sa[210];

class PiecewiseLinearFunction
{	public:
	int maximumSolutions(vector <int> Y)
	{	int i,j,x;
		
		n=Y.size();
		tot=0;
		for(i=1;i<=n;i++)
		{	sa[++tot]=a[i]=Y[i-1];
			sa[++tot]=a[i]-1;
			sa[++tot]=a[i]+1;
		}
		sort(sa+1,sa+tot+1);
		for(i=1;i<=n;i++) a[i]=lower_bound(sa+1,sa+tot+1,a[i])-sa; //离散化 
		memset(b,0,sizeof(b));
		for(i=1;i<n;i++) //累计每个值出现次数，因为整数中一定存在一个最优解 
		{	x=a[i];
			if(x==a[i+1]) return -1;
			while(x!=a[i+1])
			{	b[x]++;
				if(x>a[i+1])
					x--;
				else
					x++;
			}
		}
		b[a[n]]++;
		ans=0;
		for(i=1;i<=tot;i++) ans=max(ans,b[i]);
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {278832792, 465135153, -802394470, 142729209, -943268501, 908089082}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(0, Arg1, maximumSolutions(Arg0)); }
	void test_case_1() { int Arr0[] = {4, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(1, Arg1, maximumSolutions(Arg0)); }
	void test_case_2() { int Arr0[] = {1, 4, -1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(2, Arg1, maximumSolutions(Arg0)); }
	void test_case_3() { int Arr0[] = {2, 1, 2, 1, 3, 2, 3, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(3, Arg1, maximumSolutions(Arg0)); }
	void test_case_4() { int Arr0[] = {125612666, -991004227, 0, 6, 88023, -1000000000, 1000000000, -1000000000, 1000000000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(4, Arg1, maximumSolutions(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	PiecewiseLinearFunction ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
