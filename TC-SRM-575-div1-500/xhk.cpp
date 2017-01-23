// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheSwapsDivOne.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m;
int a[10010];
double ans;

class TheSwapsDivOne
{	public:
	double find(vector <string> sequence, int K)
	{	int i,j,s;
		double x,y,tx,ty;
		
		n=0;
		m=K;
		for(i=0;i<sequence.size();i++)
			for(j=0;j<sequence[i].length();j++)
				a[++n]=sequence[i][j]-48;
		x=1;
		y=0;
		for(i=1;i<=m;i++)
		{	tx=x*(n-2)/n+y/(n*(n-1)/2);
			ty=x*2/n+y*(1-1.0/(n*(n-1)/2));
			x=tx;
			y=ty;
			//cout<<i<<" "<<x<<" "<<y<<endl;
		}
		//printf("%.9lf",(double)x);
		//cout<<x<<" "<<y<<" "<<(1-y)<<endl;
		//x=0.5;
		//y=0.5;
		s=0;
		for(i=1;i<=n;i++) s+=a[i];
		ans=0;
		for(i=1;i<=n;i++)
			ans+=i*(n-i+1)*(x*a[i]+y*((double)(s-a[i])/(n-1)));
		//printf("%.6lf\n",ans);
		ans/=n*(n+1)/2;
		return ans;	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"4", "77"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; double Arg2 = 10.0; verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"4", "77"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 47; double Arg2 = 10.0; verify_case(1, Arg2, find(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"1", "1", "1", "1", "1", "1", "1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000000; double Arg2 = 3.0; verify_case(2, Arg2, find(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"572685085149095989026478064633266980348504469", "19720257361", "9", "69"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; double Arg2 = 98.3238536775161; verify_case(3, Arg2, find(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	TheSwapsDivOne ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
