// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheJediTest.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,ans;
int a[110];

class TheJediTest
{	public:
	int minimumSupervisors(vector <int> students, int K)
	{	int i,j,s,s1;
		
		n=students.size();
		for(i=1;i<=n;i++) a[i]=students[i-1];
		ans=0;
		s=0;
		for(i=1;i<n;i++)
		{	//cout<<i<<" "<<s<<" "<<a[i]<<" "<<ans<<endl;
			
			s1=(a[i]+s)/K;
			if(s1==0 && s!=0)
			{	ans++;
				a[i+1]-=min(a[i+1],K-(a[i]+s));
				s=0;
			}
			else
			{	ans+=s1;
				s=(a[i]+s)%K;
			}
		}
		if(a[n]+s!=0)
			ans+=(a[n]+s-1)/K+1;	
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1537850, 16423383, 94400848, 5424583, 76422187, 82935400, 3215939, 88361204, 80014335, 485978, 31677191, 39729460, 68544237}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 76106115; int Arg2 = 8; verify_case(0, Arg2, minimumSupervisors(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1, 1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 2; verify_case(1, Arg2, minimumSupervisors(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {0, 0, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12345; int Arg2 = 0; verify_case(2, Arg2, minimumSupervisors(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {15, 0, 13, 4, 29, 6, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; int Arg2 = 10; verify_case(3, Arg2, minimumSupervisors(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1284912, 1009228, 9289247, 2157, 2518, 52781, 2, 2818, 68}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 114; int Arg2 = 102138; verify_case(4, Arg2, minimumSupervisors(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	TheJediTest ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
