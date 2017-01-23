// BEGIN CUT HERE

// END CUT HERE
#line 5 "TeamContest.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m,ans;
int a[110],used[110];

class TeamContest
{	public:
	int worstRank(vector <int> strength)
	{	int i,j,k,s;
		
		n=strength.size()/3;
		for(i=4;i<=3*n;i++) a[i-3]=strength[i-1];
		s=max(strength[0],max(strength[1],strength[2]))+min(strength[0],min(strength[1],strength[2]));
		ans=1;
		memset(used,0,sizeof(used));
		m=3*n-3;
		sort(a+1,a+m+1);
		reverse(a+1,a+m+1);
		//cout<<m<<endl;
		//for(i=1;i<=m;i++) cout<<a[i]<<" ";
		//cout<<endl;
		//cout<<s<<endl;
		ans=1;
		i=1;
		while(1)
		{	while(i<=m && used[i]) i++;
			if(i>m) break;
			j=m;
			while(j>=i && (used[j] || a[j]+a[i]<=s)) j--;
			if(j<=i) break;
			k=j-1;
			while(k>=i && used[k]) k--;
			if(k<=i) break;
			used[i]=1;
			used[j]=1;
			used[k]=1;
			ans++;
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {5, 7, 3, 5, 7, 3, 5, 7, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, worstRank(Arg0)); }
	void test_case_1() { int Arr0[] = {5, 7, 3}
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, worstRank(Arg0)); }
	void test_case_2() { int Arr0[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(2, Arg1, worstRank(Arg0)); }
	void test_case_3() { int Arr0[] = {3,9,4,6,2,6,1,6,9,1,4,1,3,8,5}
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(3, Arg1, worstRank(Arg0)); }
	void test_case_4() { int Arr0[] = {53,47,88,79,99,75,28,54,65,14,22,13,11,31,43}
; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(4, Arg1, worstRank(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	TeamContest ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
