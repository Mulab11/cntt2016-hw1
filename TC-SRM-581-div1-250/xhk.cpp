// BEGIN CUT HERE

// END CUT HERE
#line 5 "SurveillanceSystem.cpp"
#include<bits/stdc++.h>
using namespace std;

const int maxn=60;
int flag[maxn];

class SurveillanceSystem
{	public:
	string getContainerInfo(string containers, vector <int> reports, int L)
	{	int i,j,k,c;
		string ans(containers.size(),'-');
		vector<vector<int> > counters(containers.size()+1);
		vector<int> kindsOfCamera(L+1);

		for(i=0;i<=containers.size()-L;i++) //计算第i个containers的可行位置 
		{	c=count(&containers[i],&containers[i]+L,'X');
			counters[c].push_back(i);
		}

		for(i=0;i<reports.size();i++) kindsOfCamera[reports[i]]++; //每种几个cameras 

		for(i=0;i<=L;i++)
		{	if(!kindsOfCamera[i]) continue;
			memset(flag,0,sizeof(flag));
			for(j=0;j<counters[i].size();j++)
				for(k=0;k<L;k++)
				{	if('-'==ans[counters[i][j]+k])
						ans[counters[i][j]+k]='?';
					flag[counters[i][j]+k]++;
				}
			for(j=0;j<counters.size();j++)
				if(flag[j]>counters[i].size()-kindsOfCamera[i])
					ans[j]='+';
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "-X--XX"; int Arr1[] = {1, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; string Arg3 = "??++++"; verify_case(0, Arg3, getContainerInfo(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "-XXXXX-"; int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; string Arg3 = "???-???"; verify_case(1, Arg3, getContainerInfo(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "------X-XX-"; int Arr1[] = {3, 0, 2, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; string Arg3 = "++++++++++?"; verify_case(2, Arg3, getContainerInfo(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "-XXXXX---X--"; int Arr1[] = {2, 1, 0, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; string Arg3 = "???-??++++??"; verify_case(3, Arg3, getContainerInfo(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arg0 = "-XX--X-XX-X-X--X---XX-X---XXXX-----X"; int Arr1[] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; string Arg3 = "???++++?++++++++++++++++++++??????--"; verify_case(4, Arg3, getContainerInfo(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	SurveillanceSystem ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
