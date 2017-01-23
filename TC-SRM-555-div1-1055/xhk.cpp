// BEGIN CUT HERE

// END CUT HERE
#line 5 "MapGuessing.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,m,mi,ma,tot;
long long w,ans;
long long c[110];
char b[1010];

int count(long long s)
{return !s?0:count(s-(s&(-s)))+1;
}

long long calc(int p)
{long long ret=0,now=0,flag=0;
 int i;
  
 for(i=1;i<=m;i++)
 {	if(b[i]=='<')
 		p--;
 	else if(b[i]=='>')
 		p++;
 	else if(b[i]-48==((w>>p)&1))
 	{	now|=(1LL<<p);
 		if((flag>>p)&1) flag^=(1LL<<p);
 	}
 	else
 		flag|=(1LL<<p);
 	if(!flag) ret=now;
 }
 return ret;
}

void dfs(int i,long long s,int sta)
{if(i==tot+1)
 {	//cout<<i<<" "<<s<<" "<<count(s)<<" "<<sta<<endl;
 	ans+=(sta?1:-1)*(1LL<<count(s));
	return;
 }
 if(s==0) return;
 dfs(i+1,s,sta);
 dfs(i+1,s&c[i],sta^1);
}

class MapGuessing
{	public:
	long long countPatterns(string goal, vector <string> code)
	{	int i,j,s;
	
		n=goal.length();	
		w=0;
		for(i=0;i<n;i++)
			if(goal[i]=='1') w+=(1LL<<i);
		m=0;	
		for(i=0;i<code.size();i++)
			for(j=0;j<code[i].length();j++)
				b[++m]=code[i][j];
		mi=0;
		ma=0;
		s=0;
		for(i=1;i<=m;i++)	
		{	if(b[i]=='<')
			{	s--;
				mi=min(mi,s);
			}
			else if(b[i]=='>')
			{	s++;
				ma=max(ma,s);
			}
		}
		tot=0;
		for(i=0;i<n;i++)
			if(i+mi>=0 && i+ma<n)
				c[++tot]=calc(i);
		//cout<<mi<<" "<<ma<<endl;		
		//for(i=1;i<=tot;i++)
		//	cout<<c[i]<<" ";
		//cout<<endl;		
		ans=0;
		dfs(1,(1LL<<n)-1,0);
		ans+=(1LL<<n);
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "000"; string Arr1[] = {"0"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 4LL; verify_case(0, Arg2, countPatterns(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "001"; string Arr1[] = {"0>1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 5LL; verify_case(1, Arg2, countPatterns(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "000"; string Arr1[] = {"1>1>1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1LL; verify_case(2, Arg2, countPatterns(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "11001"; string Arr1[] = {">><<<<><<"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(3, Arg2, countPatterns(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "1000101011"; string Arr1[] = {"1<<0>>0>1"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 22LL; verify_case(4, Arg2, countPatterns(Arg0, Arg1)); }
	void test_case_5() { string Arg0 = "00000010000000000000000000000000"; string Arr1[] = {"><>>0<0<>>1>0><>", "<<0>>0<>><0>0>>><><", ">>>0<>", ">0><>>>>0<<><>>0>>>0<0>>0>"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 13601LL; verify_case(5, Arg2, countPatterns(Arg0, Arg1)); }
	void test_case_6() { string Arg0 = "11100011010111111010100100110001101"; string Arr1[] = {"11111111111111111111"
,"1<><><><><><><><><>1"
,"1<>000>000><0<><0<>1"
,"1<0<><>0><0<00>00<>1"
,"1<>00<>000><0<0<0<>1"
,"1<><>0>0><0<0<><0<>1"
,"1<000<>0><0<0<><0<>1"
,"1<><><><><><><><><>1"
,"1<>000><000<>000><>1"
,"1<>0><><0<><>0><><>1"
,"1<>000><000<>000><>1"
,"1<><>0><><0<><>0><>1"
,"1<>000><000<>000><>1"
,"1<><><><><><><><><>1"
,"11111111111111111111"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 90LL; verify_case(6, Arg2, countPatterns(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	MapGuessing ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
