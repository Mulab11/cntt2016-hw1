// BEGIN CUT HERE

// END CUT HERE
#line 5 "PastingPaintingDivOne.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
int n,m;
int a[110][110],b[310][310];
long long f[10],g[10];
vector<long long> ans;

class PastingPaintingDivOne
{	public:
	vector<long long> countColors(vector <string> clipboard, int T)
	{	int i,j,k;
		
		n=clipboard.size();
		m=clipboard[0].length();
		memset(a,0,sizeof(a));
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				if(clipboard[i-1][j-1]=='R')
					a[i][j]=1;
				else if(clipboard[i-1][j-1]=='G')
					a[i][j]=2;
				else if(clipboard[i-1][j-1]=='B')
					a[i][j]=3;
		memset(b,0,sizeof(b));
		memset(f,0,sizeof(f));
		for(k=1;k<=100 && k<=T;k++) //前100个枚举 
		{	for(i=1;i<=n;i++)
				for(j=1;j<=m;j++)
				{	if(!a[i][j]) continue;
					f[b[k+i-1][k+j-1]]--;
					f[a[i][j]]++;
					b[k+i-1][k+j-1]=a[i][j];
				}
		}
		memset(g,0,sizeof(g));
		for(i=1;i<=n;i++) //算出下一次的变化 
			for(j=1;j<=m;j++)
			{	if(!a[i][j]) continue;
				g[b[k+i-1][k+j-1]]--;
				g[a[i][j]]++;
			}
		//cout<<f[1]<<" "<<g[1]<<endl;	
		if(T>100) //直接累加剩下的 
		{	f[1]+=(ll)(T-100)*g[1];
			f[2]+=(ll)(T-100)*g[2];
			f[3]+=(ll)(T-100)*g[3];
		}
		ans.clear();
		ans.push_back(f[1]);
		ans.push_back(f[2]);
		ans.push_back(f[3]);
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector<long long> &Expected, const vector<long long> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {
"..G",
"R..",
"BG."
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; long Arr2[] = {3, 4, 3 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, countColors(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {
"R...",
"....",
"....",
"...R"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; long Arr2[] = {4, 0, 0 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, countColors(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"RGB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100000; long Arr2[] = {100000, 100000, 100000 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, countColors(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000000000; long Arr2[] = {0, 0, 0 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, countColors(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {
"RB.",
".G."
}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; long Arr2[] = {100, 1, 100 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, countColors(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {
"..........G..........",
".........G.G.........",
"........G...G........",
".......G.....G.......",
"......G..B.B..G......",
".....G...B.B...G.....",
"....G...........G....",
"...G...R.....R...G...",
"..G.....RRRRRR....G..",
".G..........RR.....G.",
"GGGGGGGGGGGGGGGGGGGGG"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000000000; long Arr2[] = {2000000018, 17000000048, 2000000005 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(5, Arg2, countColors(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	PastingPaintingDivOne ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
