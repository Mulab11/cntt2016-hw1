// BEGIN CUT HERE

// END CUT HERE
#line 5 "WolfInZooDivOne.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=1000000007;
int n,ans;
int f[310][310],g[310][310];
vector<int> a,b;

void update(int &i,int x)
{i=(i+x)%mod;
}

vector<int> trans(vector<string> A) //格式转换 
{vector<int> ret;
 int i,j,s;
 string B;
 
 B="";
 for(i=0;i<A.size();i++)
 	B+=A[i];
 ret.clear();
 s=0;
 for(i=0;i<B.length();i++)
 	if(B[i]==' ')
 	{	ret.push_back(s);
 		s=0;
 	}
	else
		s=s*10+B[i]-48;
 ret.push_back(s);
 return ret;
}

class WolfInZooDivOne
{	public:
	int count(int N, vector <string> L, vector <string> R)
	{	int i,j,k,l,r;
		
		n=N;
		a=trans(L);
		b=trans(R);
		
		memset(g,0,sizeof(g));
		for(i=0;i<a.size();i++)
		{	l=a[i]+1;
			r=b[i]+1;
			for(j=l;j<=r;j++) //求出中间不能再放的区间(j,k) 
				for(k=j;k<=r;k++)
					g[j][k]=1;
		}
		memset(f,0,sizeof(f));
		for(i=1;i<=n;i++) f[i][0]=1;
		ans=1;
		for(i=0;i<=n;i++)
			for(j=i-1;j>=0;j--) //f[i][j]表示当前到i上一个在j的方案数，枚举下一个 
			{	if(!f[i][j]) continue;
				update(ans,f[i][j]);
				for(k=i+1;k<=n;k++)
				{	if(g[j][k]) continue;
					update(f[k][i],f[i][j]);
				}
			}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 12; string Arr1[] = {"6 6 10 6 10 9 5 10 5 4 0 3"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"10 10 10 6 10 10 5 10 9 11 10 10"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 113; verify_case(0, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 5; string Arr1[] = {"0 1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"2 4"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 21; verify_case(1, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 10; string Arr1[] = {"0 4 2 7"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"3 9 5 9"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 225; verify_case(2, Arg3, count(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 100; string Arr1[] = {"0 2 2 7 10 1","3 16 22 30 33 38"," 42 44 49 51 57 60 62"," 65 69 72 74 77 7","8 81 84 88 91 93 96"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"41 5 13 22 12 13 ","33 41 80 47 40 ","4","8 96 57 66 ","80 60 71 79"," 70 77 ","99"," 83 85 93 88 89 97 97 98"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 6419882; verify_case(3, Arg3, count(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	WolfInZooDivOne ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
