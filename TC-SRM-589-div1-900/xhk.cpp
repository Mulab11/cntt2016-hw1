// BEGIN CUT HERE

// END CUT HERE
#line 5 "FlippingBitsDiv1.cpp"
#include<bits/stdc++.h>
using namespace std;

const int inf=0x3f3f3f3f;
int n,m,l;
int a[310],b[310][310],f[310][2];

void update(int &i,int x)
{if(x<i) i=x;
}

int solve1() //m<17的情况，枚举每行状态 
{int i,j,k,s,ret=inf;
 
 for(i=0;i<(1<<m);i++)
 {	memset(f,0x3f,sizeof(f));
 	f[0][0]=0;
 	f[0][1]=1;
 	for(j=0;j<l;j++)
 	{	s=0;
 		for(k=1;k<=m;k++)
 			if(b[k][j+1]!=((i&(1<<(k-1)))?1:0))
 				s++;
 		update(f[j+1][0],f[j][0]+s);
 		update(f[j+1][1],f[j][0]+m-s+2);
 		update(f[j+1][0],f[j][1]+s);
 		update(f[j+1][1],f[j][1]+m-s);
 	}
 	s=min(f[l][0],f[l][1]);
 	for(j=1;j<=n%m;j++)
 		if(b[j][l+1]!=((i&(1<<(j-1)))?1:0)) s++;
 	ret=min(ret,s);
 }
 return ret;
}

int solve2() //m>17时n/m<17,枚举每列是否翻转 
{int i,j,k,s,x,cnt,s1,s0,ret=inf;
 
 for(i=0;i<(1<<l);i++)
 {	cnt=0;
 	for(j=1;j<=m;j++)
 	{	s0=s1=0;
 		for(k=1;(k-1)*m+j<=n;k++)
 		{	x=b[j][k]^((i&(1<<(k-1)))?1:0);
		 	if(x)
			 	s1++;
			else
				s0++;
		}
		cnt+=min(s0,s1);
	}
	for(j=2;j<=l+1;j++)
		if(((i&(1<<(j-1)))?1:0)!=((i&(1<<(j-2)))?1:0)) cnt++;
	ret=min(ret,cnt);
 }
 return ret;
}

class FlippingBitsDiv1
{	public:
	int getmin(vector <string> S, int M)
	{	int i,j;
		
		m=M;
		n=0;
		for(i=0;i<S.size();i++)
			for(j=0;j<S[i].length();j++)
				a[++n]=S[i][j]-48;
		for(i=1;i<=n;i++) //转化成按模m余数分成m行，每行值一样 
			b[(i+m-1)%m+1][(i-1)/m+1]=a[i];
		l=n/m;
		if(m<=17)
			return solve1();
		else
			return solve2();
	}
	
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"00111000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2; verify_case(0, Arg2, getmin(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"101100001101"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 2; verify_case(1, Arg2, getmin(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"11111111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; int Arg2 = 0; verify_case(2, Arg2, getmin(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"1101001000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; int Arg2 = 1; verify_case(3, Arg2, getmin(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"1","10","11","100","101","110"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 4; verify_case(4, Arg2, getmin(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"1001011000101010001111111110111011011100110001001"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 16; verify_case(5, Arg2, getmin(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{	FlippingBitsDiv1 ___test;
	___test.run_test(-1);
	return 0;
}
// END CUT HERE
