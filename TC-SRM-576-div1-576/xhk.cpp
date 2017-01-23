// BEGIN CUT HERE

// END CUT HERE
#line 5 "TheExperiment.cpp"
#include<bits/stdc++.h>
using namespace std;

#define ll long long
const int mod=1000000009;

int n,m,L,R,len,ans;
int a[310],s[310],f[310][310],g[310][310],h[310][310];

void update(int &i,int x)
{i=(i+x)%mod;
}

class TheExperiment
{	public:
	int countPlacements(vector <string> intensity, int M, int Len, int A, int B)
	{	int i,j,k,p,l,r,cnt1,cnt0;
		
		n=0;
		for(i=0;i<intensity.size();i++)
			for(j=0;j<intensity[i].length();j++)
				a[++n]=intensity[i][j]-48;
					
				
		m=M;
		len=Len;
		L=A;
		R=B;
		
		//L=8;
		//for(i=1;i<=96;i++) a[i]=1;
		//n=96;
		
		memset(s,0,sizeof(s));
		for(i=1;i<=n;i++) s[i]=s[i-1]+a[i];
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		memset(h,0,sizeof(h));
		h[0][0]=1;
		for(i=1;i<=n;i++)
		{	h[i][0]=1;
			for(j=1;j<=m;j++)
			{	h[i][j]=h[i-1][j];
				for(k=1;k<len && k<=i;k++)
					if(s[i]-s[i-k]>=L && s[i]-s[i-k]<=R)
					{	update(f[i][j],f[i-k][j-1]);
						if(i==k)
							update(f[i][j],j==1);
						else	
							update(f[i][j],h[i-k-1][j-1]);
						//if(i==4 && j==1 && k==3) cout<<"## "<<h[i-k][j-1]<<endl;
						update(g[i][j],g[i-k][j-1]);
						//update(g[i][j],h[i-k][j-1]);
					}
				if(len<=i && s[i]-s[i-len]>=L && s[i]-s[i-len]<=R)
				{	update(g[i][j],f[i-len][j-1]);
					update(g[i][j],g[i-len][j-1]);
					if(i==len)
						update(g[i][j],j==1);
					else
						update(g[i][j],h[i-len-1][j-1]);
				}
				update(h[i][j],g[i][j]);	
				//cout<<i<<" "<<j<<" "<<f[i][j]<<" "<<g[i][j]<<" "<<h[i][j]<<endl;
			}
		}
		ans=h[n][m];	
		
		return ans;	
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"341156"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 3; int Arg3 = 6; int Arg4 = 10; int Arg5 = 2; verify_case(0, Arg5, countPlacements(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { string Arr0[] = {"999112999"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 4; int Arg3 = 21; int Arg4 = 30; int Arg5 = 2; verify_case(1, Arg5, countPlacements(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { string Arr0[] = {"111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 2; int Arg3 = 2; int Arg4 = 3; int Arg5 = 0; verify_case(2, Arg5, countPlacements(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { string Arr0[] = {"59059", "110", "1132230231"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 5; int Arg3 = 10; int Arg4 = 20; int Arg5 = 6; verify_case(3, Arg5, countPlacements(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { string Arr0[] = {"111111111111111111111111", "111111111111111111111111111", "11111111111111111111111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; int Arg2 = 8; int Arg3 = 4; int Arg4 = 2700; int Arg5 = 418629948; verify_case(4, Arg5, countPlacements(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	TheExperiment ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
