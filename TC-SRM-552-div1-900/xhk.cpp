// BEGIN CUT HERE

// END CUT HERE
#line 5 "HolyNumbers.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
int maxn,tot;
int u[1000010],prime[100010];

void work()
{int i,j;
 
 memset(u,0,sizeof(u));
 tot=0;
 for(i=2;i<=maxn;i++)
 {	if(!u[i]) prime[++tot]=i;
 	for(j=1;j<=tot;j++)
	{	if(i*prime[j]>maxn) break;
		u[i*prime[j]]=1;
		if(i%prime[j]==0) break;
	}
 }
}

long long dfs(int i,long long s)
{long long x,ret=0;

 //cout<<i<<" "<<s<<endl;
 if(i==tot+1) return 1;
 if(s<prime[i]) return 1;
 if((ll)prime[i]*prime[i]>s)
 {	//cout<<i<<" "<<s<<" "<<(upper_bound(prime+i,prime+tot+1,s)-prime)-i<<endl;
 	if(prime[tot]<=s)
 		return tot-i+1+1;
	else
		return (upper_bound(prime+i,prime+tot+1,s)-prime)-i+1;
 }
 ret=dfs(i+1,s);
 x=prime[i];
 while(s>=x)
 {	ret+=dfs(i+1,s/x);
 	x*=(ll)prime[i]*prime[i];
 }
 return ret;
}

class HolyNumbers
{	public:
	long long count(long long upTo, int maximalPrime)
	{	int i,j;
		maxn=maximalPrime;
	 	work();
	 	return dfs(1,upTo);
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 10LL; int Arg1 = 100; long long Arg2 = 8LL; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { long long Arg0 = 10LL; int Arg1 = 3; long long Arg2 = 5LL; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { long long Arg0 = 123LL; int Arg1 = 12; long long Arg2 = 32LL; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { long long Arg0 = 123LL; int Arg1 = 456; long long Arg2 = 88LL; verify_case(3, Arg2, count(Arg0, Arg1)); }
	void test_case_4() { long long Arg0 = 123456789LL; int Arg1 = 12345; long long Arg2 = 25994500LL; verify_case(4, Arg2, count(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	HolyNumbers ___test;
	___test.run_test(-1);
	//cout<<___test.count(10,3)<<endl;
	return 0;
}
// END CUT HERE
