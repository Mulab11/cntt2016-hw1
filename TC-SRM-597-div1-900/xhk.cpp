// BEGIN CUT HERE

// END CUT HERE
#line 5 "LittleElephantAndBoard.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=1000000007;
int n,nr,ng,nb,ans;
int fac[2000010],ifac[2000010];

int fpow(int i,int j)
{int ret=1;
 for(;j;i=(ll)i*i%mod,j/=2)
 	if(j&1) ret=(ll)ret*i%mod;
 return ret;
}

int comb(int N,int M)
{if(N<M) return 0;
 return (ll)fac[N]*ifac[M]%mod*ifac[N-M]%mod;
}

int solve(int N,int n1,int n2)
{int i,l,r,ret=0;
 
 if(N<0) return 0;
 if(n1<n2) swap(n1,n2);
 //if((n1-n2)%2!=N%2) return 0;
 for(i=0;i<=N;i++) //枚举一样多的间隔 
 {	if((n1-n2)%2!=(N-i)%2) continue;
 	l=(N-i+(n1-n2))/2;
 	r=(N-i-l);
 	if(l<0 || r<0) continue;
 	ret=(ret+(ll)comb(N,l)*comb(N-l,r)%mod*comb(n1-l-i+N-1,N-1)%mod*fpow(2,i)%mod)%mod;
 }

 return ret;
}

class LittleElephantAndBoard
{	public:
	int getNumber(int M, int R, int G, int B)
	{	int i,j;
		
		n=M;
		nr=n-R;
		ng=n-G;
		nb=n-B; //转换成每列没有的 
		if(nr<0 || ng<0 || nb<0) return 0;
		fac[0]=1;
		for(i=1;i<=2*n;i++) fac[i]=(ll)fac[i-1]*i%mod; //预处理阶乘及阶乘的逆元 
		ifac[2*n]=fpow(fac[2*n],mod-2);
		for(i=2*n-1;i>=0;i--) ifac[i]=(ll)ifac[i+1]*(i+1)%mod;
		
		//cout<<n<<" "<<nr<<" "<<ng<<" "<<nb<<endl;
		
		if(nr>0)
		{	ans=solve(nr-1,ng,nb);
			ans=(ans+(ll)2*solve(nr,ng,nb)%mod)%mod;
			ans=(ans+solve(nr+1,ng,nb))%mod;
		}
		else
			ans=solve(1,ng,nb);
		ans=ans*2%mod;
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 1; int Arg3 = 1; int Arg4 = 4; verify_case(0, Arg4, getNumber(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 2; int Arg2 = 2; int Arg3 = 0; int Arg4 = 0; verify_case(1, Arg4, getNumber(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 10; int Arg1 = 7; int Arg2 = 7; int Arg3 = 6; int Arg4 = 496; verify_case(2, Arg4, getNumber(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 474; int Arg1 = 250; int Arg2 = 300; int Arg3 = 398; int Arg4 = 969878317; verify_case(3, Arg4, getNumber(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	LittleElephantAndBoard ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
