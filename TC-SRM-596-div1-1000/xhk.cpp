// BEGIN CUT HERE

// END CUT HERE
#line 5 "SparseFactorial.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int inf=0x3f3f3f3f;
int m,now;
int a[1000010],b[1000010],f[1000010],used[1000010];
long long ans,L,R;

void solve(int p,int c,int t) //计算能整除p^c=t的a[]数组(k的最小值) 
{int i,j,w;

 for(i=0;i<t;i++)
 {	used[i]=0;
 	b[i]=inf;
 }
 for(i=0;i<p*c;i++) //只有前p*c个是有意义的 
 {	//j=0;
 	//while(j<t && j%p!=(ll)i*i%p) j++;
 	j=(ll)i*i%p;
 	for(;j<t;j+=p) //只枚举和p同余的 
 	{	//cout<<i<<" "<<j<<endl;
	 	if(used[j]>=c) continue;
 		w=(j+t-(ll)i*i%t-1)%t+1;
 		while(w%p==0)
 		{	w/=p;
 			used[j]++;
 		}
 		if(used[j]>=c) b[j]=i;
 	}
 }

 for(j=0;j<now*t;j++)
	f[j]=max(a[j%now],b[j%t]); //更新当前的答案 
 now*=t;
 for(j=0;j<now;j++) a[j]=f[j];
}
			
long long calc(long long N,int x,int y) //计算1~N有多少满足条件且模m余x的 
{long long L,R;

 if(y==inf) return 0;
 L=(ll)y*y+1;			
 if(L%m<=x)
 	L=(L/m)*m+x;
 else
 	L=(L/m+1)*m+x;
 if(N%m>=x)
 	R=(N/m)*m+x;
 else
 	R=(N/m-1)*m+x;
 if(R>=L) return (R-L)/m+1;
 return 0;
}
			
class SparseFactorial
{	public:
	long long getCount(long long lo, long long hi, long long divisor)
	{	int i,j,t,p,s;
		
		L=lo;
		R=hi;
		m=divisor;
		t=m;
		a[0]=0;
		now=1;
		for(i=2;i*i<=m;i++)
		{	if(t%i!=0) continue;
			p=0;
			s=1;
			while(t%i==0)
			{	t/=i;
				s*=i;
				p++;
			}
			solve(i,p,s);
		}
		if(t!=1) solve(t,1,t);
		
		//for(i=0;i<m;i++) cout<<a[i]<<" ";
		//cout<<endl;
		
		ans=0;
		for(i=0;i<now;i++)
			ans+=calc(R,i,a[i])-calc(L-1,i,a[i]);
		return ans;
	}
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long long Arg0 = 16725LL; long long Arg1 = 16790LL; long long Arg2 = 50077LL; long long Arg3 = 0LL; verify_case(0, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_1() { long long Arg0 = 9LL; long long Arg1 = 11LL; long long Arg2 = 7LL; long long Arg3 = 1LL; verify_case(1, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_2() { long long Arg0 = 1LL; long long Arg1 = 1000000000000LL; long long Arg2 = 4LL; long long Arg3 = 999999999996LL; verify_case(2, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_3() { long long Arg0 = 55LL; long long Arg1 = 66LL; long long Arg2 = 98LL; long long Arg3 = 7LL; verify_case(3, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_4() { long long Arg0 = 999990LL; long long Arg1 = 999999LL; long long Arg2 = 589824LL; long long Arg3 = 7LL; verify_case(4, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_5() { long long Arg0 = 100000000LL; long long Arg1 = 100000050LL; long long Arg2 = 749910LL; long long Arg3 = 8LL; verify_case(5, Arg3, getCount(Arg0, Arg1, Arg2)); }
	void test_case_6() { long long Arg0 = 7777777776LL; long long Arg1 = 7777777777LL; long long Arg2 = 994009LL; long long Arg3 = 1LL; verify_case(6, Arg3, getCount(Arg0, Arg1, Arg2)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	SparseFactorial ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
