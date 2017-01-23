// BEGIN CUT HERE

// END CUT HERE
#line 5 "MagicalHats.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=1e9;

struct unit
{int x,y;
};
struct unit a[20];

int n,m,R,C,lim,ans;
int cx[20],cy[20],pw3[20],f[2000010];

int get_dgt(int x,int i)
{return (x/pw3[i])%3;
}

int set_dgt(int x,int i,int y)
{return x%pw3[i]+x/pw3[i+1]*pw3[i+1]+pw3[i]*y;
}

int work(int sta,int s,int p)
{int i,j,ret,s1;
 
 if(f[sta]!=-1) return f[sta];
 if(s>m) return inf;
 if(p==n)
 {	//cout<<sta<<" "<<s<<" "<<p<<endl;
 	if(s!=m) return inf;
 	memset(cx,0,sizeof(cx));
 	memset(cy,0,sizeof(cy));
 	for(i=0;i<n;i++)
 		if(get_dgt(sta,i)==1)
 		{	cx[a[i+1].x]^=1;
 			cy[a[i+1].y]^=1;
 		}
 	for(i=1;i<=R;i++)
 		if(cx[i]) return inf;
 	for(i=1;i<=C;i++)
 		if(cy[i]) return inf;
 	//cout<<sta<<" ok"<<endl;	
 	return 0;
 }
 ret=-1;
 for(i=0;i<n;i++)
 {	if(get_dgt(sta,i)) continue;
 	s1=min(work(set_dgt(sta,i,1),s,p+1),work(set_dgt(sta,i,2),s+1,p+1)+(p<lim));
 	if(ret==-1 || s1>ret) ret=s1;
 }
 ret=min(ret,inf);
 return f[sta]=ret;
}

class MagicalHats
{	public:
	int findMaximumReward(vector <string> board, vector <int> coins, int numGuesses)
	{	int i,j,k;
	 
	 	R=board.size();
	 	C=board[0].length();
	 	lim=numGuesses;
	 	n=0;
	 	for(i=1;i<=R;i++)
	 		for(j=1;j<=C;j++)
	 			if(board[i-1][j-1]=='H')
	 				a[++n]=(unit){i,j};
	 	pw3[0]=1;			
	 	for(i=1;i<=n;i++) pw3[i]=pw3[i-1]*3;			
	 	m=coins.size();	
	 	
	 	//cout<<n<<" "<<m<<endl;
	 	
	 	memset(f,-1,sizeof(f));
		k=work(0,0,0);
		if(k==inf) return -1;
		ans=0;
		sort(coins.begin(),coins.end());
		for(i=0;i<k;i++) ans+=coins[i];
		return ans; 		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"H"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 1; verify_case(0, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"HHH",
 "H.H",
 "HH."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; int Arg3 = 9; verify_case(1, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"HH",
 "HH"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 6; verify_case(2, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"HHH",
 "HHH",
 "H.H"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {13,13,13,13}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; int Arg3 = 13; verify_case(3, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"HHH",
 "HHH",
 "H.H"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {13,13,13,13}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 26; verify_case(4, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arr0[] = {"H.H.",
 ".H.H",
 "H.H."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {17}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; int Arg3 = -1; verify_case(5, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
	void test_case_6() { string Arr0[] = {"HHH",
 "H.H",
 "HHH",
 "H.H",
 "HHH"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {33,337,1007,2403,5601,6003,9999}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; int Arg3 = 1377; verify_case(6, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }
	void test_case_7() { string Arr0[] = {".............",
 ".............",
 ".............",
 ".............",
 ".............",
 ".............",
 ".....H.H.....",
 "......H......",
 ".....H.H.....",
 ".............",
 ".............",
 ".............",
 "............."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {22}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; int Arg3 = 22; verify_case(7, Arg3, findMaximumReward(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	MagicalHats ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
