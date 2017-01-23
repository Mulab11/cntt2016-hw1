// BEGIN CUT HERE

// END CUT HERE
#line 5 "EelAndRabbit.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,tot,ans;
int a[110],b[110],sa[210];

class EelAndRabbit
{	public:
	int getmax(vector <int> l, vector <int> t)
	{	int i,j,k,s,flag;
		
		n=l.size();
		tot=0;
		for(i=1;i<=n;i++)
		{	a[i]=-t[i-1]-l[i-1];
			b[i]=-t[i-1];
			sa[++tot]=a[i]; //离散化 
			sa[++tot]=b[i];
		}
		ans=0;
		for(i=1;i<=tot;i++)
			for(j=1;j<=tot;j++) //枚举两个时刻 
			{	s=0;
				for(k=1;k<=n;k++) //统计能抓到那些鱼 
				{	flag=0;
					if(a[k]<=sa[i] && b[k]>=sa[i]) flag=1;
					if(a[k]<=sa[j] && b[k]>=sa[j]) flag=1;
					s+=flag;
				}
				ans=max(ans,s);
			}
		return ans;	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2, 4, 3, 2, 2, 1, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 6, 3, 7, 0, 2, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; verify_case(0, Arg2, getmax(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 0, 4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(1, Arg2, getmax(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(2, Arg2, getmax(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {8, 2, 1, 10, 8, 6, 3, 1, 2, 5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {17, 27, 26, 11, 1, 27, 23, 12, 11, 13}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; verify_case(3, Arg2, getmax(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	EelAndRabbit ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
