// BEGIN CUT HERE

// END CUT HERE
#line 5 "DefectiveAddition.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=1000000007;
int n,ans;
int a[110],f[110][2][2];

void update(int &i,int x)
{i=(i+x)%mod;
}

class DefectiveAddition
{	public:
	int count(vector <int> cards, int m)
	{	int i,j,k,p,s,rest;
		
		n=cards.size();
		for(i=1;i<=n;i++) a[i]=cards[i-1];
		ans=0;
		for(i=30;i>=0;i--)
		{	if(i!=30)
			{	s=0;
				p=((1<<(30-i))-1)<<(i+1);
				for(j=1;j<=n;j++)
					s^=a[j]&p;
				//cout<<i<<" "<<s<<" "<<(m&p)<<" "<<p<<endl;
				if(s!=(m&p)) continue;
			}
			memset(f,0,sizeof(f));
			f[0][0][0]=1;
			for(j=1;j<=n;j++)
			{	rest=(a[j]&((1<<i)-1))+1;
				//cout<<j<<" "<<rest<<endl;
				if(a[j]&(1<<i))
				{	update(f[j][0][1],((ll)f[j-1][0][1]*(1<<i)%mod+f[j-1][0][0])%mod);
					update(f[j][0][1],(ll)f[j-1][1][1]*rest%mod);
					update(f[j][1][1],((ll)f[j-1][1][1]*(1<<i)%mod+f[j-1][1][0])%mod);
					update(f[j][1][1],(ll)f[j-1][0][1]*rest%mod);
					update(f[j][0][0],(ll)f[j-1][1][0]*rest%mod);
					update(f[j][1][0],(ll)f[j-1][0][0]*rest%mod);
				}
				else
				{	update(f[j][0][1],(ll)f[j-1][0][1]*rest%mod);
					update(f[j][1][1],(ll)f[j-1][1][1]*rest%mod);
					update(f[j][0][0],(ll)f[j-1][0][0]*rest%mod);
					update(f[j][1][0],(ll)f[j-1][1][0]*rest%mod);
				}
			}
			//if(i==1) cout<<f[n][1][1]<<endl;
			update(ans,f[n][(m&(1<<i))?1:0][1]);
		}
		s=0;
		for(i=1;i<=n;i++) s^=a[i];
		if(s==m) update(ans,1);
		return ans;		
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 3; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 6; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {4, 5, 7, 11}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 240; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {1,2,3,4,5,6,7,8,9,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 15; int Arg2 = 1965600; verify_case(3, Arg2, count(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {1,2,3,4,5,6,7,8,9,10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 16; int Arg2 = 0; verify_case(4, Arg2, count(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 949480669; verify_case(5, Arg2, count(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	DefectiveAddition ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
