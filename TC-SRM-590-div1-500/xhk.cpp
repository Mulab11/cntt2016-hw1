// BEGIN CUT HERE

// END CUT HERE
#line 5 "XorCards.cpp"
#include<bits/stdc++.h>
using namespace std;

int n,tot,cnt;
long long m,ans;
long long a[110],b[110];

class XorCards
{	public:
	long long numberOfWays(vector<long long> number, long long limit)
	{	int i,j;
		long long w,s,now;
		
		n=number.size();
		m=limit;
		for(i=1;i<=n;i++) a[i]=number[i-1];
		memset(b,0,sizeof(b));
		tot=0;
		for(i=1;i<=n;i++) //求出线性基 
		{	for(j=60;j>=0;j--)
			{	if((a[i]&(1LL<<j))==0) continue;
				if(b[j])
					a[i]^=b[j];
				else
				{	b[j]=a[i];
					tot++;
					break;
				}
			}
		}
		w=1LL<<(n-tot);
		cnt=tot;
		now=0;
		ans=0;
		for(i=60;i>=0;i--) //逐位递推 
		{	if(!b[i]) //如果这一位没有线性基且now和m的位置不一样 
			{	if((now&(1LL<<i)) && (m&(1LL<<i))==0)
					break;
				else if((now&(1LL<<i))==0 && (m&(1LL<<i)))
				{	ans+=(1LL<<cnt)*w;
					break;
				}
				continue;
			}
			s=now;
			if(now&(1LL<<i)) s^=b[i];
			cnt--;
			if(m&(1LL<<i)) //如果m这位是1而now这位选0,更新答案 
			{	ans+=(1LL<<cnt)*w;
				s^=b[i];
			}
			now=s;	
		}
		if(i==-1) ans+=w;
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long Arr0[] = {345891921, 382252721, 345891921, 345891921, 382252721, 382252721, 398067702, 398067702, 345891921, 345891921, 345891921, 382252721, 345891921, 345891921, 345891921, 364380802, 368124924, 398067702}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 948354736LL; long long Arg2 = 262144LL; verify_case(0, Arg2, numberOfWays(Arg0, Arg1)); }
	void test_case_1() { long Arr0[] = {5,5}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 3LL; long long Arg2 = 2LL; verify_case(1, Arg2, numberOfWays(Arg0, Arg1)); }
	void test_case_2() { long Arr0[] = {1,2,3,4,5,6,7}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 5LL; long long Arg2 = 96LL; verify_case(2, Arg2, numberOfWays(Arg0, Arg1)); }
	void test_case_3() { long Arr0[] = {123, 456, 789, 147, 258, 369, 159, 357}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 500LL; long long Arg2 = 125LL; verify_case(3, Arg2, numberOfWays(Arg0, Arg1)); }
	void test_case_4() { long Arr0[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 1000000000000000LL; long long Arg2 = 4294967296LL; verify_case(4, Arg2, numberOfWays(Arg0, Arg1)); }
	void test_case_5() { long Arr0[] = {1000000000000000, 999999999999999}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 65535LL; long long Arg2 = 2LL; verify_case(5, Arg2, numberOfWays(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	XorCards ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
