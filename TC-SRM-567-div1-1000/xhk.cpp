// BEGIN CUT HERE

// END CUT HERE
#line 5 "Mountains.cpp"
#include<bits/stdc++.h>
using namespace std;

const int mod=1000000009;
int n,m,ans;
int a[20];
long long vis[110];
map<vector<int>,int> h;

int check(int i,vector<int> w,int j)
{int k;
 long long s=0;
 
 for(k=1;k<=m;k++)
 	if(a[i]-abs(j-k)>w[k])
 		s|=(1LL<<k);
 return s==vis[i];
}		

int dfs(int i,vector<int> w)
{int j,k,ret=0;
 vector<int> w1;
 
 if(h.find(w)!=h.end()) return h[w];
 if(i==0) return 1;
 for(j=1;j<=m;j++)
 	if(check(i,w,j))
 	{	w1=w;
 		for(k=1;k<=m;k++)
 			if(a[i]-abs(k-j)>w1[k])
 				w1[k]=a[i]-abs(k-j);
 		w1[0]=i-1;
 		ret=(ret+dfs(i-1,w1))%mod;
 	}
 h[w]=ret;
 return ret;
}

class Mountains
{	public:
	int countPlacements(vector <int> heights, vector <string> visibility)
	{	int i,j;
		vector<int> w;
		
		n=heights.size();
		m=visibility[0].length();
		for(i=1;i<=n;i++) a[i]=heights[i-1];
		for(i=1;i<=n;i++)
		{	vis[i]=0;
			for(j=1;j<=m;j++)
				if(visibility[i-1][j-1]=='X')
					vis[i]|=1LL<<j;
		}
		h.clear();
		w.clear();
		w.push_back(n);
		for(i=1;i<=m;i++) w.push_back(0);
		ans=dfs(n,w);
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2, 3, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"------",
 "XXXX--",
 "---XXX"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(0, Arg2, countPlacements(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {4, 3, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"XXXXX--------",
 "----------XXX",
 "----XXXXXXX--"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(1, Arg2, countPlacements(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {13, 2, 3, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"XXXXXXXXX",
 "-XXX-----",
 "----XXXXX",
 "-----XXX-"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 9; verify_case(2, Arg2, countPlacements(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {8, 2, 9, 3, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"X------",
 "-------",
 "------X",
 "-------",
 "XXXXXXX"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 98; verify_case(3, Arg2, countPlacements(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {20, 20, 20, 20, 20, 20, 45, 50, 49, 50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"-------------------",
 "-------------------",
 "-------------------",
 "-------------------",
 "-------------------",
 "-------------------",
 "-------------------",
 "------------XXXXXXX",
 "XXXXXXX------------",
 "XXXXXXXXXXXXXXXXXXX"}
; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 973726691; verify_case(4, Arg2, countPlacements(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	Mountains ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
