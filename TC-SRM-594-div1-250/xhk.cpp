// BEGIN CUT HERE

// END CUT HERE
#line 5 "AstronomicalRecords.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
int n,m,ans;
int f[110][110];
long long c[110],d[110];

class AstronomicalRecords
{	public:
	int minimalPlanets(vector <int> A, vector <int> B)
	{	int i,j,k,p;
		
		n=A.size();
		m=B.size();
		ans=n+m;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++) //枚举a[i-1]=b[j-1]，并确定比例 
			{	for(k=1;k<=n;k++)
					c[k]=(ll)A[k-1]*B[j-1];
				for(k=1;k<=m;k++)
					d[k]=(ll)B[k-1]*A[i-1]; //构造新序列 
				memset(f,0,sizeof(f));
				for(k=1;k<=n;k++) //求出最长公共子序列 
					for(p=1;p<=m;p++)
					{	f[k][p]=max(f[k-1][p],f[k][p-1]);
						if(c[k]==d[p]) f[k][p]=max(f[k][p],f[k-1][p-1]+1);
					}
				ans=min(ans,n+m-f[n][m]); //更新答案 
			}
		return ans;	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,2,1,2,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,1,2,1,2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; verify_case(0, Arg2, minimalPlanets(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,2,3,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,4,6,8}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(1, Arg2, minimalPlanets(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {2,3,2,3,2,3,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {600,700,600,700,600,700,600}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 10; verify_case(2, Arg2, minimalPlanets(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {1,2,3,4,5,6,7,8,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {6,7,8,9,10,11,12}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 12; verify_case(3, Arg2, minimalPlanets(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {100000000,200000000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {200000000,100000000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(4, Arg2, minimalPlanets(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	AstronomicalRecords ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
