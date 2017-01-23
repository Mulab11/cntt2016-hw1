// BEGIN CUT HERE

// END CUT HERE
#line 5 "XorAndSum.cpp"
#include<bits/stdc++.h>
using namespace std;

int n;
long long ans;
long long a[110],b[110];

class XorAndSum
{	public:
	long long maxSum(vector<long long> number)
	{	int i,j,k,flag;
		long long s;
		
		n=number.size();
		for(i=1;i<=n;i++) a[i]=number[i-1];
		memset(b,0,sizeof(b));
		for(i=1;i<=n;i++)
		{	flag=0;
			for(j=62;j>=0;j--)
			{	if(a[i]&(1LL<<j))
				{	if(b[j]==0)
					{	b[j]=a[i];
						for(k=j-1;k>=0;k--)
							if(b[k] && (b[j]&(1LL<<k)))
								b[j]^=b[k];
						for(k=62;k>j;k--)
							if(b[k] && (b[k]&(1LL<<j)))
								b[k]^=b[j];
						flag=1;
					}
					else
						a[i]^=b[j];
				}
				if(flag) break;
			}
		}
		//cout<<b[1]<<" "<<b[0]<<endl;
		s=0;
		for(i=62;i>=0;i--)
			if(b[i]) s^=b[i];
		ans=n*s;
		flag=0;
		for(i=62;i>=0;i--)
		{	if(!b[i]) continue;
			if(!flag)
				flag=1;
			else
				ans+=(s^b[i])-s;
		}			
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long Arr0[] = {1,0}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 2LL; verify_case(0, Arg1, maxSum(Arg0)); }
	void test_case_1() { long Arr0[] = {1,2,3}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 8LL; verify_case(1, Arg1, maxSum(Arg0)); }
	void test_case_2() { long Arr0[] = {0,0,0,0,0,0,0,0,0,0}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 0LL; verify_case(2, Arg1, maxSum(Arg0)); }
	void test_case_3() { long Arr0[] = {2,3,5,7,11,13,17,19}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 233LL; verify_case(3, Arg1, maxSum(Arg0)); }
	void test_case_4() { long Arr0[] = {123456789012345, 0, 0, 0, 0, 0, 0, 0, 0, 0}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 1234567890123450LL; verify_case(4, Arg1, maxSum(Arg0)); }
	void test_case_5() { long Arr0[] = {627,674,281,272,289,877,62,122,603,189,615}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 10742LL; verify_case(5, Arg1, maxSum(Arg0)); }
	void test_case_6() { long Arr0[] = {557}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 557LL; verify_case(6, Arg1, maxSum(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	XorAndSum ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
