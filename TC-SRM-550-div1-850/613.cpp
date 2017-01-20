// BEGIN CUT HERE

// END CUT HERE
#line 5 "ConversionMachine.cpp"
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
#define mo 1000000007ll
using namespace std;
int matsize;
struct mat
{
	int a[155][155];
	friend mat operator *(mat x,mat y)
	{
		mat ans;
		memset(ans.a,0,sizeof(ans.a));
		for (int i=0;i<=matsize;i++)
		for (int j=0;j<=matsize;j++)
		for (int k=0;k<=matsize;k++)
			ans.a[i][j]=(ans.a[i][j]+(long long)x.a[i][k]*y.a[k][j])%mo;
		return ans;
	}
};
/*inline matrix exp(matrix x,int y){
	matrix ans;ans.e();
	while(y){
		if(y&1) ans=ans*x;
		x=x*x;y>>=1;
	}
	return ans;
}*/
mat getmi(mat a,int x)
{
	/*if (x==1) return a;
	mat ans=getmi(a,x>>1);
	ans=ans*ans;
	if (x&1) ans=ans*a;
	return ans;*/
	mat ans;
	for (int i=0;i<=matsize;i++)
	for (int j=0;j<=matsize;j++)
		ans.a[i][j]=(i==j);
	while (x)
	{
		if (x&1) ans=ans*a;
		a=a*a;x>>=1;
	}
	return ans;
}
class ConversionMachine
{
        public:
        int countAll(string word1, string word2, vector <int> cost, int mc)
        {
        	long long maxcost=mc,mincost=0;
			int n=word1.size(),js1=0,js2=0,all=0;
			for (int i=0;i<n;i++)
			{
				if ((word1[i]=='a')&&(word2[i]=='b')) {mincost+=cost[0];js1++;}
				if ((word1[i]=='a')&&(word2[i]=='c')) {mincost+=cost[0]+cost[1];js2++;}
				if ((word1[i]=='b')&&(word2[i]=='a')) {mincost+=cost[1]+cost[2];js2++;}
				if ((word1[i]=='b')&&(word2[i]=='c')) {mincost+=cost[1];js1++;}
				if ((word1[i]=='c')&&(word2[i]=='a')) {mincost+=cost[2];js1++;}
				if ((word1[i]=='c')&&(word2[i]=='b')) {mincost+=cost[2]+cost[0];js2++;}
			}
			if (mincost>maxcost) return 0;
			all=js1+js2*2+(maxcost-mincost)/((long long)cost[0]+cost[1]+cost[2])*3;
			
			//cout<<all<<endl;
			
			matsize=(n+1)*(n+1);
			mat mts;
			for (int i=0;i<=n;i++)
			for (int j=0;j<=n-i;j++)
			{
				if ((i!=n)&&(j!=0)) mts.a[i*(n+1)+j][(i+1)*(n+1)+(j-1)]+=j;
				if (i!=0) mts.a[i*(n+1)+j][(i-1)*(n+1)+j]+=i;
				if (j!=n) mts.a[i*(n+1)+j][i*(n+1)+(j+1)]+=n-i-j;
			}
			mts.a[matsize][matsize]++;
			mts.a[0][matsize]++;
			mts=getmi(mts,all+1);
			/*for (int i=0;i<=10;i++)
			for (int j=0;j<=10;j++)
			{
				cout<<mts.a[i][j]<<' ';
				if (j==10) cout<<endl;
			}
			cout<<js1*(n+1)+js2<<endl;*/
			return mts.a[js1*(n+1)+js2][matsize];
        }
        
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "a"; string Arg1 = "b"; int Arr2[] = {100,2,3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 205; int Arg4 = 2; verify_case(0, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { string Arg0 = "abcba"; string Arg1 = "abcba"; int Arr2[] = {67,23,43}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; int Arg4 = 1; verify_case(1, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { string Arg0 = "cccccccc"; string Arg1 = "aaaaaaaa"; int Arr2[] = {10000000,1,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 100; int Arg4 = 40320; verify_case(2, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { string Arg0 = "aa"; string Arg1 = "cc"; int Arr2[] = {1,10,100}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1787; int Arg4 = 123611681; verify_case(3, Arg4, countAll(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        ConversionMachine ___test;
        ___test.run_test(1);
        return 0;
}
// END CUT HERE
