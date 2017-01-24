// BEGIN CUT HERE

// END CUT HERE
#line 5 "ICPCBalloons.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=1<<16;

int ans;
vector<int> a,b,ua,ub;

int calc(vector<int> &A, vector<int> &B)
{int i,s1,s2,maxn,cnt1,cnt2,ret=0;

 if(A.empty() || B.empty()) return 0;
 s1=A.size();
 s2=B.size();
 maxn=max(s1,s2);
 for(i=0;i<maxn;i++)
 {	cnt1=i<s1?A[i]:0;
	cnt2=i<s2?B[i]:0;
	ret+=(cnt1>cnt2?(cnt1-cnt2):0);
 }
 return ret;
}

class ICPCBalloons
{	public:

	int minRepaintings(vector <int> balloonCount, string balloonSize, vector <int> maxAccepted)
	{	int i,j,k,x,sa=0,sb=0,ns1,ns2;
		int total=maxAccepted.size(),colors=balloonSize.size();
		
		ans=inf;
		a.clear();
		b.clear();
		for(i=0;i<colors;i++)
			if(balloonSize[i]=='L')
			{	a.push_back(balloonCount[i]);
				sa+=balloonCount[i];
			}
			else
			{	b.push_back(balloonCount[i]);
				sb+=balloonCount[i];
			}
		sort(a.begin(),a.end());
		reverse(a.begin(),a.end());
		sort(b.begin(),b.end());
		reverse(b.begin(),b.end());
		for(i=1;i<=(1<<total);i++)
		{	ns1=0;
			ns2=0;
			ua.clear();
			ub.clear();
			for(j=0;j<total;j++)
				if(((i>>j)&1)==1)
				{	ub.push_back(maxAccepted[j]);
					ns1+=maxAccepted[j];
				}
				else
				{	ua.push_back(maxAccepted[j]);
					ns2+=maxAccepted[j];
				}
			if(ns2>sa || ns1>sb) continue;
			sort(ua.begin(),ua.end());
			reverse(ua.begin(),ua.end());
			sort(ub.begin(),ub.end());
			reverse(ub.begin(),ub.end());
			x=calc(ua,a)+calc(ub,b);
			if (x<ans) ans=x;
		}
		if(ans!=inf) return ans;
		return -1;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "L"; int Arr2[] = {1,2,3,4,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 10; verify_case(0, Arg3, minRepaintings(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "M"; int Arr2[] = {10,20,30,40,50}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -1; verify_case(1, Arg3, minRepaintings(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {5,6,1,5,6,1,5,6,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "MLMMLMMLM"; int Arr2[] = {7,7,4,4,7,7}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 6; verify_case(2, Arg3, minRepaintings(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {100,100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "ML"; int Arr2[] = {50,51,51}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -1; verify_case(3, Arg3, minRepaintings(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {8,5,1,4,1,1,3,1,3,3,5,4,5,6,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "MMMLLLMMLLMLMLM"; int Arr2[] = {3,5,3,3,5,6,4,6,4,2,3,7,1,5,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 5; verify_case(4, Arg3, minRepaintings(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {1,18,4,7,19,7,7,1,4,8,10,5,14,13,8,22,6,3,13,5,3,4,2,1,3,15,19,4,5,9,4,11,2,7,12,20,11,26,22,7,2,10,9,20,13,20,2,9,11,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arg1 = "LLMLLLLMLLLLLLLLLLLLMLLLLLLLLLLMMLMLLLMLLLLLLLLMLL"; int Arr2[] = {44,59,29,53,16,23,13,14,29,42,13,15,66,4,47}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 210; verify_case(5, Arg3, minRepaintings(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	ICPCBalloons ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
