// BEGIN CUT HERE

// END CUT HERE
#line 6 "XorTravelingSalesman.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m;
int a[60],q[1000010],ga[60][60],f[60][1100];

class XorTravelingSalesman
{
	public:
	int maxProfit(vector <int> cityValues, vector <string> roads)
	{	int i,j,k,t,w,flag;
		
		n=cityValues.size();
		for(i=1;i<=n;i++) a[i]=cityValues[i-1];
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				ga[i][j]=(roads[i-1][j-1]=='Y');
		memset(f,0,sizeof(f));
		f[1][a[1]]=1;
		t=1;
		w=1;
		q[t]=1;
		while(t<=w)
		{	i=q[t];
			for(j=1;j<=n;j++)
				if(ga[i][j])
				{	flag=0;
					for(k=0;k<1024;k++)
						if(f[i][k] && !f[j][k^a[j]])
						{	f[j][k^a[j]]=1;
							flag=1;
						}
					if(flag) q[++w]=j;
				}
			t++;
			//cout<<t<<" "<<w<<endl;
		}
		for(i=1023;i>=0;i--)
		{	flag=0;
			for(j=1;j<=n;j++)
				if(f[j][i])
				{	flag=1;
					break;
				}
			if(flag) return i;
		}	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 7, 11, 5, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NYNYY",
 "YNYNN",
 "NYNNN",
 "YNNNN",
 "YNNNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 14; verify_case(0, Arg2, maxProfit(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {556}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"N"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 556; verify_case(1, Arg2, maxProfit(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {0, 4, 8, 32, 512}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NYYYY",
 "YNNNN",
 "YNNNN",
 "YNNNN",
 "YNNNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 556; verify_case(2, Arg2, maxProfit(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {37, 1, 19, 64, 42, 41, 64, 64, 54, 16, 256, 36, 64, 2, 4, 2, 62, 29, 58, 64, 1, 32, 16,
 256, 17, 2, 17, 4, 1, 64, 21, 8, 256, 63, 3, 1, 43, 15, 8, 39, 41, 8, 16, 8, 16, 256, 64, 512, 45, 64}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNNNNNYYYYNNNNNNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNNYNNNNNNNYNNNNNNNNNNNNNNNNYYNNNYYNN",
 "NNNNNYYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNYNNNNNNNNNNYNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNNNNNNNYNNYNYNNNNNNYNNNNNNNNNNYNNNNNNNNNNN",
 "NNYNNNYNNNNNNNNYNNYNNNYYNNNYNYNNNNYNNNNNNNNYNNNNNN",
 "YNYNNYNYNNNNNNNYNNNNNNNNNNNNNNNNNNNYNNNNNNNNYNNYNN",
 "YNNYNNYNYNYYNNNNNNNNNNNNNNNNNNNNNNYNNYNNNNNNNNNNNN",
 "YNNNNNNYNNNNNNNNNNNNNNYNYNNNNNNNNNNYYYNNNNNNNYNNNY",
 "YNNNNNNNNNNNNNNNNYNYNYNYYNNNYNNNNYNNNNNNNNNNNNNNNY",
 "NNNNNNNYNNNNYNNNNNNNNYYNNNYYNNNNYNYYNNNNNNNNNNNNNN",
 "NNNNNNNYNNNNNNYNNNNYYNNNYNNYYNNNNNNNNNNNNNYNYNNNNN",
 "NNNNNNNNNNYNNNNNYNNNNYNNNNNNNNNNYNYNNYNYNNNYNYNNNN",
 "NNNNNNNNNNNNNNNYNNNNNNNNNYNNNNNNNNNNNNYNNNNNNNNYNN",
 "NNNNNNNNNNNYNNNNNYNYNNYYNNNNNYNNNNNNNNNYNNYNNYNNNN",
 "NNNNYYYNNNNNNYNNNYYNNYNNNYNYYNNNNNNNNNYYYNNYNNYNYN",
 "NYNNNNNNNNNNYNNNNNNNYNNNYYNNNYNNNNYNNNNNNNNNNNNNNN",
 "NNNNNNNNNYNNNNYYNNNNNNYNNNYNNNNNYNNYNYYNNNNYNNNYNN",
 "NNNYYYNNNNNNNNNYNNNNNYNYNYNNNNNNNNYNNNNNNNNNNNNNNN",
 "NNNNNNNNNYNYNNYNNNNNNYNYYYNNNNNNNNNNNYNNYNNNNNYNNN",
 "NNNNYNNNNNNYNNNNYNNNNYNNNYYNNNYNNNYNNNNNNNNNNYNYNY",
 "NNNNNNNNNYYNYNNYNNYYYNYNNNNNNNNYNYNNNNNNNNNNYNNNNN",
 "NNNNNYNNYNYNNNYNNYNNNYNNNNNNNNNNNYNNYNYNNYNNNNNNNN",
 "NNNNNYNNNYNNNNYNNNYYNNNNNNNNNNNNNNNNNNNNNNYNNNYNNN",
 "NYNNNNNNYYNYNNNNYNNYNNNNNNNNNNYNNNNNNYNNNYNNYNNNNN",
 "NNNNNNNNNNNNNYNYYNYYYNNNNNNYNNNNNNNNNNNYYNNNNNNNYN",
 "NNNNNNNNNNYNNNNNNYNNYNNNNNNNNYNNNNYNNNNNNYYNNNNYNN",
 "NNNNYYNNNNYYNNNYNNNNNNNNNYNNNYYNYNNNNNNNNNNNNNNNNN",
 "NNNNNNNNNYNYNNNYNNNNNNNNNNNNNYNNNNYNNNNNNNNYNNYNYN",
 "NNNNNYNNNNNNNNYNYNNNNNNNNNYYYNNNNNNNNYNNNNYNNNNNNN",
 "NNNNNNNNNNNNNNNNNNNNYNNNYNNYNNNNNYNNNNNNNNNNNNNNNY",
 "NNNNNNNNNNNNNNNNNNNNNYNNNNNNNNNNYNNNNNNNNNYNNNNNNN",
 "NNNNNNNNNNYNYNNNNYNNNNNNNNNYNNNYNNNYYNNNNNYNNNYNNN",
 "NNNNNNNNNYNNNNNNNNNNNYYNNNNNNNYNNNNNNNYNNYNNNNNNNN",
 "NNNNNYNYNNYNYNNNYNYNYNNNNNYNYNNNNNNYYNYNYNYNNNNNYN",
 "YNNNNNYNYNYNNNNNNYNNNNNNNNNNNNNNYNYNNNNNYNNYNNNYNN",
 "NNNNNNNNYNNNNNNNNNNNNNYNNNNNNNNNYNYNNNNNNYNNNNNNYN",
 "NNNNNNNYYNNNYNNNNYNYNNNNYNNNNYNNNNNNNNNNNYNNNNYNNN",
 "NNNNYNNNNNNNNYNYNYNNNNYNNNNNNNNNNYYNNNNYNNNNNNNNNY",
 "NNNNNNNNNNNNYNYYNNNNNNNNNYNNNNNNNNNNNNYNNNNNYNYYNN",
 "NNNNNNNNNNNNNNNYNNNYNNNNNYNNNNNNNNYYNNNNNNNNNNNNNN",
 "NYNNNNNNNNNNNNNNNNNNNNYNYNYNNNNNNYNNYYNNNNNNNNNNNN",
 "NYNNNNNNNNNYNNYNNNNNNNNYNNYNNYNYYNYNNNNNNNNNYNNNNN",
 "NNNNNYNNNNNNYNNYNYNNNNNNNNNNYNNNNNNYNNNNNNNNNNNNNY",
 "NNNNNNYNNNNYNNNNNNNNNYNNYNNNNNNNNNNNNNNYNNYNNYNNNY",
 "NNNNNNNNYNNNYNYNNNNNYNNNNNNNNNNNNNNNNNNNNNNNYNNNNN",
 "NYNNNNNNNNNNNNNYNNNYNNNYNNNNYNNNYNNNNYNYNNNNNNNNNN",
 "NYNNNNYNNNNNNYNNNYNNYNNNNNYNNNNNNNNYNNNYNNNNNNNNNN",
 "NNNNNNNNNNNNNNNYNNNNNNNNNYNNYNNNNNYNYNNNNNNNNNNNNN",
 "NNNNNNNNYYNNNNNNNNNNYNNNNNNNNNYNNNNNNNYNNNNYYNNNNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 895; verify_case(3, Arg2, maxProfit(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{XorTravelingSalesman ___test;
 ___test.run_test(-1);
 return 0;
}
// END CUT HERE
