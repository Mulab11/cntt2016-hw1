// BEGIN CUT HERE

// END CUT HERE
#line 5 "FoxAndHandle.cpp"
#include<bits/stdc++.h>
using namespace std;

int n;
int b[110][30],c[30];
char a[110];
string ans;

class FoxAndHandle
{	public:
	string lexSmallestName(string S)
	{	int i,j,k,p,s,flag;
		
		n=S.length();
		for(i=1;i<=n;i++) a[i]=S[i-1];
		for(i=1;i<=n;i++)
		{	for(j=1;j<=26;j++) b[i][j]=b[i-1][j];
			b[i][a[i]-96]++;
		}
		s=0;
		for(i=1;i<=26;i++)
		{	c[i]=b[n][i]/2;
			if(c[i]) s++;
		}
		i=0;
		ans="";
		while(s)
		{	for(j=1;j<=26;j++)
			{	k=i+1;
				while(k<=n && a[k]!=96+j) k++;
				flag=0;
				if(k<=n)
				{	flag=1;
					for(p=1;p<=26;p++)
						if(b[n][p]-b[k-1][p]<c[p])
						{	flag=0;
							break;
						}
					if(c[a[k]-96]==0) flag=0;	
				}
				if(flag) break;
			}
			c[a[k]-96]--;
			if(c[a[k]-96]==0) s--;
			i=k;
			ans+=a[i];
		}
		return ans;
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "foxfox"; string Arg1 = "fox"; verify_case(0, Arg1, lexSmallestName(Arg0)); }
	void test_case_1() { string Arg0 = "ccieliel"; string Arg1 = "ceil"; verify_case(1, Arg1, lexSmallestName(Arg0)); }
	void test_case_2() { string Arg0 = "abaabbab"; string Arg1 = "aabb"; verify_case(2, Arg1, lexSmallestName(Arg0)); }
	void test_case_3() { string Arg0 = "bbbbaaaa"; string Arg1 = "bbaa"; verify_case(3, Arg1, lexSmallestName(Arg0)); }
	void test_case_4() { string Arg0 = "fedcbafedcba"; string Arg1 = "afedcb"; verify_case(4, Arg1, lexSmallestName(Arg0)); }
	void test_case_5() { string Arg0 = "nodevillivedon"; string Arg1 = "deilvon"; verify_case(5, Arg1, lexSmallestName(Arg0)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	FoxAndHandle ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
