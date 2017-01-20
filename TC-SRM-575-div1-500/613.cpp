// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheSwapsDivOne.cpp"
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
using namespace std;
int st[2555],n;
long double in_in[2555],in_out[2555],out_in[2555],out_out[2555];
int sum[2555];
int getsum(int l,int r){return sum[r]-sum[l-1];}
struct mat
{
	long double a00,a01,a10,a11;
	friend mat operator *(mat x,mat y)
	{
		mat ans;
		ans.a00=x.a00*y.a00+x.a01*y.a10;
		ans.a01=x.a00*y.a01+x.a01*y.a11;
		ans.a10=x.a10*y.a00+x.a11*y.a10;
		ans.a11=x.a10*y.a01+x.a11*y.a11;
		return ans;
	}
};
mat getmi(mat a,int x)
{
	if (x==1) return a;
	mat p=getmi(a,x>>1);
	p=p*p;
	if (x&1) p=p*a;
	return p;
}
class TheSwapsDivOne
{
        public:
        double find(vector <string> ls, int k)
        {
			for (int i=0;i<ls.size();i++)
			for (int j=0;j<ls[i].size();j++)
				st[++n]=ls[i][j]-'0';
			for (int i=1;i<=n;i++) sum[i]=sum[i-1]+st[i];
			for (int len=1;len<=n;len++)
			{
				mat p=(mat){1-2.0*(n-len)/n/(n-1),2.0*(n-len)/n/(n-1),2.0*len/n/(n-1),1-2.0*len/n/(n-1)};
					//cout<<(double)p.a00<<' '<<(double)p.a01<<' '<<(double)p.a10<<' '<<(double)p.a11<<endl;
				p=getmi(p,k);
					//cout<<(double)p.a00<<' '<<(double)p.a01<<' '<<(double)p.a10<<' '<<(double)p.a11<<endl<<endl;
				in_in[len]=p.a00;
				in_out[len]=p.a01;
				out_in[len]=p.a10;
				out_out[len]=p.a11;
			}
			long double ans=0;
			for (int i=1;i<=n;i++)
			for (int j=i;j<=n;j++)
				ans+=in_in[j-i+1]*getsum(i,j)+out_in[j-i+1]*(sum[n]-getsum(i,j));
			return (double)ans/((n+1)*n/2.0);
			
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
{
        TheSwapsDivOne ___test;
        ___test.run_test(3);
        return 0;
}
// END CUT HERE
