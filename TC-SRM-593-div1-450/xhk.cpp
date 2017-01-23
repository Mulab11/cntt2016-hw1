// BEGIN CUT HERE

// END CUT HERE
#line 5 "MayTheBestPetWin.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=1e9;
int n,ans;
int a[110],b[110],f[1000010];

class MayTheBestPetWin
{	public:
	int calc(vector <int> A, vector <int> B)
	{	int i,j,s1,s2;
	 
	 	n=A.size();
	 	for(i=1;i<=n;i++) a[i]=A[i-1];
	 	for(i=1;i<=n;i++) b[i]=B[i-1];
	 	memset(f,0,sizeof(f));
	 	f[0]=1;
	 	for(i=1;i<=n;i++)
	 		for(j=1000000;j>=0;j--) //按照a[i]+b[i]求背包 
	 			if(j>=a[i]+b[i])
	 				f[j]=f[j]|f[j-a[i]-b[i]];
	 	ans=inf;
	 	s1=0;
	 	s2=0;
	 	for(i=1;i<=n;i++) s1+=a[i],s2+=b[i];
	 	for(i=0;i<=1000000;i++) //枚举每个之判断哪个更优 
	 		if(f[i])
	 			ans=min(ans,max(s2-i,i-s1)); //确定集合之后这个方案的答案为 max(sigma(b)-i,i-sigma(a))
	 	return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {3,4,4,7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,4,4,7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(0, Arg2, calc(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,3,5,4,5}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,5,6,8,7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(1, Arg2, calc(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {2907,949,1674,6092,8608,5186,2630,970,1050,2415,1923,2697,5571,6941,8065,4710,716,756,5185,1341,993,5092,248,1895,4223,1783,3844,3531,2431,1755,2837,4015}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {7296,6954,4407,9724,8645,8065,9323,8433,1352,9618,6487,7309,9297,8999,9960,5653,4721,7623,6017,7320,3513,6642,6359,3145,7233,5077,6457,3605,2911,4679,5381,6574}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 52873; verify_case(2, Arg2, calc(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	MayTheBestPetWin ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
